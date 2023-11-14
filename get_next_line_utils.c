/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:28:49 by lhojoon           #+#    #+#             */
/*   Updated: 2023/11/14 17:55:47 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	contains_newline(char *str);
void	*copymem(void *content, void *src, size_t *count, size_t newlen);
void	removefront(void *buf, size_t len, size_t maxlen);

size_t	verify_start(void *buf, size_t *remain_count, char **cur)
{
	size_t	nl;
	size_t	count;
	char	*s;

	count = 0;
	nl = contains_newline((char *)buf);
	if (nl)
	{
		s = copymem(NULL, buf, &count, nl);
		if (!s)
			return (1);
	}
	else
	{
		s = copymem(NULL, buf, &count, *remain_count);
		if (!s)
			return (1);
		*cur = s;
		return (0);
	}
	removefront(buf, count, BUFFER_SIZE);
	*remain_count -= count;
	*cur = s;
	return (2);
}

void	removefront(void *buf, size_t len, size_t maxlen)
{
	size_t	i;

	i = 0;
	while (maxlen - len > i && maxlen >= i)
	{
		*((char *)buf + i) = *((char *)buf + i + len);
		i++;
	}
	while (i < maxlen)
	{
		*((char *)buf + i++) = 0;
	}
}
