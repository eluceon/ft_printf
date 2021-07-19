/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:57:16 by eluceon           #+#    #+#             */
/*   Updated: 2020/12/05 15:18:01 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoa_un_base(uintmax_t nbr, int base, char c)
{
	char	*str;
	int		len;
	int		remainder;

	len = ft_un_nbr_base_len(nbr, base);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len] = '\0';
	while (len)
	{
		remainder = nbr % base;
		if (remainder <= 9)
			str[--len] = remainder + '0';
		else if (remainder > 9)
			str[--len] = remainder + c - 10;
		nbr /= base;
	}
	return (str);
}

int		ft_nbr_len(long long int n)
{
	int	len;

	len = 1;
	if (n < 0)
		len++;
	while (n / 10 != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int		ft_un_nbr_base_len(unsigned long long int n, int base)
{
	int	len;

	len = 1;
	while (n / base != 0)
	{
		n /= base;
		len++;
	}
	return (len);
}

int		ft_print_sign(unsigned char c, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		write(1, &c, 1);
	if (len > 0)
		return (len);
	return (0);
}
