/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_fe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvoltorb <cvoltorb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 18:02:36 by cvoltorb          #+#    #+#             */
/*   Updated: 2020/08/02 19:21:11 by cvoltorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../ft_printf.h"

static long double	round_float_and_conv_to_sci(long double val,
												t_options *opts)
{
	int			i;
	long double	tmp;

	if (opts->spec == 'e' || opts->spec == 'E')
	{
		tmp = (val < 0) ? -val : val;
		while (tmp >= 10)
		{
			tmp /= 10;
			opts->e_pow++;
		}
		while (val && tmp < 1)
		{
			tmp *= 10;
			opts->e_pow--;
		}
		val = (val < 0) ? -tmp : tmp;
	}
	i = 0;
	tmp = 0.5;
	opts->prec = (!(opts->flags & 32)) ? 6 : opts->prec;
	while (i++ < opts->prec)
		tmp /= 10;
	return (val < 0) ? (val - tmp) : (val + tmp);
}

static int			ft_print_fract(t_options *opts, long double val)
{
	int			count;

	count = 0;
	if (opts->prec || (opts->flags & 2))
		count += ft_putchar_count('.', 1);
	if (opts->prec)
	{
		val = (val < 0) ? -(val - (ssize_t)val) : val - (ssize_t)val;
		while (count <= opts->prec)
		{
			val *= 10;
			count += ft_putchar_count((int)val + '0', 1);
			val -= (int)val;
		}
	}
	count += (opts->spec == 'e' || opts->spec == 'E') ? \
			ft_print_e_pow(opts) : 0;
	return (count);
}

static int			ft_flag_minus_zero(t_options *opts, char *s,
										long double val, int len)
{
	int			count;
	int			spaces;

	count = 0;
	count += ft_print_sign(opts, val);
	spaces = (opts->prec) ? opts->width - count - len - opts->prec - 1 : \
			opts->width - len - count;
	spaces -= ((opts->flags & 2) && (opts->prec == 0)) ? 1 : 0;
	spaces -= (opts->spec == 'e' || opts->spec == 'E') ? 4 : 0;
	if (opts->flags & 16)
	{
		count += ft_putstr_count(s, 1);
		count += ft_print_fract(opts, val);
		while (spaces-- > 0)
			count += ft_putchar_count(' ', 1);
	}
	else if (opts->flags & 1)
	{
		while (spaces-- > 0)
			count += ft_putchar_count('0', 1);
		count += ft_putstr_count(s, 1);
		count += ft_print_fract(opts, val);
	}
	return (count);
}

static int			ft_other_cases(t_options *opts, char *s, long double val, \
		int len)
{
	int			count;
	int			spaces;

	count = 0;
	spaces = (opts->prec) ? opts->width - len - opts->prec - 1 : \
			opts->width - len;
	spaces -= ((opts->flags & 12) || val < 0) ? 1 : 0;
	spaces -= ((opts->flags & 2) && (opts->prec == 0)) ? 1 : 0;
	spaces -= (opts->spec == 'e' || opts->spec == 'E') ? 4 : 0;
	while (spaces-- > 0)
		count += ft_putchar_count(' ', 1);
	count += ft_print_sign(opts, val);
	count += ft_putstr_count(s, 1);
	count += ft_print_fract(opts, val);
	return (count);
}

int					ft_print_float_scientific(va_list params, t_options *opts)
{
	int			count;
	int			len_int_part;
	long double	val;
	char		*s;

	count = 0;
	val = (opts->subspec & 4) ? va_arg(params, long double) :
										va_arg(params, double);
	val = round_float_and_conv_to_sci(val, opts);
	s = (val < 0 && !(ssize_t)val) ? \
		ft_printf_strdup("-0") : ft_llitoa_base((ssize_t)val, 10);
	if (!s)
		return (-1);
	len_int_part = (int)ft_printf_strlen(s);
	len_int_part -= (val < 0) ? 1 : 0;
	s += (val < 0) ? 1 : 0;
	if ((opts->flags & 16) || (opts->flags & 1))
		count = ft_flag_minus_zero(opts, s, val, len_int_part);
	else
		count = ft_other_cases(opts, s, val, len_int_part);
	(val < 0) ? free(--s) : free(s);
	return (count);
}
