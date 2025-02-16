/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kim <jae-kim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 00:27:44 by jae-kim           #+#    #+#             */
/*   Updated: 2021/01/08 11:30:26 by jae-kim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digit(long long n)
{
	size_t	ret;

	if (n == 0)
		return (1);
	ret = 1;
	while (n >= 10 || n <= (-10))
	{
		n = n / 10;
		ret++;
	}
	return (ret);
}

static char		*allocate_digit(char *ret, long long n, size_t count, char sign)
{
	if (n == 0)
		*ret = 48;
	*(ret + count) = '\0';
	if (sign)
	{
		*ret = '-';
		*(ret + --count) = n % 10 * (-1) + 48;
		n = n / 10 * (-1);
	}
	while (n >= 10)
	{
		*(ret + count - 1) = (n % 10) + 48;
		n = n / 10;
		count--;
	}
	if (n != 0)
		*(ret + count - 1) = n + 48;
	return (ret);
}

char			*ft_itoa(long long n)
{
	size_t		count;
	char		sign;
	char		*ret;

	sign = '\0';
	count = count_digit(n);
	if (n < 0)
	{
		sign = '-';
		count++;
	}
	if (!(ret = malloc(sizeof(char) * (count + 1))))
		return (NULL);
	ret = allocate_digit(ret, n, count, sign);
	return (ret);
}
