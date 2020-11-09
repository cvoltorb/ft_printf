/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvoltorb <cvoltorb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 17:36:41 by cvoltorb          #+#    #+#             */
/*   Updated: 2020/08/02 19:17:59 by cvoltorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H
# include <stdarg.h>
# include <wchar.h>
# include <sys/types.h>

typedef struct	s_options
{
	int			width;
	int			prec;
	int			count_already_printed;
	int			e_pow;
	char		flags;
	char		subspec;
	char		spec;
}				t_options;

int				ft_printf(const char *format, ...);
char			*ft_printf_strchr(const char *s, int c);
char			*ft_printf_strdup(const char *s);
size_t			ft_printf_strlcpy(char *dst, const char *src, size_t size);
int				ft_printf_toupper(int c);
size_t			ft_printf_strlen(const char *s);
char			*ft_strupper(char *s);
char			*ft_llitoa_base(ssize_t n, int base);
char			*ft_ullitoa_base(unsigned long long n, int base);
char			ft_isspec(const char *format, int *i, t_options *opts);
int				ft_pars_format(va_list params, const char *format);
int				ft_print_argument(va_list params, t_options *opts);
int				ft_print_char(va_list params, t_options *opts);
int				ft_print_str(va_list params, t_options *opts);
int				ft_print_int(va_list params, t_options *opts);
int				ft_print_ptr_uns_hex_oct(va_list params, t_options *opts);
size_t			ft_check_u_o_x_subspec(va_list params, t_options *opts);
int				ft_print_float_scientific(va_list params, t_options *opts);
int				ft_print_percent(t_options *opts);
int				ft_print_e_pow(t_options *opts);
int				ft_print_sign(t_options *opts, long double val);
int				ft_putchar_count(char c, int fd);
int				ft_putstr_count(char *s, int fd);
int				ft_save_count_printed(va_list params, t_options *opts);
t_options		ft_init_opts(int count);

#endif
