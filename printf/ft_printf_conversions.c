/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conversions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:47:46 by lhopp             #+#    #+#             */
/*   Updated: 2024/03/18 14:00:50 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_utoa(unsigned int n)
{
	unsigned int	temp;
	int				len;
	char			*str;

	len = 1;
	temp = n;
	temp /= 10;
	while (temp)
	{
		len++;
		temp /= 10;
	}
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

char	convert_digit_to_hex(int digit, int uppercase)
{
	if (digit < 10)
		return (digit + '0');
	else
	{
		if (uppercase)
			return (digit - 10 + 'A');
		else
			return (digit - 10 + 'a');
	}
}

char	*ft_utohex(unsigned int n, int uppercase)
{
	unsigned int	temp;
	int				len;
	char			*str;
	int				digit;

	len = 1;
	temp = n;
	temp /= 16;
	while (temp)
	{
		len++;
		temp /= 16;
	}
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		digit = n % 16;
		str[len] = convert_digit_to_hex(digit, uppercase);
		n /= 16;
	}
	return (str);
}

char	*fill_str(unsigned long long n, int len)
{
	int		digit;
	char	*str;

	str = malloc(len + 3);
	if (!str)
		return (NULL);
	str[0] = '0';
	str[1] = 'x';
	str[len + 2] = '\0';
	while (len--)
	{
		digit = n % 16;
		if (digit < 10)
			str[len + 2] = digit + '0';
		else
			str[len + 2] = digit - 10 + 'a';
		n /= 16;
	}
	return (str);
}

char	*ft_ptohex(void *ptr)
{
	unsigned long long	n;
	int					len;
	char				*str;

	if (ptr == NULL)
	{
		str = malloc(6);
		if (!str)
			return (NULL);
		ft_strlcpy(str, "(nil)", 6);
		return (str);
	}
	n = (unsigned long long)ptr;
	if (n)
		len = 1;
	else
		len = 0;
	n /= 16;
	while (n)
	{
		len++;
		n /= 16;
	}
	n = (unsigned long long)ptr;
	return (fill_str(n, len));
}
