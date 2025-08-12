/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:14:34 by aes-sayo          #+#    #+#             */
/*   Updated: 2023/12/06 18:14:39 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdlib.h>

int	ft_helper(char c, va_list ap);
int	ft_printf(const char *format, ...);
int	ft_puthex(unsigned int n, char x);
int	ft_pointer(unsigned long long ptr);

#endif
