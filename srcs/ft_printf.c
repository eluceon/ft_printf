/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 06:54:49 by eluceon           #+#    #+#             */
/*   Updated: 2020/12/07 15:47:51 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** The function parses flags, width, percision, modifyer and type.
** If flag is zero and minus simultaneously or zero and percision
** simultaneously it exludes zero flag.
** If type hasn't been fount it frees data and returns NULL.
*/

t_struct	*ft_parse(const char *str, va_list *arg_ptr)
{
	t_struct		*data;

	str++;
	if (!(data = (t_struct *)malloc(sizeof(t_struct))))
		return (NULL);
	data->length = 1;
	str += ft_check_flags(str, data);
	str += ft_check_width(str, data, arg_ptr);
	if ((data->flags & FLG_ZERO) && (data->flags & FLG_MINUS))
		data->flags = data->flags & (~FLG_ZERO);
	str += ft_check_precision(str, data, arg_ptr);
	str += ft_check_modifier(str, data);
	if (!(ft_check_type(str, data)))
	{
		free(data);
		return (NULL);
	}
	if (data->precision > -1 && data->type != '%')
		data->flags = data->flags & (~FLG_ZERO);
	return (data);
}

/*
** The function chooses function to print arguments from
** specifier. Returns the number of characters printed from
** the specifier.
*/

int			ft_get_type(t_struct *data, va_list *arg_ptr, int long long length)
{
	if (data->type == 'd' || data->type == 'i')
		return (ft_type_d(data, arg_ptr));
	else if (data->type == 'u')
		return (ft_type_u(data, arg_ptr));
	else if (data->type == 'c')
		return (ft_type_c(data, arg_ptr));
	else if (data->type == 's')
		return (ft_type_s(data, arg_ptr));
	else if (data->type == 'x' || data->type == 'X')
		return (ft_type_x(data, arg_ptr));
	else if (data->type == 'p')
		return (ft_type_p(data, arg_ptr));
	else if (data->type == '%')
		return (ft_type_percent(data));
	else if (data->type == 'n')
		return (ft_type_n(data, arg_ptr, length));
	return (0);
}

/*
** The main function. Prints ordinary characters before %.
** If % is found parses data and gets type from specifier.
** Return the number of characters printed.
*/

int			ft_printf(const char *format, ...)
{
	int long long	length;
	va_list			arg_ptr;
	t_struct		*data;

	va_start(arg_ptr, format);
	length = 0;
	while (*format)
	{
		if (*format != '%')
			length += ft_print_sign(*format++, 1);
		else if ((data = ft_parse(format, &arg_ptr)))
		{
			format += data->length;
			length += ft_get_type(data, &arg_ptr, length);
			free(data);
		}
		else
		{
			va_end(arg_ptr);
			return (-1);
		}
	}
	va_end(arg_ptr);
	return (length);
}
