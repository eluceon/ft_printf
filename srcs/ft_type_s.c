/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 16:00:33 by eluceon           #+#    #+#             */
/*   Updated: 2020/12/09 15:57:48 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** The function prints blanks. Returns the length of printed blanks.
*/

static int	ft_print_blanks(t_struct *data, int str_len)
{
	int	length;

	length = 0;
	length += ft_print_sign(' ', data->width - str_len);
	return (length);
}

/*
** The function prints zeros. Returns the length of printed zeros.
*/

static int	ft_print_zeros(t_struct *data, int nbr_len)
{
	int	length;

	length = 0;
	if (data->flags & FLG_ZERO)
		length += ft_print_sign('0', data->width - nbr_len);
	return (length);
}

/*
**	The function prints string from the char * argument.
*/

int			ft_type_s(t_struct *data, va_list *arg_ptr)
{
	int		length;
	int		str_len;
	char	*str;
	char	need_to_free;

	need_to_free = 0;
	str = (va_arg(*arg_ptr, char *));
	if (!str && ((str = strdup("(null)"))))
		need_to_free = 1;
	else if (!str)
		return (-1);
	str_len = ft_strlen(str);
	if (data->precision >= 0 && data->precision < str_len)
		str_len = data->precision;
	length = str_len;
	if (!(data->flags & FLG_MINUS) & !(data->flags & FLG_ZERO))
		length += ft_print_blanks(data, str_len);
	length += ft_print_zeros(data, str_len);
	write(1, str, str_len);
	if (need_to_free)
		free(str);
	if ((data->flags & FLG_MINUS))
		length += ft_print_blanks(data, str_len);
	return (length);
}
