/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_numbers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:46:30 by lhopp             #+#    #+#             */
/*   Updated: 2024/03/18 12:46:32 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_int(va_list args, int *count)
{
	int		value;
	char	*str;

	value = va_arg(args, int);
	str = ft_itoa(value);
	ft_putstr_fd(str, 1);
	(*count) += (int)ft_strlen(str);
	free(str);
}

void	print_uint(va_list args, int *count)
{
	unsigned int	value;
	char			*str;

	value = va_arg(args, unsigned int);
	str = ft_utoa(value);
	ft_putstr_fd(str, 1);
	(*count) += (int)ft_strlen(str);
	free(str);
}

void	print_hex(va_list args, int *count)
{
	unsigned int	value;
	char			*str;

	value = va_arg(args, unsigned int);
	str = ft_utohex(value, 0);
	ft_putstr_fd(str, 1);
	(*count) += (int)ft_strlen(str);
	free(str);
}

void	print_hex_upper(va_list args, int *count)
{
	unsigned int	value;
	char			*str;

	value = va_arg(args, unsigned int);
	str = ft_utohex(value, 1);
	ft_putstr_fd(str, 1);
	(*count) += (int)ft_strlen(str);
	free(str);
}
