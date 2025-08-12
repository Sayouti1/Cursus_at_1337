/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:30:36 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/06/28 09:30:38 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

/*
 *pwd ✅
 */
int	pwd(void)
{
	char	*curr_dir;

	curr_dir = getcwd(NULL, 0);
	if (NULL == curr_dir && NULL != get_env_v1("PWD"))
		return (printf("%s\n", get_env_v1("PWD")), g_vars.exit_status = 0, 1);
	if (NULL == curr_dir)
		return (ft_putstr_fd("pwd: error retrieving current directory: getcwd:"
				"cannot access parent directories:"
				" No such file or directory\n", 2),
			g_vars.exit_status = 1, 1);
	printf("%s\n", curr_dir);
	free(curr_dir);
	return (g_vars.exit_status = 0, 0);
}

/*
 * ✅ return bin PATH as a char **
 * from PATH = /usr/bin:/bin:/sbin:....
 * to "/usr/bin",  "/bin", "/sbin" etc
 */
char	**get_path_dirs(void)
{
	char	*path;
	char	**dirs;

	path = get_env_v1("PATH");
	if (NULL == path)
		return (g_vars.exit_status = 127, NULL);
	dirs = ft_split(path, ':');
	if (NULL == dirs)
		return (g_vars.exit_status = 127, NULL);
	return (dirs);
}

/*
 * First , I check if the binary in exis
 * to get the correct absolute path of
 * the binary to be executed in PATH variable!!
 * ✅
 */
char	*bin_in_path(char *bin)
{
	char	**dirs;
	char	*path;
	int		i;

	dirs = get_path_dirs();
	if (NULL == dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		path = ft_strjoin_prefixed(dirs[i], '/', bin);
		if (NULL == path)
			return (free_split(dirs), g_vars.exit_status = 1, NULL);
		if (!access(path, F_OK))
			return (free_split(dirs), path);
		free(path);
		++i;
	}
	return (free_split(dirs), NULL);
}
