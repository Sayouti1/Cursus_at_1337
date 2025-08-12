/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:29:37 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/06/28 09:29:39 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

int	ft_str_isdigit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		++i;
	if (!str[i])
		return (0);
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

int	fix_env(void)
{
	char	*tmp;

	tmp = get_env_v1("PWD");
	if (NULL == tmp)
	{
		tmp = getcwd(NULL, 0);
		add_to_env(ft_strdup("PWD"), ft_strdup(tmp), 1);
		free(tmp);
	}
	tmp = NULL;
	tmp = get_env_v1("OLDPWD");
	if (NULL == tmp)
		add_to_env(ft_strdup("OLDPWD"), NULL, 0);
	return (0);
}

int	fix_shlvl(void)
{
	char	*level;
	int		val;

	fix_env();
	level = get_env_v1("SHLVL");
	if (NULL == level)
		return (add_to_env(ft_strdup("SHLVL"), ft_strdup("1"), 1), 1);
	if (!ft_str_isdigit(level))
		return (ft_env_replace("SHLVL", "1"), 1);
	val = ft_atoi(level);
	if (val < 0)
		val = 0;
	else if (++val >= 1000)
	{
		ft_putstr_fd("minishell: warning: shell level too high\n", 2);
		val = 1;
	}
	level = ft_itoa(val);
	ft_env_replace("SHLVL", level);
	free(level);
	return (0);
}
