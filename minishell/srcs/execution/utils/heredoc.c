/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:16:16 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/04 13:04:06 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

char	*expand_heredoc(char *line, int *bad_sub)
{
	char	*expanded;

	if (check_curly_braces(line))
	{
		*bad_sub = 1;
		g_vars.exit_status = 1;
		return (line);
	}
	expanded = substitute_var(line);
	free(line);
	return (expanded);
}

int	read_heredoc(char *del, char **line)
{
	*line = readline(">");
	if (g_vars.sig_c == 1)
		return (g_vars.sig_c = 2, 1);
	if (NULL == *line)
		return (
			printf("here-document : delimited by end-of-file (wanted `%s')\n",
				del), 1);
	if (!ft_strcmp(*line, del))
	{
		free(*line);
		return (1);
	}
	return (0);
}

int	treat_heredoc(char *del, int fd, int sub_var)
{
	char	*line;
	int		bad_sub;

	bad_sub = 0;
	if (!del)
	{
		del = ft_strdup("");
		sub_var = 1;
	}
	signal(SIGINT, heredoc_sig);
	while (1)
	{
		if (read_heredoc(del, &line))
			break ;
		if (sub_var == 0)
			line = expand_heredoc(line, &bad_sub);
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
	}
	signal(SIGINT, sig_handler);
	free(del);
	if (bad_sub)
		return (ft_putstr_fd(" : bad substitution\n", 2), 1);
	return (0);
}

char	*open_tmp_file(int *fd)
{
	char	*file_name;
	char	*tmp;

	fd[0] = -1;
	fd[1] = -1;
	tmp = ft_itoa(g_vars.tmp_file++);
	file_name = ft_strjoin("/tmp/minishell_", tmp);
	free(tmp);
	while (file_name && access(file_name, F_OK) == 0)
	{
		free(file_name);
		tmp = ft_itoa(g_vars.tmp_file++);
		file_name = ft_strjoin("/tmp/minishell_", tmp);
		free(tmp);
	}
	if (NULL == file_name)
		return (ft_putstr_fd("Error creating /tmp/file\n", 2), NULL);
	fd[1] = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (-1 == fd[1])
		return (ft_putstr_fd("Error opening /tmp/file\n", 2), file_name);
	return (file_name);
}

int	open_heredoc(t_redirection *red, char *del, char *file_name)
{
	int		sub_var;
	int		fd[2];

	if (g_vars.sig_c == 2)
		return (1);
	sub_var = ft_char_in('\'', red->file_name) + ft_char_in('"',
			red->file_name);
	file_name = open_tmp_file(fd);
	if (NULL == file_name || fd[1] == -1)
		return (1);
	del = trim_str(ft_strdup(red->file_name));
	if (treat_heredoc(del, fd[1], sub_var))
		return (free(file_name), 1);
	close(fd[1]);
	fd[0] = open(file_name, O_RDONLY);
	free(file_name);
	if (fd[0] == -1)
		return (ft_putstr_fd("Error opening /tmp/file\n", 2), 1);
	if (g_vars.sig_c == 2)
	{
		close(fd[0]);
		return (red->fd = 0, 1);
	}
	red->fd = fd[0];
	return (0);
}
