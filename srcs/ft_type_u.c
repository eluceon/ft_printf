/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 05:37:03 by eluceon           #+#    #+#             */
/*   Updated: 2020/12/07 15:56:24 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			ft_un_putnbr(unsigned long long int n)
{
	char					c;

	if (n > 9)
		ft_un_putnbr(n / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
}

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
**	The function prints unsigned int argument.
*/

int					ft_type_u(t_struct *data, va_list *arg_ptr)
{
	unsigned long long int	nbr;
	int						nbr_len;
	int						length;

	nbr = ft_modify_un_nbr(data, arg_ptr);
	nbr_len = ft_un_nbr_base_len(nbr, 10);
	if (data->precision == 0 && nbr == 0)
		nbr_len = 0;
	length = nbr_len;
	if (!(data->flags & FLG_MINUS) & !(data->flags & FLG_ZERO))
		length += ft_print_blanks(data, nbr_len);
	length += ft_print_zeros(data, nbr_len);
	if (!(data->precision == 0 && nbr == 0))
		ft_un_putnbr(nbr);
	if ((data->flags & FLG_MINUS))
		length += ft_print_blanks(data, nbr_len);
	return (length);
}
