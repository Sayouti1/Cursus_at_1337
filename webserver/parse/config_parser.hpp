#pragma once

#include <string>
#include <vector>
#include <map>
#include <stdexcept>


class Location {
public:
    Location();

    // Setters
    void set_path(const std::string& path);
    void add_allow_method(const std::string& method);
    void set_root(const std::string& root);
    void set_index(const std::string& index);
    void set_autoindex(bool autoindex);
    void set_cgi_enable(bool cgi);
    void set_upload_enable(bool upload_enable);
    void set_cgi_extension(const std::string& cgi_extension);
    void set_cgi_path(const std::string& cgi_path);
    void set_return(int code, const std::string& url);
    void set_upload_pass(const std::string& path);
    void set_cgi_bool(bool cgi_);
    void set_is_redirect(bool is_red);

    // Getters
    const std::string& get_path() const;
    const std::vector<std::string>& get_allow_methods() const;
    const std::string& get_root() const;
    const std::string& get_index() const;
    bool get_autoindex() const;
    bool cgi_enable() const;
    bool upload_enable() const;
    const std::vector<std::string>& get_cgi_extension() const;
    const std::string& get_cgi_path() const;
    const std::pair<int, std::string>& get_return() const;
    const std::string& get_upload_pass() const;
    bool get_cgi_bool() const;
    bool get_is_redirect() const;

private:
    bool is_redirect;
    bool is_cgi_location;
    std::string path_;
    std::vector<std::string> allow_methods_;
    std::string root_;
    std::string index_;
    bool autoindex_;
    bool cgi_enable_;
    std::vector<std::string> cgi_extension_;
    std::string cgi_path_;
    std::pair<int, std::string> return_;
    bool upload_enable_;
    std::string upload_pass_;
};

class Server {
public:
    Server();

    // Setters
    void set_listen(int port);
    void set_hoste(const std::string& hoste);
    void set_server_name(const std::string& name);
    void set_root(const std::string& root);
    void add_error_page(int code, const std::string& page);
    void set_client_max_body_size(size_t size);
    void add_location(const Location& location);
    void cheak_location();

    // Getters
    int get_listen() const;
    std::string get_hoste() const;
    const std::vector <std::string>& get_server_names() const;
    const std::string& get_root() const;
    const std::map<int, std::string>& get_error_pages() const;
    size_t get_client_max_body_size() const;
    const std::vector<Location>& get_locations() const;

private:
    int listen_;
    std::string hoste_;
    std::vector<std::string> server_names_;
    std::string root_;
    std::map<int, std::string> error_pages_;
    size_t client_max_body_size_;
    std::vector<Location> locations_;
};

class Config {
public:
    Config();
    void parse(const std::string& filename);
    const std::vector<Server>& get_servers() const;

private:
    void parse_server_block(std::string& line, std::vector<std::string> &V);
    void parse_syntax(std::vector<std::string> &V);
    void parse_server_syntax(std::vector<std::string>::iterator &it, std::vector<std::string> &V, bool& server_b);
    void parse_location_syntax(std::vector<std::string>::iterator &i, std::vector<std::string> &V, bool& server_b);
    void parse_location_block(std::vector<std::string> &V, std::string& line, Server& server, bool& loaction_b, 
                              std::vector<std::string>::iterator &i);
    void parse_directive(std::string& line, std::vector<std::string> &V, bool& server_b, 
                         std::vector<std::string>::iterator &it);

    std::string trim_whitespace(const std::string& str);
    std::vector<std::string> tokenize_directive(const std::string& str);
    size_t parse_size_with_suffix(const std::string& str);
    bool is_valid_directive(const std::string& directive, size_t min_args, size_t max_args);

    std::vector<Server> servers_;
};
