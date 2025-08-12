/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:33:50 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/09/19 14:54:49 by aez-zoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# include "../Libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum s_token_type
{
	TOKEN_WORD, // using for the cmd argm 0
	TOKEN_PIPE, // using for the pipe cmd 1
	TOKEN_REDIR_IN, // using like < 2
	TOKEN_REDIR_OUT, // using like > 3
	TOKEN_REDIR_APPEND, // using for >> 4
	TOKEN_REDIR_HEREDOC, // using for <<
}								t_token_type;

typedef struct s_token
{
	t_token_type				type;
	char						*value;
	struct s_token				*next;
}								t_token;

typedef struct s_env
{
	char						*key;
	char						*value;
	int							to_export;
	struct s_env				*next;
}								t_env;

typedef struct s_garbage_collector
{
	void						*str;
	struct s_garbage_collector	*next;
}								t_garbage_collector;

typedef struct s_fd_collectors
{
	int							fd;
	struct s_fd_collectors		*next;
}								t_fd_collectors;

typedef struct s_command	t_command;

typedef struct s_global_vars
{
	t_env						*env;
	char						**envp;
	int							parent;
	int							exit_status;
	int							sig_c;
	int							tmp_file;
	int							std_in;
	int							std_out;
	t_command					*cmd;
	t_token						*token;
	t_garbage_collector			*garbage_coll;
	t_fd_collectors				*fd_collectors;

}								t_global_vars;

extern t_global_vars		g_vars;

enum	e_redirection
{
	OUTPUT,
	APPEND,
	INPUT,
	HEREDOC
};

typedef struct s_redirection
{
	int						type;
	char					*file_name;
	int						fd;
	struct s_redirection	*next;

}								t_redirection;

typedef struct s_command
{
	char						*command;
	char						**args;
	t_redirection				*redirection;
	int							fd_in;
	int							fd_out;
	struct s_command			*next;
	struct s_command			*prev;
}								t_command;

// ---------------------------- PARSING -----------------
int								is_split(char *data);
void							close_file_ds(void);
void							update_quote_counts(char c, int *s_q_count,
									int *d_q_count);
char							*skip_spaces(char *input);
int								is_space(char *line);
int								check_line(char **line);
int								is_invalid_op(char **input);
int								is_syntaxe_cmd(char *line);
int								is_closed_qoute(char *line);
int								is_invalid_redirection(char *line);
int								is_error_misplaced(char *line);
int								is_error_logic(char *line);
// -----------------------------LEXER----------------------
void							update_quote_status(char c, int *is_quote,
									char *qoute_char);
t_token							*new_token(t_token_type type, char *value);
void							add_token_to_list(t_token **tokens,
									t_token *new_token);
void							free_token(t_token *tokens);
void							word_to_token(char **start, char **line,
									t_token **tokens);
t_token							*token_line(char *line);
void							do_words(char **line, t_token **tokens);
void							do_speacil_chars(char **line, t_token **tokens);
char							*ft_strndup(char *src, size_t n);
int								_strcmp(char *s_1, char *s_2, char *s_3);
int								sizeof_str(char *str, char end);
size_t							ft_strnlen(const char *s, size_t maxlen);
void							word_to_token(char **start, char **line,
									t_token **tokens);
char							*substitute_var1(char *str);
t_token							*expand_var(t_token *tokens);
int								ft_ambiguous_err(t_token *tokens);
void							helper_func(t_token *token);
void							free_words(char **words);
char							*handle_dollar_sign(char *str, int *i,
									char *concat, int in_quotes);
int								error_heredoc(t_token *token);
int								handle_tokens(t_token **tokens,
									t_token **ntokens);
void							process_line(char *line, t_command **command);
t_token							*check_and_token(char *line);
void							print_commands(t_command *command);
void							ft_print_token(t_token *tokens);
char							*surround_quotes(char *str);
int								closing_found(char *str, int start, char c);
char							**split_expand(char const *s);
int								is_trim(char c);

// ------------------------------------------------------

/***************************_______EXECUTION_______*************************/

int								cd_home(char *home);
int								cd(char **split);
void							exec_cd(char **split);

int								n_option(int *i, char **str);
void							ft_echo(char **str);

t_env							*new_node(char *key, char *value,
									int to_export);
int								env_len(t_env *env);
char							**get_env_array(int i, char *key);

int								add_to_env(char *key, char *value,
									int to_export);
void							init_env(void);
char							*get_env_v1(char *key);
void							ft_env(void);
int								ft_env_replace(char *key, char *new_value);

void							exec_echo(t_command *cmd);
void							exec_export(t_command *cmd);
void							exec_env(t_command *cmd);
void							exec_unset(t_command *cmd);
void							execute_built_in(t_command *cmd, int piped);

int								exit_overflow(char *arg);
int								ft_exit(char **arg, int piped);

int								ft_concat_env_var(char *var, char *tmp, int i,
									int x);
int								is_not_valid(char *var);
int								ft_export(char **var);
void							ft_print_export(void);
int								fix_shlvl(void);

int								pwd(void);
char							**get_path_dirs(void);
char							*bin_in_path(char *bin);

void							search_and_delete(t_env *iter, char *split);
int								ft_unset(char **key);

int								built_in(char *str);
int								check_redirection(t_command *cmd);
int								is_directory(char *path);

void							dup2_and_close(int new_fd, int old_fd);
int								execute_bin(t_command *cmd);
int								execute_bin_pipe(t_command *cmd);
void							redirection_exec(t_command *cmd);
void							execute_command(t_command *cmd, int piped);
int								fix_command_path(t_command *cmd);

void							free_env(void);
void							delete_env(t_env *env);
void							free_split(char **arr);
void							free_redirection(t_redirection *red);
int								reset_fd(void);
void							free_cmds(t_command *cmd);

void							free_cmd_token_garbage(void);
int								collect_garbage(void *to_add);
void							free_garbage(void);

char							*get_full_path(char *cmd, char *curr_dir);
char							**get_exec_arg(char *fullpath, char *split);
char							*get_dollar_key_v1(char *line, int *i);
t_redirection					*get_last_red(t_redirection *red);

char							*substitute_var(char *str);
int								check_curly_braces(char *str);

char							*expand_heredoc(char *line, int *bad_sub);
int								read_heredoc(char *del, char **line);
int								treat_heredoc(char *del, int fd, int sub_var);
int								open_heredoc(t_redirection *red, char *del,
									char *file_name);

int								list_len(t_command *head);
int								split_len(char **split);

void							not_first_command(t_command *cmd, int prev_in);
void							not_last_command(t_command *cmd, int curr_out);
int								init_commands_fds(t_command *cmd, int len,
									int *curr_pipes, int *prev_pipes);
int								execute_pipes(int len, int i, t_command *cmd,
									int *pids);
void							process_command(t_command *command);

void							add_to_fds(int val);
void							close_file_ds(void);
void							close_fds(t_command *cmd);
void							swap_pipes(int *curr_pipes, int *prev_pipes);

char							*file_name_permissions(char *file_name,
									int type, int create_file);
t_redirection					*new_redirection(int type, char *file_name,
									int fd, int create_file);
t_command						*new_command(char *command, char **args,
									t_redirection *redirection);
void							add_to_cmds(t_command **head, t_command *cmd);
char							**fix_command_arg(t_command *cmd);

int								set_exit_status(int n);

void							sig_handler(int sig);
void							heredoc_sig(int sig);
void							sig_init(void);

int								ft_char_in(char c, char *str);
char							**ft_split_del(char const *s, char *del);

char							*ft_strjoin_prefixed(char *s1, char c,
									char *s2);
char							*char_concat(char *line, char c);
char							*string_concat(char *line, char *str);
int								ft_perror(char *s1, char *s2, char *s3);

char							*trim_str(char *str);
void							remove_quotes(t_command *cmd);
int								token_type_to_cmd_type(t_token_type type);
void							*ft_realloc(void *ptr, size_t old_size,
									size_t new_size);
int								has_null(t_redirection *red);

char							**add_to_list(char **old_list, char *to_add);
t_redirection					*add_redirection(t_redirection *red,
									t_token **token);
void							copy_cmd_args(t_token **token, t_command **cmd);
int								token_to_command_convert(t_token *token,
									t_command **cmd);

int								ft_isspace(char c);
int								str_isdigit(char *str);

int								ft_strcmp(char *s1, char *s2);
char							**split_on_two(char *line, char *del);

void							init_g_vars(char **envp);
void							update_under_s(t_command *command);
#endif
