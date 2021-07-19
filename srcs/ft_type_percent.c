/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_percent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 12:55:48 by eluceon           #+#    #+#             */
/*   Updated: 2020/12/07 16:12:35 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_blnaks(t_struct *data, int str_len)
{
	int	length;

	length = 0;
	length += ft_print_sign(' ', data->width - str_len);
	return (length);
}

static int	ft_print_zeros(t_struct *data, int nbr_len)
{
	int	length;

	length = 0;
	if (data->flags & FLG_ZERO)
		length += ft_print_sign('0', data->width - nbr_len);
	return (length);
}

/*
** Prints % symbol
*/

int			ft_type_percent(t_struct *data)
{
	int		length;

	length = 1;
	if (!(data->flags & FLG_MINUS) & !(data->flags & FLG_ZERO))
		length += ft_print_blnaks(data, 1);
	length += ft_print_zeros(data, 1);
	write(1, "%", 1);
	if ((data->flags & FLG_MINUS))
		length += ft_print_blnaks(data, 1);
	return (length);
}
