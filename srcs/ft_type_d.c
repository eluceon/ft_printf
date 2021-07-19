/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 05:37:03 by eluceon           #+#    #+#             */
/*   Updated: 2020/12/07 14:59:28 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	void	ft_putnbr(long long int n)
{
	char					c;
	unsigned long long int	nb;

	nb = (unsigned long long int)n;
	if (n < 0)
		nb = -nb;
	if (nb > 9)
		ft_putnbr(nb / 10);
	c = nb % 10 + '0';
	write(1, &c, 1);
}

/*
** The function applies the length modifier. Gets number from
** argument. Returns the modified number.
*/

static intmax_t	ft_modify_nbr(t_struct *data, va_list *arg_ptr)
{
	long long int	nbr;

	if (data->modifier & MOD_LLNG)
		nbr = va_arg(*arg_ptr, long long int);
	else if (data->modifier & MOD_LONG)
		nbr = va_arg(*arg_ptr, long int);
	else
		nbr = va_arg(*arg_ptr, int);
	if (data->modifier & MOD_SHRT)
		nbr = (short)nbr;
	else if (data->modifier & MOD_CHAR)
		nbr = (char)nbr;
	return (nbr);
}

/*
** The function prints blanks. Returns the length of printed blanks.
*/

static int		ft_print_blanks(t_struct *data, int nbr_len, int minus)
{
	int	length;

	length = 0;
	if (data->precision >= nbr_len)
		length += ft_print_sign(' ', data->width - data->precision - minus);
	else
		length += ft_print_sign(' ', data->width - nbr_len);
	return (length);
}

/*
** The function prints zeros. Returns the length of printed zeros.
*/

static	int		ft_print_zeros(t_struct *data, int nbr_len, int minus)
{
	int	length;

	length = 0;
	length += ft_print_sign('0', data->precision + minus - nbr_len);
	if (data->flags & FLG_ZERO)
		length += ft_print_sign('0', data->width - nbr_len);
	return (length);
}

/*
**	The function prints signed int argument.
*/

int				ft_type_d(t_struct *data, va_list *arg_ptr)
{
	long long int	nbr;
	int				nbr_len;
	int				length;

	nbr = ft_modify_nbr(data, arg_ptr);
	nbr_len = ft_nbr_len(nbr);
	if (data->precision == 0 && nbr == 0)
		nbr_len = 0;
	length = nbr_len;
	if (!(data->flags & FLG_MINUS) & !(data->flags & FLG_ZERO))
		length += ft_print_blanks(data, nbr_len, (nbr < 0));
	if (nbr < 0)
		ft_print_sign('-', 1);
	length += ft_print_zeros(data, nbr_len, (nbr < 0));
	if (!(data->precision == 0 && nbr == 0))
		ft_putnbr(nbr);
	if ((data->flags & FLG_MINUS))
		length += ft_print_blanks(data, nbr_len, (nbr < 0));
	return (length);
}
