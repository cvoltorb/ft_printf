/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_percent.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvoltorb <cvoltorb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 18:05:33 by cvoltorb          #+#    #+#             */
/*   Updated: 2020/08/02 19:21:21 by cvoltorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int				ft_print_percent(t_options *opts)
{
	int		count;
	int		spaces;

	count = 0;
	spaces = opts->width - 1;
	count += (opts->flags & 16) ? ft_putchar_count('%', 1) : 0;
	while (spaces-- > 0)
		count += ((opts->flags & 17) == 1) ? \
			ft_putchar_count('0', 1) : ft_putchar_count(' ', 1);
	count += (!(opts->flags & 16)) ? ft_putchar_count('%', 1) : 0;
	return (count);
}
