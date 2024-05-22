/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:58:50 by lhopp             #+#    #+#             */
/*   Updated: 2024/03/18 12:46:19 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

// Function pointer type for print functions
typedef void	(*t_print_func)(va_list args, int *count);

// Function prototypes
int				ft_printf(const char *format, ...);
char			*ft_utoa(unsigned int n);
char			*ft_utohex(unsigned int n, int uppercase);
char			*ft_ptohex(void *ptr);
void			print_char(va_list args, int *count);
void			print_string(va_list args, int *count);
void			print_int(va_list args, int *count);
void			print_uint(va_list args, int *count);
void			print_hex(va_list args, int *count);
void			print_hex_upper(va_list args, int *count);
void			print_pointer(va_list args, int *count);

#endif // FT_PRINTF_H
