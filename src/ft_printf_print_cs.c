/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_cs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvoltorb <cvoltorb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 18:00:54 by cvoltorb          #+#    #+#             */
/*   Updated: 2020/08/02 19:19:20 by cvoltorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../ft_printf.h"

int				ft_print_char(va_list params, t_options *opts)
{
	int		count;
	char	val;

	count = 0;
	val = va_arg(params, int);
	if ((opts->subspec & 8) && val < 0)
		return (-1);
	if (opts->width > 1)
	{
		if (opts->flags & 16)
		{
			count += ft_putchar_count(val, 1);
			while (count < opts->width)
				count += ft_putchar_count(' ', 1);
			return (count);
		}
		while (count < opts->width - 1)
			count += ft_putchar_count(' ', 1);
	}
	count += ft_putchar_count(val, 1);
	return (count);
}

static int		ft_print_assist_str(char *str, t_options *opts)
{
	int		count;
	int		len;
	int		spaces;
	char	*tmp;

	count = 0;
	len = (int)ft_printf_strlen(str);
	tmp = str;
	if ((opts->flags & 32) && len > opts->prec)
	{
		if (!(tmp = malloc(sizeof(char) * opts->prec + 1)))
			return (-1);
		ft_printf_strlcpy(tmp, str, opts->prec + 1);
	}
	spaces = (len > opts->prec && (opts->flags & 32)) ? \
			opts->width - opts->prec : opts->width - len;
	count += (opts->flags & 16) ? ft_putstr_count(tmp, 1) : 0;
	while (spaces-- > 0)
		count += ft_putchar_count(' ', 1);
	count += (!(opts->flags & 16)) ? ft_putstr_count(tmp, 1) : 0;
	if ((opts->flags & 32) && len > opts->prec)
		free(tmp);
	return (count);
}

int				ft_print_str(va_list params, t_options *opts)
{
	int		count;
	char	*val;
	char	*str;

	str = NULL;
	val = va_arg(params, char*);
	str = (!val) ? ft_printf_strdup("(null)") : val;
	if (!str)
		return (-1);
	count = ft_print_assist_str(str, opts);
	!val ? free(str) : 0;
	return (count);
}
