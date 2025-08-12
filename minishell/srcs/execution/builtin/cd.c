/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:28:29 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/06/28 09:28:37 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

int	cd_home(char *home)
{
	home = get_env_v1("HOME");
	if (NULL == home)
		return (ft_putstr_fd("cd: HOME not set\n", 2), g_vars.exit_status = 1,
			1);
	if (chdir(home))
		return (ft_perror(home, " : No such file or directory\n", NULL),
			g_vars.exit_status = 1, 1);
	return (g_vars.exit_status = 0, 0);
}

/*
 *cd ✅
 */
int	cd(char **split)
{
	char	*home;
	char	*full_path;

	home = NULL;
	if (split_len(split) > 1)
		return (ft_putstr_fd("cd: too many arguments\n", 2),
			g_vars.exit_status = 1, 1);
	if (NULL == split || NULL == split[0] || (split[0] && split[0][0] == '~'
		&& !split[0][1]))
		return (cd_home(home));
	if (split[0][0] == '/')
	{
		if (chdir(split[0]))
			return (perror("cd "), g_vars.exit_status = 1, 1);
		return (g_vars.exit_status = 0, 0);
	}
	home = getcwd(NULL, 0);
	full_path = ft_strjoin_prefixed(home, '/', split[0]);
	free(home);
	if (NULL == full_path)
		return (g_vars.exit_status = 1, 1);
	if (chdir(full_path))
		return (perror("cd "), free(full_path), g_vars.exit_status = 1, 1);
	return (free(full_path), g_vars.exit_status = 0, 0);
}

void	exec_cd(char **split)
{
	char	*old_pwd;
	char	*pwd;

	if (get_env_v1("PWD") == NULL)
		old_pwd = getcwd(NULL, 0);
	else
		old_pwd = ft_strdup(get_env_v1("PWD"));
	if (cd(split) == 0 && old_pwd != NULL)
	{
		if (!ft_env_replace("OLDPWD", old_pwd))
			add_to_env(ft_strdup("OLDPWD"), ft_strdup(old_pwd), 1);
		pwd = getcwd(NULL, 0);
		if (pwd != NULL && !ft_env_replace("PWD", pwd))
			add_to_env(ft_strdup("PWD"), ft_strdup(pwd), 1);
		free(pwd);
	}
	free(old_pwd);
}
