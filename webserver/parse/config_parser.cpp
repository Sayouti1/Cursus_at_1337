#include "config_parser.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <set>

std::string Config::trim_whitespace(const std::string& str) {
    size_t first = str.find_first_not_of(" \t");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

std::vector<std::string> Config::tokenize_directive(const std::string& str) {
    std::vector<std::string> tokens;
    std::string token;
    bool in_quotes = false;
    char c = '\0';
    bool found_semicolon = false;

    // Trim leading whitespace
    size_t start = 0;
    while (start < str.size() && isspace(str[start])) {
        start++;
    }

    for (size_t i = start; i < str.size(); ++i) {
        c = str[i];

        if (c == '"') {
            in_quotes = !in_quotes;
            // Don't include quotes in the token
        } else if (isspace(c) && !in_quotes) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else if (c == ';' && !in_quotes) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            found_semicolon = true;
            break;
        } else if ((c == '{' || c == '}') && !in_quotes) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(std::string(1, c));
            break;
        } else {
            token += c;
        }
    }
    if (!token.empty()) {
        tokens.push_back(token);
    }

    if (in_quotes) {
        throw std::runtime_error(": [emerg] unmatched quotes in directive: " + str);
    }
    if (!tokens.empty()) {
        std::string last_token = tokens.back();
        bool is_block_directive = (last_token == "{" || last_token == "}");
        bool is_block_start = false;

        if (!tokens.empty() && tokens.size() >= 2) {
            std::string first_token = tokens[0];
            is_block_start = (first_token == "server" || first_token == "location") && last_token == "{";
        }
        if (!found_semicolon && !is_block_directive && !is_block_start) {
            throw std::runtime_error(": [emerg] missing semicolon at the end of directive: " + str);
        }
    }

    if (tokens.size() >= 2) {
        if (tokens[tokens.size()-1] == "}" && tokens[tokens.size()-2] == "}") {
            throw std::runtime_error(": [emerg] unexpected '}' in directive: " + str);
        }
    }

    return tokens;
}



bool Config::is_valid_directive(const std::string& directive, size_t min_args, size_t max_args) {
    if (directive.empty()) return false;
    if (directive[0] == '#') return false;
    if (directive.find('{') != std::string::npos && directive.find("location") == std::string::npos){ return false;}
    // if (directive.find('}') != std::string::npos) return false;

    std::vector<std::string> tokens = tokenize_directive(directive);
    if (tokens.size() < min_args + 1) return false;
    if (max_args != 0 && tokens.size() > max_args + 1) return false;

    return true;
}

Location::Location()
    : is_redirect(false),
      is_cgi_location(false),
      path_("/"),
      allow_methods_(),
      root_(""),
      index_("index.html"),
      autoindex_(false),
      cgi_enable_(false),
      cgi_extension_(),
      cgi_path_(""),
      return_(std::make_pair(0, "")),
      upload_enable_(false),
      upload_pass_("")
{}


void Location::set_path(const std::string& path) { path_ = path; }
void Location::set_cgi_bool(bool cgi_) { is_cgi_location = cgi_; }
void Location::add_allow_method(const std::string& method) { allow_methods_.push_back(method); }
void Location::set_root(const std::string& root) { root_ = root; }
void Location::set_index(const std::string& index) { index_ = index; }
void Location::set_autoindex(bool autoindex) { autoindex_ = autoindex; }
void Location::set_cgi_extension(const std::string& cgi_extension) { cgi_extension_.push_back(cgi_extension); }
void Location::set_cgi_path(const std::string& cgi_path) { cgi_path_ = cgi_path; }
void Location::set_cgi_enable(bool cgi) { cgi_enable_ = cgi; }
void Location::set_upload_enable(bool upload_enable) { upload_enable_ = upload_enable; }
void Location::set_return(int code, const std::string& url) { return_ = std::make_pair(code, url); }
void Location::set_upload_pass(const std::string& path) { upload_pass_ = path; }
void Location::set_is_redirect(bool is_red) { is_redirect = is_red; }

const std::string& Location::get_path() const { return path_; }
const std::vector<std::string>& Location::get_allow_methods() const { return allow_methods_; }
const std::string& Location::get_root() const { return root_; }
const std::string& Location::get_index() const { return index_; }
bool Location::get_autoindex() const { return autoindex_; }
bool Location::cgi_enable() const { return cgi_enable_; }
bool Location::upload_enable() const { return upload_enable_; }
const std::vector<std::string>& Location::get_cgi_extension() const { return cgi_extension_; }
const std::pair<int, std::string>& Location::get_return() const { return return_; }
const std::string& Location::get_cgi_path() const { return cgi_path_; }
const std::string& Location::get_upload_pass() const { return upload_pass_; }
bool Location::get_cgi_bool() const { return is_cgi_location; }
bool Location::get_is_redirect() const { return is_redirect; }

// Server implementation
Server::Server() :
    listen_(9090) {
    hoste_ = "127.0.0.1";
    root_ = "";
    client_max_body_size_ = 10000000;
    error_pages_[404] = "/error_pages/error_404.html";
    // server_names_.push_back("localhost");
    root_ = "./html";
    }

void Server::set_listen(int port) { listen_ = port; }
void Server::set_hoste(const std::string& hoste) { hoste_ = hoste; }
void Server::set_server_name(const std::string& name) { server_names_.push_back(name); }
void Server::set_root(const std::string& root) { root_ = root; }
void Server::add_error_page(int code, const std::string& page) { error_pages_[code] = page; }
void Server::set_client_max_body_size(size_t size) { client_max_body_size_ = size; }
void Server::add_location(const Location& location) { locations_.push_back(location); }

int Server::get_listen() const { return listen_; }
std::string Server::get_hoste() const { return hoste_; }
const std::vector<std::string>& Server::get_server_names() const { return server_names_; }
const std::string& Server::get_root() const { return root_; }
const std::map<int, std::string>& Server::get_error_pages() const { return error_pages_; }
size_t Server::get_client_max_body_size() const { return client_max_body_size_; }
const std::vector<Location>& Server::get_locations() const { return locations_; }

// Config implementation
Config::Config() {}

std::vector<std::string> split_by_whitespace(const std::string& str) {
    std::istringstream iss(str);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

size_t Config::parse_size_with_suffix(const std::string& str) {
    size_t multiplier = 1;
    size_t num = 0;
    std::string num_str = str;

    if (!num_str.empty()) {
        char last = tolower(num_str[num_str.size()-1]);
        if (last == 'k') {
            multiplier = 1024;
            num_str = num_str.substr(0, num_str.size()-1);
        } else if (last == 'm') {
            multiplier = 1024 * 1024;
            num_str = num_str.substr(0, num_str.size()-1);
        } else if (last == 'g') {
            multiplier = 1024 * 1024 * 1024;
            num_str = num_str.substr(0, num_str.size()-1);
        }
        num = atoi(num_str.c_str());
    }
    return num * multiplier;
}

void Config::parse_location_syntax(std::vector<std::string>::iterator &it, std::vector<std::string> &V, bool& server_b)
{
    (void) V;
    (void) server_b;
    bool root_b = true;
    std::vector<std::string> tokens;
    it++;
    for(; (*it) != "}"; it++)
    {
        if (*it == "}" && !root_b)
        {
            throw std::runtime_error(std::string(": [emerg] unexpected '}' found: ") + (*it).c_str());
        }
        if (*it == "}" && root_b)
        {
            root_b = false;
            break;
        }
        tokens = split_by_whitespace(*it);
        if (tokens.empty())
            continue;
        if (tokens.back()[tokens.back().size()-1] != ';' && tokens[0] != "}" && tokens[0] != "location"){
            throw std::runtime_error(std::string(": [emerg] missing semicolon at the end of directive: ") + (*it).c_str());
        }
        tokens.back().erase(tokens.back().size() - 1);
        if (tokens[0] == "root")
        {
            if (tokens.size() != 2)
                throw std::runtime_error(std::string(": [emerg] invalid root directive: ") + (*it).c_str());
            if (!root_b)
                throw std::runtime_error(std::string(": [emerg] root directive outside of location block: ") + (*it).c_str());
        }
        else if (tokens[0] == "index")
        {
            if (tokens.size() < 2)
                throw std::runtime_error(std::string(": [emerg] invalid index directive: ") + (*it).c_str());
        }
        else if (tokens[0] == "methods")
        {
            if (tokens.size() < 2)
                throw std::runtime_error(std::string(": [emerg] invalid allow_methods directive."));
            std::vector<std::string> valid_methods; valid_methods.push_back("GET"); valid_methods.push_back("DELETE"); valid_methods.push_back("POST");
            std::set<std::string> seen_methods;
            for (size_t i = 1; i < tokens.size(); i++) {
                bool is_valid = false;
                for (size_t j = 0; j < valid_methods.size(); j++) {
                    if (tokens[i] == valid_methods[j]) {
                        is_valid = true;
                        break;
                    }
                }
                if (!is_valid)
                    throw std::runtime_error(std::string(": [emerg] invalid allow_methods directive: ") + (*it).c_str());
                if (seen_methods.count(tokens[i]) > 0)
                    throw std::runtime_error(std::string(": [emerg] duplicate method in allow_methods directive: ") + tokens[i]);
                seen_methods.insert(tokens[i]);
            }
        }
        else if (tokens[0] == "return" || tokens[0] == "redirect")
        {
            for (size_t i = 0; i < tokens.size(); i++) {
                if (tokens[i].empty())
                    throw std::runtime_error(std::string(": [emerg] invalid return directive: ") + (*it).c_str());
            }
            if (tokens.size() != 3)
                throw std::runtime_error(std::string(": [emerg] invalid return directive: ") + (*it).c_str());
            int code = atoi(tokens[1].c_str());
            if (code < 100 || code > 599)
                throw std::runtime_error(std::string(": [emerg] invalid return code in directive: ") + (*it).c_str());
        }
        else if (tokens[0] == "autoindex")
        {
            if (tokens.size() != 2 ||( tokens[1] != "on" && tokens[1] != "off"))
                throw std::runtime_error(std::string(": [emerg] invalid autoindex directive: ") + (*it).c_str());
        }
        else if (tokens[0] == "upload_pass")
        {
            if (tokens.size() != 2)
                throw std::runtime_error(std::string(": [emerg] invalid upload_pass directive: ") + (*it).c_str());
        }
        else if (tokens[0]== "upload_enable")
        {
            if (tokens.size() != 2 ||( tokens[1] != "on" && tokens[1] != "off"))
                throw std::runtime_error(std::string(": [emerg] invalid upload_enable directive: ") + (*it).c_str());
        }
        else if (tokens[0] == "cgi_path")
        {
            if (tokens.size() != 2)
                throw std::runtime_error(std::string(": [emerg] invalid cgi_path directive: ") + (*it).c_str());
        }
        else if (tokens[0] == "cgi_extension")
        {
            if (tokens.size() < 2)
                throw std::runtime_error(std::string(": [emerg] invalid cgi_extensions directive: ") + (*it).c_str());
        }
        else if (tokens[0] == "cgi_enable")
        {
            if (tokens.size() != 2 ||( tokens[1] != "on" && tokens[1] != "off"))
                throw std::runtime_error(std::string(": [emerg] invalid cgi_extensions directive: ") + (*it).c_str());
        }
        else
        {
            throw std::runtime_error(std::string(": [emerg] unknown directive: ") + tokens[0]);
        }
    }
}


bool parse_ip_port(std::vector<std::string>& tokns) {
    if (tokns.size() != 2)
        return false;

    std::string value = tokns[1];
    size_t colon_pos = value.find(':');
    std::string ip;
    std::string port_str;

    if (colon_pos != std::string::npos) {
        ip = value.substr(0, colon_pos);
        if (ip.empty())
            return false;
        port_str = value.substr(colon_pos + 1);
        // Validate IP address (IPv4 only)
        int dots = 0;
        size_t start = 0;
        for (size_t i = 0; i < ip.size(); ++i) {
            if (ip[i] == '.') {
                std::string part = ip.substr(start, i - start);
                if (part.empty() || part.size() > 3)
                    return false;
                for (size_t j = 0; j < part.size(); ++j) {
                    if (!isdigit(part[j]))
                        return false;
                }
                int num = atoi(part.c_str());
                if (num < 0 || num > 255)
                    return false;
                dots++;
                start = i + 1;
            }
        }
        std::string last_part = ip.substr(start);
        if (last_part.empty() || last_part.size() > 3)
            return false;
        for (size_t j = 0; j < last_part.size(); ++j) {
            if (!isdigit(last_part[j]))
                return false;
        }
        int num = atoi(last_part.c_str());
        if (num < 0 || num > 255)
            return false;
        if (dots != 3)
            return false;
        for (size_t j = 0; j < port_str.size(); ++j) {
            if (!isdigit(port_str[j]))
                return false;
        }
        int port = atoi(port_str.c_str());
        if (port <= 0 || port > 65535)
            return false;
    } else {
        for (size_t j = 0; j < value.size(); ++j) {
            if (!isdigit(value[j]))
                return false;
        }
        int port = atoi(value.c_str());
        if (port <= 0 || port > 65535)
            return false;
    }
    return true;
}

void Config::parse_server_syntax(std::vector<std::string>::iterator &i, std::vector<std::string> &V, bool& server_b)
{
    std::vector<std::string> s_tokens;
    std::vector<std::string> tokens;
    std::vector<std::string>::iterator it = i;

    for (; it != V.end(); it++)
    {
        s_tokens = tokenize_directive(*it);

        if (s_tokens.empty())
            continue;
        if (s_tokens[0] == "listen")
        {
            if (s_tokens.size() != 2)
                throw std::runtime_error(std::string(": [emerg] invalid listen directive: ") + (*it).c_str());
            if (!parse_ip_port(s_tokens))
                throw std::runtime_error(std::string(": [emerg] invalid listen directive: ") + (*it).c_str());
            // int port = atoi(s_tokens[1].c_str());
            // if (port <= 0 || port > 65535)
            //     throw std::runtime_error(std::string(": [emerg] invalid port number in listen directive: ") + s_tokens[1]);
            continue;
        }
        if (s_tokens[0] == "server_name")
        {
            if (s_tokens.size() < 2)
                throw std::runtime_error(std::string(": [emerg] invalid server_name directive: ") + (*it).c_str());
            continue;
        }
        if (s_tokens[0] == "error_page")
        {
            if (s_tokens.size() != 3)
                throw std::runtime_error(std::string(": [emerg] invalid error_page directive: ") + (*it).c_str());
            int code = atoi(s_tokens[1].c_str());
            if (code < 100 || code > 599)
                throw std::runtime_error(std::string(": [emerg] invalid error code in error_page directive: ") + s_tokens[1]);
            continue;
        }
        if (s_tokens[0] == "client_max_body_size")
        {
            if (s_tokens.size() != 2)
                throw std::runtime_error(std::string(": [emerg] invalid client_max_body_size directive: ") + (*it).c_str());
            size_t size = parse_size_with_suffix(s_tokens[1]);
            if (size == 0)
                throw std::runtime_error(std::string(": [emerg] invalid client_max_body_size value: ") + s_tokens[1]);
            continue;
        }
        // if (s_tokens.back()[s_tokens.back().size()-1] != ';' && s_tokens[0] != "location" && s_tokens[0] != "}")
        //     throw std::runtime_error(std::string(": [emerg] missing semicolon at the end of directive: ") + (*it).c_str());
        if (s_tokens[0] == "location")
        {
            if (!server_b)
                throw std::runtime_error(std::string(": [emerg] location directive outside of server block: ") + (*it).c_str());
            if (s_tokens.size() < 2 || trim_whitespace(s_tokens[1]) == "{")
                throw std::runtime_error(std::string(": [emerg] invalid location directive"));
            if ((*it)[(*it).size()-1] != '{')
                throw std::runtime_error(std::string(": [emerg] invalid location directive: ") + (*it).c_str());
            parse_location_syntax(it, V, server_b);
            continue;
        }
        if (s_tokens[0] == ";")
                throw std::runtime_error(std::string(": [emerg] invalid semicolon directive: ") + (*it).c_str());
        if (s_tokens[0] == "}" || it == V.end() - 1)
            break;
    }
    i = it;
}

void Config::parse_syntax(std::vector<std::string> &V)
{
    bool server_b = false;

    std::string d;
    std::vector<std::string> s_tokens;
    std::vector<std::string> tokens;
    if (V[0] != "server {" && V[0] != "server" && V[0] != "server{")
        throw std::runtime_error(std::string(": [emerg] expected 'server {' at the beginning of configuration file: ") + V[0].c_str());
    for (std::vector<std::string>::iterator it = V.begin(); it != V.end(); it++)
    {
        if ((*it).find("server") == 0)
        {
            it++;
            server_b = true;
            parse_server_syntax(it, V, server_b);
        }
        if (it == V.end())
            throw std::runtime_error(": [emerg] unexpected end of file, expecting '}' in server block");
        if (*it == "}")
        {
            if (!server_b)
                throw std::runtime_error(std::string(": [emerg] unexpected '}' found: ") + (*it).c_str());
            server_b = false;
            continue;
        }
        else if (*it == "server {" && server_b)
        {
            throw std::runtime_error(std::string(": [emerg] nested server block found: ") + (*it).c_str());
        }
    }
}

std::string trim(const std::string& s) {
    size_t start = 0;
    while (start < s.length() && std::isspace(s[start])) ++start;

    size_t end = s.length();
    while (end > start && std::isspace(s[end - 1])) --end;

    return s.substr(start, end - start);
}

std::vector<std::string> tokenize_config(const std::string& config) {
    std::vector<std::string> tokens;
    std::string current;

    for (size_t i = 0; i < config.size(); ++i) {
        char ch = config[i];

        if (ch == '\n')
            ch = ' ';
        if (ch == ';' || ch == '{') {
            current += ch;
            std::string trimmed = trim(current);
            if (!trimmed.empty()) {
                tokens.push_back(trimmed);
            }
            current.clear();
        } else if (ch == '}') {
            std::string trimmed = trim(current);
            if (!trimmed.empty()) {
                tokens.push_back(trimmed);
            }
            current.clear();

            tokens.push_back("}");
        } else {
            current += ch;
        }
    }

    std::string trimmed = trim(current);
    if (!trimmed.empty()) {
        tokens.push_back(trimmed);
    }

    return tokens;
}



void Config::parse(const std::string& filename) {
    std::ifstream file(filename.c_str());
    std::vector<std::string> C;
    std::string V;
    if (!file.is_open()) {
        throw std::runtime_error(": [emerg] could not open configuration file: " + filename);
    }
    std::string line;
    while (std::getline(file, line)) {
        line = trim_whitespace(line);
        if (line.empty() || line[0] == '#') continue;
        V += line + "\n"; // Append line to V with newline
    }
    if (V.empty())
        throw std::runtime_error(": [emerg] empty configuration file");
    C = tokenize_config(V);
    parse_syntax(C);
    parse_server_block(C[0], C);
}

void Config::parse_server_block(std::string& line, std::vector<std::string> &V) {
    bool server_b = false;

    for(std::vector<std::string>::iterator it = V.begin(); it != V.end(); it++) {
        if ((*it) == "server {"){
            server_b = true;
            parse_directive(line, V, server_b, it);
        }
        else
            throw std::runtime_error(std::string(": [emerg] unexpected directive outside of server block: ") + (*it).c_str());
    }
}

void Config::parse_location_block(std::vector<std::string> &V, std::string& line, Server& server, bool& loaction_b, std::vector<std::string>::iterator &i) {
    Location location;
    // (void) V;
    location.set_root(server.get_root());
    std::vector<std::string> tokens = tokenize_directive(*i);
    if (tokens.empty()) {
        throw std::runtime_error(": [emerg] empty location directive");
    }
    if (tokens.size() < 2 || tokens[0] != "location") {
        throw std::runtime_error(": [emerg] invalid location directive: " + line);
    }

    location.set_path(tokens[1]);
    if (tokens[1].size() >= 3 && tokens[1].substr(tokens[1].size() - 3) == ".py") {
        location.set_cgi_bool(true);
    }
    if (tokens.size() > 2 && tokens[2] != "{") {
        throw std::runtime_error(": [emerg] invalid location block syntax");
    }
    for(    ; i != V.end(); i++) {
        line = trim_whitespace(*i);
        if (line.empty()) continue;

        if (line == "}") {

            server.add_location(location);
            i++;
            loaction_b = false;
            return;
        }

        if (is_valid_directive(line, 1, 10)) {
            tokens = tokenize_directive(line);
            if (tokens[0] == "root")
                location.set_root(tokens[1]);
            if (tokens[0] == "index")
                location.set_index(tokens[1]);
            if (tokens[0] == "methods") {
                for (size_t i = 1; i < tokens.size(); i++) {
                    std::transform(tokens[i].begin(), tokens[i].end(), tokens[i].begin(), ::tolower);
                    location.add_allow_method(tokens[i]);
                }
            }
            if (tokens[0] == "return" || tokens[0] == "redirect"){
                location.set_return(atoi((tokens[1]).c_str()), tokens[2]);
                location.set_is_redirect(true);
            }
            if (tokens[0] == "autoindex"){
                if (tokens[1] == "on")
                    location.set_autoindex(true);
                else
                    location.set_autoindex(false);
            }
            if (tokens[0] == "upload_pass")
                location.set_upload_pass(tokens[1]);
            if (tokens[0] == "upload_enable") {
                if (tokens[1] == "on")
                    location.set_upload_enable(true);
                else
                    location.set_upload_enable(false);
            }
            if (tokens[0] == "cgi_extension") {
                for (size_t i = 1; i < tokens.size(); i++){
                    location.set_cgi_extension(tokens[i]);
                }
            }
            if (tokens[0] == "cgi_path"){
                location.set_cgi_bool(true);
                location.set_cgi_path(tokens[1]);}
            if (tokens[0] == "cgi_enable") {
                if (tokens[1] == "on"){
                    location.set_cgi_bool(true);
                    location.set_cgi_enable(true);
                }
                else
                    location.set_cgi_enable(false);
            }
        }
    }
}

void Server::cheak_location()
{
    std::vector<Location>::const_iterator it;
    for (it = get_locations().begin(); it != get_locations().end(); it++)
    {
        if ((*it).get_path() == "/")
        break;
    }
    if (it == get_locations().end())
    {
        Location loaction;
        loaction.set_path("/");
        if (get_root().empty())
            loaction.set_root("./html");
        else
            loaction.set_root(get_root());
        if (loaction.upload_enable()) {
            if (loaction.get_upload_pass().empty())
                loaction.set_upload_pass("upload");
        }
        loaction.add_allow_method("get");
        loaction.add_allow_method("post");
        loaction.set_index("index.html");
        locations_.insert(locations_.begin(), loaction);
    }
}

void Config::parse_directive(std::string& line, std::vector<std::string> &V, bool& server_b, std::vector<std::string>::iterator &it) {

    (void) server_b;
    bool location_block = false;
    Server server;
    it++;
    std::vector<std::string>::iterator i = it;
    while (i != V.end())
    {
        std::vector<std::string> tokens = tokenize_directive(*i);
        if (tokens[0] == "listen") {
            std::string host = "127.0.0.1"; // Default host
            int port = 9090; // Default port
            if (tokens.size() != 2) {
                throw std::runtime_error(": [emerg] invalid host directive: " + line);
            }
            if (tokens[1].find(':') != std::string::npos) {
                host = tokens[1].substr(0, tokens[1].find(':'));
                port = atoi(tokens[1].substr(tokens[1].find(':') + 1).c_str());
                if (port <= 0 || port > 65535) {
                    throw std::runtime_error(": [emerg] invalid port number in listen directive: " + tokens[1]);
                }
                server.set_listen(port);
                server.set_hoste(host);
            } else {
                port = atoi(tokens[1].c_str());
                if (port <= 0 || port > 65535) {
                    throw std::runtime_error(": [emerg] invalid port number in listen directive: " + tokens[1]);
                }
                server.set_listen(port);
            }
            i++;
            continue;
        } else if (tokens[0] == "server_name") {
            if (tokens.size() < 2) {
                throw std::runtime_error(": [emerg] invalid server_name directive: " + line);
            }
            for (size_t i = 1; i < tokens.size(); ++i) {
                server.set_server_name(tokens[i]);
            }
            i++;
            continue;
        } else if (tokens[0] == "root") {
            if (tokens.size() != 2) {
                throw std::runtime_error(": [emerg] invalid root directive: " + line);
            }
            server.set_root(tokens[1]);
            i++;
            continue;
        } else if (tokens[0] == "error_page") {
            if (tokens.size() != 3) {
                throw std::runtime_error(": [emerg] invalid error_page directive: " + line);
            }
            int code = atoi(tokens[1].c_str());
            if (code < 100 || code > 599) {
                throw std::runtime_error(": [emerg] invalid error code in error_page directive: " + tokens[1]);
            }
            server.add_error_page(code, tokens[2]);
            i++;
            continue;
        }
        else if (tokens[0] == "client_max_body_size") {
            if (tokens.size() != 2) {
                throw std::runtime_error(": [emerg] invalid client_max_body_size directive: " + line);
            }
            size_t size = parse_size_with_suffix(tokens[1]);
            if (size == 0) {
                throw std::runtime_error(": [emerg] invalid client_max_body_size value: " + tokens[1]);
            }
            server.set_client_max_body_size(size);
            i++;
            continue;
        }
        if (tokens[0] == "location") {
            location_block = true;
            parse_location_block(V, line, server, location_block, i);
            continue;
        }
        if (*i == "}" && !location_block) {
            server.cheak_location();
            servers_.push_back(server);
            it = i;
            return;
        }
        else
            throw std::runtime_error(": [emerg] unknown directive: " + tokens[0]);
    }
}

const std::vector<Server>& Config::get_servers() const {
    return servers_;
}