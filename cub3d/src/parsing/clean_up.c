/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarda <hbarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 11:53:21 by hbarda            #+#    #+#             */
/*   Updated: 2024/12/29 15:44:42 by hbarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr && arr[++i])
		free(arr[i]);
	free(arr);
}

void	free_parse_allocated(t_data *data, char **parts, char *message)
{
	if (data->trimmed)
		free(data->trimmed);
	if (parts)
		free_array(parts);
	ft_free_all(message, data, 1);
}
