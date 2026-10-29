/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <lcosta-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 01:27:04 by lcosta-a          #+#    #+#             */
/*   Updated: 2025/08/13 17:07:34 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex(unsigned long n, int uppercase)
{
	char	*base;
	int		len;

	if (uppercase)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	len = 0;
	if (n >= 16)
		len += ft_puthex(n / 16, uppercase);
	len += ft_putchar(base[n % 16]);
	return (len);
}
