/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:15:23 by eluceon           #+#    #+#             */
/*   Updated: 2020/12/07 15:20:50 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static uintmax_t	ft_get_ptr_nbr(va_list *arg_ptr)
{
	uintmax_t	nbr;

	nbr = va_arg(*arg_ptr, uintmax_t);
	return (nbr);
}

static	int			ft_print_blanks(t_struct *data, int nbr_len)
{
	int	length;

	length = 0;
	if (data->precision + 2 >= nbr_len)
		length += ft_print_sign(' ', data->width - data->precision - 2);
	else
		length += ft_print_sign(' ', data->width - nbr_len);
	return (length);
}

static int			ft_print_zeros(t_struct *data, int nbr_len)
{
	int	length;

	length = 0;
	length += ft_print_sign('0', data->precision - nbr_len + 2);
	return (length);
}

/*
**	The pointer argument is printed in hexadecimal.
*/

int					ft_type_p(t_struct *data, va_list *arg_ptr)
{
	uintmax_t	nbr;
	int			nbr_len;
	int			length;
	char		*str;

	nbr = ft_get_ptr_nbr(arg_ptr);
	nbr_len = ft_un_nbr_base_len(nbr, 16) + 2;
	if (data->precision == 0 && nbr == 0)
		nbr_len = 2;
	length = nbr_len;
	if (!(data->flags & FLG_MINUS) & !(data->flags & FLG_ZERO))
		length += ft_print_blanks(data, nbr_len);
	write(1, "0x", 2);
	length += ft_print_zeros(data, nbr_len);
	if (!(data->precision == 0 && nbr == 0))
	{
		if (!(str = ft_itoa_un_base(nbr, 16, 'a')))
			return (-1);
		ft_putstr_fd(str, 1);
		free(str);
		str = NULL;
	}
	if ((data->flags & FLG_MINUS))
		length += ft_print_blanks(data, nbr_len);
	return (length);
}
