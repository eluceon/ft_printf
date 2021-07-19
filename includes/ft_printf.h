/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 07:10:56 by eluceon           #+#    #+#             */
/*   Updated: 2020/12/07 16:17:16 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
# include "../libft/libft.h"

# define FLG_NONE	0b00000000
# define FLG_MINUS	0b00000001
# define FLG_PLUS	0b00000010
# define FLG_SPACE	0b00000100
# define FLG_HASH	0b00001000
# define FLG_ZERO	0b00010000

# define MOD_NONE	0b00000000
# define MOD_LONG	0b00000001
# define MOD_CHAR	0b00000010
# define MOD_SHRT	0b00000100
# define MOD_LLNG	0b00001000
# define MOD_LLLG	0b00010000

typedef struct	s_struct
{
	unsigned char	flags;
	int				width;
	int				precision;
	unsigned char	modifier;
	char			type;
	unsigned int	length;
}				t_struct;

int				ft_check_flags(const char *str, t_struct *data);
int				ft_check_width(const char *str, t_struct *data,
									va_list *arg_ptr);
int				ft_check_precision(const char *str, t_struct *data,
									va_list *arg_ptr);
int				ft_check_modifier(const char *str, t_struct *data);
int				ft_check_type(const char *str, t_struct *data);
int				ft_type_d(t_struct *data, va_list *arg_ptr);
int				ft_type_u(t_struct *data, va_list *arg_ptr);
int				ft_type_c(t_struct *data, va_list *arg_ptr);
int				ft_type_s(t_struct *data, va_list *arg_ptr);
int				ft_type_x(t_struct *data, va_list *arg_ptr);
int				ft_type_p(t_struct *data, va_list *arg_ptr);
int				ft_type_n(t_struct *data, va_list *arg_ptr,
									long long int length);
int				ft_type_percent(t_struct *data);
char			*ft_itoa_un_base(uintmax_t nbr, int base, char c);
int				ft_printf(const char *format, ...);
int				ft_nbr_len(long long int n);
int				ft_print_sign(unsigned char c, int len);
int				ft_un_nbr_base_len(unsigned long long int n, int base);

#endif
