/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:28:49 by lhojoon           #+#    #+#             */
/*   Updated: 2023/11/15 14:21:41 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	contains_newline(char *str, size_t limit);
void	*copymem(void *content, void *src, size_t *count, size_t newlen);
void	removefront(char buf[], size_t len, size_t maxlen);

size_t	verify_start(char buf[], size_t *remain_count, char **cur)
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

void	removefront(char buf[], size_t len, size_t maxlen)
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

void	putzero(char buf[], size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		buf[i] = 0;
		i++;
	}
}

void	*free_and_go(char *cur, size_t count, size_t *remain_count)
{
	if (count == 0)
		return (NULL);
	if (remain_count)
		*remain_count = 0;
	return (cur);
}

size_t	contains_newline(char str[], size_t limit)
{
	char	*sp;

	sp = str;
	while ((size_t)(sp - str) < limit && *sp)
	{
		if (*sp++ == '\n')
			return (sp - str);
	}
	return (0);
}
