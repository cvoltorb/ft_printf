/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_puxo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvoltorb <cvoltorb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 18:04:12 by cvoltorb          #+#    #+#             */
/*   Updated: 2020/08/02 19:58:39 by cvoltorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../ft_printf.h"

static int		ft_print_prefix(t_options *opts, size_t val)
{
	if (opts->spec == 'p' || ((opts->spec == 'x') && (opts->flags & 2) && val))
		return (ft_putstr_count("0x", 1));
	if ((opts->spec == 'X') && (opts->flags & 2) && val)
		return (ft_putstr_count("0X", 1));
	if (opts->spec == 'o' && (opts->flags & 2))
	{
		opts->prec -= (opts->prec) ? 1 : 0;
		return (ft_putchar_count('0', 1));
	}
	return (0);
}

static int		ft_flag_minus_or_zero(t_options *opts, char *s,
												int val, int len)
{
	int		count;

	count = 0;
	if (opts->flags & 16)
	{
		count += ft_print_prefix(opts, val);
		while (opts->prec > len)
			opts->prec -= (count += ft_putchar_count('0', 1)) ? 1 : 0;
		count += (!val && ((((opts->flags & 32) && !opts->prec)) || \
		((opts->spec == 'o' && ((opts->flags & 3) == 2) && !opts->prec)))) ? \
				0 : ft_putstr_count(s, 1);
		while (count < opts->width)
			count += ft_putchar_count(' ', 1);
	}
	else if ((opts->flags & 1) && !(opts->flags & 32))
	{
		count += ft_print_prefix(opts, val);
		while (count < opts->width - len)
			count += ft_putchar_count('0', 1);
		count += (!val && ((((opts->flags & 32) && !opts->prec)) || \
				((opts->spec == 'o' && ((opts->flags & 3) == 2))))) ? \
					0 : ft_putstr_count(s, 1);
	}
	return (count);
}

static int		ft_val_zero(t_options *opts, int len)
{
	int		count;
	int		spaces;

	count = 0;
	if (opts->spec != 'p' && (opts->flags & 12))
		opts->width--;
	if (opts->spec == 'p')
		opts->width -= 2;
	if (opts->prec)
		spaces = opts->width - opts->prec;
	else if (!(opts->flags & 32))
		spaces = opts->width - len;
	else
		spaces = opts->width;
	spaces -= (opts->spec == 'o' && ((opts->flags & 34) == 34) && \
			!opts->prec) ? 1 : 0;
	while (count < spaces)
		count += ft_putchar_count(' ', 1);
	count += ft_print_prefix(opts, 0);
	while (opts->prec-- >= len)
		count += ft_putchar_count('0', 1);
	count += (!(opts->flags & 32) && (!(opts->spec == 'o' && \
					(opts->flags & 34)))) ? ft_putchar_count('0', 1) : 0;
	return (count);
}

static int		ft_other_cases(t_options *opts, char *s, int val, int len)
{
	int		count;

	count = 0;
	opts->prec = (len > opts->prec) ? len : opts->prec;
	if ((opts->spec != 'p' && (opts->flags & 12 || val < 0)) || \
			(opts->spec == 'o' && (opts->flags & 2) && opts->prec == len))
		opts->width--;
	if (opts->spec == 'p' || \
			((opts->spec == 'x' || opts->spec == 'X') && (opts->flags & 2)))
		opts->width -= 2;
	while (count < opts->width - opts->prec)
		count += ft_putchar_count(' ', 1);
	count += ft_print_prefix(opts, val);
	while (opts->prec-- > len)
		count += ft_putchar_count('0', 1);
	count += ft_putstr_count(s, 1);
	return (count);
}

int				ft_print_ptr_uns_hex_oct(va_list params, t_options *opts)
{
	int				count;
	size_t			val;
	char			*s;
	int				len;

	count = 0;
	val = ft_check_u_o_x_subspec(params, opts);
	if (opts->spec == 'u')
		s = ft_ullitoa_base(val, 10);
	else if (opts->spec == 'o')
		s = ft_ullitoa_base(val, 8);
	else if (opts->spec == 'p' || opts->spec == 'x' || opts->spec == 'X')
		s = ft_ullitoa_base(val, 16);
	s = (opts->spec == 'X') ? ft_strupper(s) : s;
	if (!s)
		return (-1);
	len = (int)ft_printf_strlen(s);
	if (opts->flags & 16 || ((opts->flags & 1) && !(opts->flags & 32)))
		count = ft_flag_minus_or_zero(opts, s, val, len);
	else if (!val)
		count = ft_val_zero(opts, len);
	else
		count = ft_other_cases(opts, s, val, len);
	free(s);
	return (count);
}
