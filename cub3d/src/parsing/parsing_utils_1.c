/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarda <hbarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 09:38:58 by hbarda            #+#    #+#             */
/*   Updated: 2024/12/29 09:23:03 by hbarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	**init_int_arr(int *lines_len, int arr_len)
{
	int	i;
	int	**arr;

	i = -1;
	arr = malloc(sizeof(int *) * arr_len);
	if (!arr)
		return (NULL);
	while (++i < arr_len)
	{
		arr[i] = ft_calloc(lines_len[i], sizeof(int));
		if (!arr[i])
		{
			while (--i >= 0)
				free(arr[i]);
			free(arr);
			return (NULL);
		}
	}
	return (arr);
}

char	**copy_array(char **array, int array_len)
{
	int		i;
	char	**cpy_array;

	i = -1;
	if (array_len <= 0)
		return (NULL);
	cpy_array = (char **)ft_calloc(sizeof(char *), array_len + 1);
	if (!cpy_array)
		return (NULL);
	while (++i < array_len)
		cpy_array[i] = ft_strdup(array[i]);
	return (cpy_array);
}

int	arr_len(char **array)
{
	int	i;

	i = -1;
	if (!array)
		return (0);
	while (array[++i])
		;
	return (i);
}
