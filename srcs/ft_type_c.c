/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 14:48:57 by eluceon           #+#    #+#             */
/*   Updated: 2020/12/07 15:02:27 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** The function prints blanks. Returns the length of printed blanks.
*/

static int	ft_print_blanks(t_struct *data, int len)
{
	int	length;

	length = 0;
	length += ft_print_sign(' ', data->width - len);
	return (length);
}

/*
**	The function prints character form c specifier.
*/

int			ft_type_c(t_struct *data, va_list *arg_ptr)
{
	int		length;

	length = 0;
	if (!(data->flags & FLG_MINUS))
		length += ft_print_blanks(data, 1);
	length += ft_print_sign((unsigned char)(va_arg(*arg_ptr, int)), 1);
	if ((data->flags & FLG_MINUS))
		length += ft_print_blanks(data, 1);
	return (length);
}
