/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:15:44 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/12/28 19:19:10 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

double	normalize_angle(double angle_tofix)
{
	double	angle;

	angle = fmod(angle_tofix, 2 * PI);
	if (angle < 0)
		angle += 2 * PI;
	return (angle);
}
