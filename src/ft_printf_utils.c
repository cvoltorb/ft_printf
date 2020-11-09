/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvoltorb <cvoltorb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 18:06:04 by cvoltorb          #+#    #+#             */
/*   Updated: 2020/08/02 20:35:40 by cvoltorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../ft_printf.h"

int				ft_putchar_count(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int				ft_putstr_count(char *s, int fd)
{
	int		count;

	count = 0;
	while (*s)
		count += ft_putchar_count(*s++, fd);
	return (count);
}

size_t			ft_check_u_o_x_subspec(va_list params, t_options *opts)
{
	size_t	val;

	if (opts->spec == 'p')
		return (va_arg(params, size_t));
	if (opts->subspec & 12)
		val = (opts->subspec & 4) ? \
			va_arg(params, unsigned long long) : va_arg(params, unsigned long);
	else if (opts->subspec & 3 && opts->subspec != 'p')
		val = (opts->subspec & 1) ? \
			(unsigned char)va_arg(params, unsigned int) : \
			(unsigned short int)va_arg(params, unsigned int);
	else
		val = va_arg(params, unsigned int);
	return (val);
}

int				ft_print_sign(t_options *opts, long double val)
{
	if ((opts->flags & 12) && val >= 0)
		return (opts->flags & 8) ? \
		ft_putchar_count('+', 1) : ft_putchar_count(' ', 1);
	return (val < 0) ? ft_putchar_count('-', 1) : 0;
}

char			ft_isspec(const char *format, int *i, t_options *opts)
{
	if (!format[*i])
		return (0);
	if (format[*i] == 'L')
	{
		opts->subspec += 4;
		(*i)++;
	}
	else if (format[*i] == 'l')
	{
		opts->subspec = 8;
		(*i)++;
		if (format[(*i)++] == 'l')
			opts->subspec += 4;
		*i -= (opts->subspec & 4) ? 0 : 1;
	}
	else if (format[*i] == 'h')
	{
		(*i)++;
		opts->subspec = 2;
		if (format[(*i)++] == 'h')
			opts->subspec += 1;
		*i -= (opts->subspec & 1) ? 0 : 1;
	}
	return (ft_printf_strchr("cCspdiuoxXnfFgGeE%", format[*i])) ?
	format[*i] : 0;
}
