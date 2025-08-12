/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:24:18 by aes-sayo          #+#    #+#             */
/*   Updated: 2023/11/23 04:12:58 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*pdst;
	unsigned char	*psrc;

	pdst = (unsigned char *)dst;
	psrc = (unsigned char *)src;
	if (dst == src || len == 0)
		return (dst);
	if (dst > src && src + len > dst)
	{
		pdst += len - 1;
		psrc += len - 1;
		while (len-- > 0)
			*pdst-- = *psrc--;
		return (dst);
	}
	return (ft_memcpy(dst, src, len));
}
