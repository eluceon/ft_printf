/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:15:23 by eluceon           #+#    #+#             */
/*   Updated: 2020/12/07 16:03:50 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** The function applies the length modifier. Gets number from
** argument. Returns the modified number.
*/

static uintmax_t	ft_modify_un_nbr(t_struct *data, va_list *arg_ptr)
{
	unsigned long long int	nbr;

	if (data->modifier & MOD_LLNG)
		nbr = va_arg(*arg_ptr, unsigned long long int);
	else if (data->modifier & MOD_LONG)
		nbr = va_arg(*arg_ptr, unsigned long int);
	else
		nbr = va_arg(*arg_ptr, unsigned int);
	if (data->modifier & MOD_SHRT)
		nbr = (unsigned short)nbr;
	else if (data->modifier & MOD_CHAR)
		nbr = (unsigned char)nbr;
	return (nbr);
}

/*
** The function prints blanks. Returns the length of printed blanks.
*/

static	int			ft_print_blanks(t_struct *data, int nbr_len)
{
	int	length;

	length = 0;
	if (data->precision >= nbr_len)
		length += ft_print_sign(' ', data->width - data->precision);
	else
		length += ft_print_sign(' ', data->width - nbr_len);
	return (length);
}

/*
** The function prints zeros. Returns the length of printed zeros.
*/

static int			ft_print_zeros(t_struct *data, int nbr_len)
{
	int	length;

	length = 0;
	length += ft_print_sign('0', data->precision - nbr_len);
	if (data->flags & FLG_ZERO)
		length += ft_print_sign('0', data->width - nbr_len);
	return (length);
}

/*
**	The int (or appropriate variant) argument is converted to
**	unsigned hexadecimal (x and X) notation.  The letters
**	'abcdef' are used for x conversions; the letters
**  'ABCDEF' are used for X conversions.
*/

int					ft_type_x(t_struct *data, va_list *arg_ptr)
{
	uintmax_t	nbr;
	int			nbr_len;
	int			length;
	char		*str;

	nbr = ft_modify_un_nbr(data, arg_ptr);
	nbr_len = ft_un_nbr_base_len(nbr, 16);
	if (data->precision == 0 && nbr == 0)
		nbr_len = 0;
	length = nbr_len;
	if (!(data->flags & FLG_MINUS) & !(data->flags & FLG_ZERO))
		length += ft_print_blanks(data, nbr_len);
	length += ft_print_zeros(data, nbr_len);
	if (!(data->precision == 0 && nbr == 0))
	{
		if (data->type == 'x' && !(str = ft_itoa_un_base(nbr, 16, 'a')))
			return (-1);
		else if (data->type == 'X' && !(str = ft_itoa_un_base(nbr, 16, 'A')))
			return (-1);
		ft_putstr_fd(str, 1);
		free(str);
	}
	if ((data->flags & FLG_MINUS))
		length += ft_print_blanks(data, nbr_len);
	return (length);
}
