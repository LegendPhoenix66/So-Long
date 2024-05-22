/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:38:21 by lhopp             #+#    #+#             */
/*   Updated: 2024/03/18 12:38:22 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_print_func	get_print_func(char specifier)
{
	unsigned char		u_specifier;
	static t_print_func	funcs[] = {
	['c'] = print_char,
	['s'] = print_string,
	['d'] = print_int,
	['i'] = print_int,
	['u'] = print_uint,
	['x'] = print_hex,
	['X'] = print_hex_upper,
	['p'] = print_pointer,
	};

	u_specifier = (unsigned char)specifier;
	if (u_specifier < sizeof(funcs) / sizeof(*funcs))
		return (funcs[u_specifier]);
	else
		return (NULL);
}

void	check_char(va_list args, t_print_func func, int *count, const char **p)
{
	if (*(*p) == '%')
	{
		func = get_print_func(*++(*p));
		if (func)
			func(args, count);
		else
		{
			ft_putchar_fd(*(*p), 1);
			(*count)++;
		}
	}
	else
	{
		ft_putchar_fd(*(*p), 1);
		(*count)++;
	}
}

int	ft_printf(const char *format, ...)
{
	va_list			args;
	int				count;
	const char		*p = format;
	t_print_func	func;

	func = NULL;
	va_start(args, format);
	count = 0;
	while (*p != '\0')
	{
		check_char(args, func, &count, &p);
		p++;
	}
	va_end(args);
	return (count);
}
