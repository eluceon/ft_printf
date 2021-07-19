/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_n.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 14:01:57 by eluceon           #+#    #+#             */
/*   Updated: 2020/12/07 15:05:10 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	The function gets the number of characters written so far
**	and stored into the integer indicated by the int *
**	(or variant) pointer argument. No argument is converted.
*/

int	ft_type_n(t_struct *data, va_list *arg_ptr, long long int length)
{
	long long int	*n;

	n = (long long int	*)va_arg(*arg_ptr, long long int *);
	if (data->modifier & MOD_LLNG)
		*n = (long long int)length;
	else if (data->modifier & MOD_LONG)
		*n = (long int)length;
	else
		*n = (int)length;
	if (data->modifier & MOD_SHRT)
		*n = (short)length;
	else if (data->modifier & MOD_CHAR)
		*n = (char)length;
	return (0);
}
