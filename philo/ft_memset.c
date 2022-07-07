/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:41:04 by eestelle          #+#    #+#             */
/*   Updated: 2022/07/07 15:41:05 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
typedef unsigned long long	t_ull;

static	t_ull	*ft_completion(t_ull *ptrs, size_t len, t_ull c)
{	
	while (len--)
	{
		ptrs[0] = c;
		ptrs[1] = c;
		ptrs[2] = c;
		ptrs[3] = c;
		ptrs[4] = c;
		ptrs[5] = c;
		ptrs[6] = c;
		ptrs[7] = c;
		ptrs += 8;
	}
	return (ptrs);
}

void	ft_fast_completion(char *bs, size_t n, int c)
{
	size_t		len;
	t_ull		*ptrs;
	t_ull		cccccccc;

	cccccccc = (unsigned char)c;
	cccccccc |= cccccccc << 8;
	cccccccc |= cccccccc << 16;
	cccccccc |= cccccccc << 32;
	ptrs = (t_ull *)bs;
	len = n / 64;
	if (len)
		ptrs = ft_completion(ptrs, len, cccccccc);
	len = (n % 64) / 8;
	while (len)
	{
		*(ptrs++) = cccccccc;
		len--;
	}
	len = n % 8;
	bs = (char *)ptrs;
	while (len--)
		*(bs++) = (unsigned char)c;
}

void	*ft_memset(void *s, int c, size_t n)
{
	char		*bptr;

	bptr = (char *)s;
	while ((size_t)bptr % 8 && n)
	{
		*(bptr++) = (unsigned char)c;
		n--;
	}
	if (!n)
		return (s);
	ft_fast_completion(bptr, n, c);
	return (s);
}
