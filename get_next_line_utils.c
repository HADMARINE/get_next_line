/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:28:49 by lhojoon           #+#    #+#             */
/*   Updated: 2023/11/15 13:08:03 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	contains_newline(char *str, size_t limit);
void	*copymem(void *content, void *src, size_t *count, size_t newlen);
void	removefront(void *buf, size_t len, size_t maxlen);

size_t	verify_start(void *buf, size_t *remain_count, char **cur)
{
	size_t	nl;
	size_t	count;
	char	*s;

	count = 0;
	nl = contains_newline((char *)buf, BUFFER_SIZE);
	if (nl != 0)
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

void	*getzeromem(size_t size)
{
	unsigned char	*p;
	void			*v;

	v = malloc(size);
	p = (unsigned char *)v;
	while (size--)
	{
		*(p++) = (unsigned char)0;
	}
	return (v);
}

void	*free_and_go(void **buf, char *cur, size_t count, size_t *remain_count)
{
	if (buf != NULL)
	{
		free(*buf);
		*buf = NULL;
	}
	if (count == 0)
		return (NULL);
	if (remain_count)
		*remain_count = 0;
	return (cur);
}

size_t	contains_newline(char *str, size_t limit)
{
	char	*sp;

	if (!str)
		return (0);
	sp = (char *)str;
	while ((size_t)(sp - str) < limit && *sp)
	{
		if (*sp++ == '\n')
			return (sp - str);
	}
	return (0);
}
