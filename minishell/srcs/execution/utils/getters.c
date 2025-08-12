/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:30:00 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/04 13:04:06 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

/*
 * ✅
 */
char	*get_full_path(char *cmd, char *curr_dir)
{
	char	*full_path;

	if (NULL == cmd || cmd[0] == '\0')
		return (NULL);
	if (cmd[0] == '.' && cmd[1] == '/')
		full_path = ft_strjoin_prefixed(curr_dir, '/', cmd);
	else if (cmd[0] == '/')
		full_path = ft_strdup(cmd);
	else
		full_path = bin_in_path(cmd);
	return (full_path);
}

/*
 * ✅
 */
char	**get_exec_arg(char *fullpath, char *split)
{
	char	**exec_arg;
	char	**arg;
	int		i;

	arg = ft_split_del(split, " \t");
	i = 0;
	while (arg && arg[i])
		i++;
	exec_arg = (char **)malloc(sizeof(char *) * (i + 2));
	if (NULL == exec_arg)
		return (g_vars.exit_status = 1, NULL);
	exec_arg[0] = ft_strdup(fullpath);
	i = 0;
	while (arg && arg[i])
	{
		exec_arg[i + 1] = arg[i];
		++i;
	}
	exec_arg[i + 1] = NULL;
	return (exec_arg);
}

char	*get_dollar_key_v1(char *line, int *i)
{
	int		j;
	int		k;
	char	*key;

	j = *i + 1;
	if (NULL == line)
		return (NULL);
	if (!line[j] || ft_isdigit(line[j]) || ft_char_in(line[j],
			" \n\t$\'\"\n{}><@+-/*"))
		return ((*i)++, (*i)++, NULL);
	while (line[j] && !ft_char_in(line[j], " \t$\'\"\n{}><")
		&& (ft_isalnum(line[j]) || line[j] == '_'))
		j++;
	key = (char *)malloc(sizeof(char) * (j - *i));
	if (NULL == key)
		return (NULL);
	k = 0;
	(*i)++;
	while (*i < j && line[*i])
		key[k++] = line[(*i)++];
	key[k] = '\0';
	return (key);
}

t_redirection	*get_last_red(t_redirection *red)
{
	while (red && red->next)
		red = red->next;
	return (red);
}
