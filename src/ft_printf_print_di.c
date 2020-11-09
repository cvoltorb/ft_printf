/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_di.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvoltorb <cvoltorb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 18:01:40 by cvoltorb          #+#    #+#             */
/*   Updated: 2020/08/02 19:20:17 by cvoltorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../ft_printf.h"

static int		ft_flag_minus_zero(t_options *opts, char *s, ssize_t val,
																int len)
{
	int		count;

	count = 0;
	if (opts->flags & 16)
	{
		count += ft_print_sign(opts, val);
		while (opts->prec > len)
		{
			count += ft_putchar_count('0', 1);
			opts->prec--;
		}
		count += ((opts->flags & 32) && !opts->prec && !val) ? \
				0 : ft_putstr_count(s, 1);
		while (count < opts->width)
			count += ft_putchar_count(' ', 1);
	}
	else if ((opts->flags & 1) && !(opts->flags & 32))
	{
		count += ft_print_sign(opts, val);
		while (count < opts->width - len)
			count += ft_putchar_count('0', 1);
		count += ((opts->flags & 32) && !opts->prec && !val) ? \
				0 : ft_putstr_count(s, 1);
	}
	return (count);
}

static int		ft_val_zero(t_options *opts, ssize_t val, int len)
{
	int		count;
	int		spaces;

	count = 0;
	if (opts->flags & 12)
		opts->width--;
	if (opts->prec)
		spaces = opts->width - opts->prec;
	else if (!(opts->flags & 32))
		spaces = opts->width - len;
	else
		spaces = opts->width;
	while (count < spaces)
		count += ft_putchar_count(' ', 1);
	count += ft_print_sign(opts, val);
	while (opts->prec-- >= len)
		count += ft_putchar_count('0', 1);
	count += (!(opts->flags & 32)) ? ft_putchar_count('0', 1) : 0;
	return (count);
}

static int		ft_other_cases(t_options *opts, char *s, ssize_t val, int len)
{
	int		count;

	count = 0;
	opts->prec = (len > opts->prec) ? len : opts->prec;
	if (opts->flags & 12 || val < 0)
		opts->width--;
	while (count < opts->width - opts->prec)
		count += ft_putchar_count(' ', 1);
	count += ft_print_sign(opts, val);
	while (opts->prec-- > len)
		count += ft_putchar_count('0', 1);
	count += ft_putstr_count(s, 1);
	return (count);
}

int				ft_print_int(va_list params, t_options *opts)
{
	int		count;
	ssize_t	val;
	char	*s;
	int		len;

	if (opts->subspec & 12)
		val = (opts->subspec & 4) ? va_arg(params, long long) :
											va_arg(params, long);
	else if (opts->subspec & 3)
		val = (opts->subspec & 1) ? \
			(signed char)va_arg(params, int) : (short int)va_arg(params, int);
	else
		val = va_arg(params, int);
	s = ft_llitoa_base(val, 10);
	len = (int)ft_printf_strlen(s);
	len -= (val < 0) ? 1 : 0;
	s += (val < 0) ? 1 : 0;
	if (opts->flags & 16 || ((opts->flags & 1) && !(opts->flags & 32)))
		count = ft_flag_minus_zero(opts, s, val, len);
	else if (!val)
		count = ft_val_zero(opts, 0, len);
	else
		count = ft_other_cases(opts, s, val, len);
	(val < 0) ? free(--s) : free(s);
	return (count);
}
