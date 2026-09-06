/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <lcosta-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:22:41 by lcosta-a          #+#    #+#             */
/*   Updated: 2025/08/13 17:05:19 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	process_specifier(va_list args, char specifier)
{
	int		count;
	void	*ptr;

	count = 0;
	if (specifier == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (specifier == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (specifier == 'd' || specifier == 'i')
		count += ft_putnbr(va_arg(args, long long));
	else if (specifier == 'u')
		count += ft_putunbr(va_arg(args, unsigned int));
	else if (specifier == 'x' || specifier == 'X')
		count += ft_puthex(va_arg(args, unsigned int), specifier == 'X');
	else if (specifier == 'p')
	{
		ptr = va_arg(args, void *);
		count += ft_putptr(ptr);
	}
	else if (specifier == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(const	char	*format, ...)
{
	int			len;
	va_list		args;

	len = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			len += process_specifier(args, *format);
		}
		else
		{
			ft_putchar(*format);
			len++;
		}
		format++;
	}
	va_end(args);
	return (len);
}
