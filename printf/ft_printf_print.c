/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:46:24 by lhopp             #+#    #+#             */
/*   Updated: 2024/03/18 12:47:10 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_char(va_list args, int *count)
{
	char	value;

	value = va_arg(args, int);
	ft_putchar_fd(value, 1);
	(*count)++;
}

void	print_string(va_list args, int *count)
{
	char	*value;

	value = va_arg(args, char *);
	if (value == NULL)
	{
		value = "(null)";
	}
	ft_putstr_fd(value, 1);
	(*count) += (int)ft_strlen(value);
}

void	print_pointer(va_list args, int *count)
{
	void	*value;
	char	*str;

	value = va_arg(args, void *);
	str = ft_ptohex(value);
	ft_putstr_fd(str, 1);
	(*count) += (int)ft_strlen(str);
	free(str);
}
