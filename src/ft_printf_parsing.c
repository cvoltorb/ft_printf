/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvoltorb <cvoltorb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 17:59:15 by cvoltorb          #+#    #+#             */
/*   Updated: 2020/08/02 19:23:57 by cvoltorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static char	ft_pars_flags(char c, char flags)
{
	if (c == '-' && !(16 & flags))
		flags += 16;
	else if (c == '+' && !(8 & flags))
		flags += 8;
	else if (c == ' ' && !(4 & flags))
		flags += 4;
	else if (c == '#' && !(2 & flags))
		flags += 2;
	else if (c == '0' && !(1 & flags))
		flags += 1;
	return (flags);
}

static int	ft_pars_width(va_list params, const char *format, int *i,
												t_options *opts)
{
	int		width;

	width = 0;
	if (format[*i] == '*')
	{
		if ((width = va_arg(params, int)) < 0)
		{
			width *= -1;
			opts->flags = opts->flags | 16;
			opts->flags = opts->flags & 30;
		}
		*i += 1;
	}
	else
	{
		while (format[*i] >= '0' && format[*i] <= '9')
		{
			if ((width * 10) < width)
				return (-1);
			width = width * 10 + format[*i] - '0';
			*i += 1;
		}
	}
	return (width);
}

static int	ft_pars_prec(va_list params, const char *format, int *i,
													t_options *opts)
{
	int		prec;

	prec = 0;
	opts->flags += 32;
	if (format[*i] == '*')
	{
		if ((prec = va_arg(params, int)) < 0)
		{
			prec = 0;
			opts->flags -= 32;
		}
		*i += 1;
	}
	else
	{
		while (format[*i] >= '0' && format[*i] <= '9')
		{
			if ((prec * 10) < prec)
				return (-1);
			prec = prec * 10 + format[*i] - '0';
			*i += 1;
		}
	}
	return (prec);
}

static int	ft_pars_opts(va_list params, const char *format, int *i, int count)
{
	t_options	opts;

	opts = ft_init_opts(count);
	*i += 1;
	while (ft_printf_strchr("-+ #0", format[*i]))
	{
		if (!(opts.flags = ft_pars_flags(format[*i], opts.flags)))
			return (-1);
		*i += 1;
	}
	if (format[*i] == '*' || (format[*i] >= '0' && format[*i] <= '9'))
	{
		if ((opts.width = ft_pars_width(params, format, i, &opts)) < 0)
			return (-1);
	}
	if (format[*i] == '.' && format[*i + 1])
	{
		*i += 1;
		if ((opts.prec = ft_pars_prec(params, format, i, &opts)) < 0)
			return (-1);
	}
	opts.spec = ft_isspec(format, i, &opts);
	return (opts.spec != 0) ? (ft_print_argument(params, &opts)) : (-1);
}

int			ft_pars_format(va_list params, const char *format)
{
	int		i;
	int		count;
	int		tmp;

	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] != '%')
			count += ft_putchar_count(format[i], 1);
		else if (format[i] == '%' && format[i + 1])
		{
			if ((tmp = ft_pars_opts(params, format, &i, count)) < 0)
				return (-1);
			count += tmp;
		}
		else
			return (-1);
		i++;
	}
	return (count);
}
