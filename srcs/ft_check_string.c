/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 13:04:05 by eluceon           #+#    #+#             */
/*   Updated: 2020/12/07 12:14:26 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_type(const char *str, t_struct *data)
{
	if (*str == 'd' || *str == 'i' || *str == 'u' || *str == 'x' ||
		*str == 'X' || *str == 'c' || *str == 's' || *str == 'p' ||
		*str == 'n' || *str == '%')
	{
		data->type = *str;
		++data->length;
		return (1);
	}
	return (0);
}

int	ft_check_modifier(const char *str, t_struct *data)
{
	const char	*start;

	start = str;
	if (*str == 'l' && *(str + 1) == 'l')
	{
		str++;
		data->modifier = MOD_LLNG;
	}
	else if (*str == 'l')
		data->modifier = MOD_LONG;
	else if (*str == 'h' && *(str + 1) == 'h')
	{
		str++;
		data->modifier = MOD_CHAR;
	}
	else if (*str == 'h')
		data->modifier = MOD_SHRT;
	else
	{
		data->modifier = MOD_NONE;
		return (0);
	}
	str++;
	data->length += str - start;
	return (str - start);
}

int	ft_check_precision(const char *str, t_struct *data, va_list *arg_ptr)
{
	const char	*start;

	start = str;
	data->precision = 0;
	if (*str == '.' && *(str + 1) == '*')
	{
		str += 2;
		data->precision = va_arg(*arg_ptr, int);
	}
	else if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
			data->precision = data->precision * 10 + *str++ - '0';
	}
	else
		data->precision = -1;
	data->length += str - start;
	return (str - start);
}

int	ft_check_width(const char *str, t_struct *data, va_list *arg_ptr)
{
	const char	*start;

	start = str;
	data->width = 0;
	if (*str == '*')
	{
		if ((data->width = va_arg(*arg_ptr, int)) < 0)
		{
			data->flags = data->flags | FLG_MINUS;
			data->width *= -1;
		}
		++data->length;
		return (1);
	}
	while (*str >= '0' && *str <= '9')
		data->width = data->width * 10 + *str++ - '0';
	data->length += str - start;
	return (str - start);
}

int	ft_check_flags(const char *str, t_struct *data)
{
	const char	*start;

	start = str;
	data->flags = FLG_NONE;
	while (*str)
	{
		if (*str == '-')
			data->flags = data->flags | FLG_MINUS;
		else if (*str == '0')
			data->flags = data->flags | FLG_ZERO;
		else if (*str == '+')
			data->flags = data->flags | FLG_PLUS;
		else if (*str == ' ')
			data->flags = data->flags | FLG_SPACE;
		else if (*str == '#')
			data->flags = data->flags | FLG_HASH;
		else
			break ;
		str++;
	}
	data->length += str - start;
	return (str - start);
}
