/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvoltorb <cvoltorb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 17:55:25 by cvoltorb          #+#    #+#             */
/*   Updated: 2020/08/02 19:23:28 by cvoltorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_options	ft_init_opts(int count)
{
	t_options	opts;

	opts.width = 0;
	opts.prec = 0;
	opts.count_already_printed = count;
	opts.e_pow = 0;
	opts.flags = 0;
	opts.subspec = 0;
	opts.spec = 0;
	return (opts);
}

int			ft_print_argument(va_list params, t_options *opts)
{
	if (opts->spec == 'c' || opts->spec == 'C')
		return (ft_print_char(params, opts));
	if (opts->spec == 's')
		return (ft_print_str(params, opts));
	if (opts->spec == 'd' || opts->spec == 'i')
		return (ft_print_int(params, opts));
	if (opts->spec == 'p' || opts->spec == 'u' || opts->spec == 'o' || \
			opts->spec == 'x' || opts->spec == 'X')
		return (ft_print_ptr_uns_hex_oct(params, opts));
	if (opts->spec == 'f' || opts->spec == 'F' || \
			opts->spec == 'e' || opts->spec == 'E')
		return (ft_print_float_scientific(params, opts));
	if (opts->spec == 'n')
		return (ft_save_count_printed(params, opts));
	if (opts->spec == '%')
		return (ft_print_percent(opts));
	return (0);
}

int			ft_printf(const char *format, ...)
{
	va_list	params;
	int		count;

	if (!format)
		return (-1);
	count = 0;
	va_start(params, format);
	count += ft_pars_format(params, format);
	va_end(params);
	return (count);
}
