/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:28:47 by lhojoon           #+#    #+#             */
/*   Updated: 2023/11/14 14:01:27 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

short	contains_newline(const char *str);
void	*copymem(void *content, void *src, size_t *count, size_t newlen);

char	*get_next_line(int fd)
{
	static void		*buf;
	char			*cur;
	int				res;
	size_t			count;

	buf = malloc(BUFFER_SIZE);
	res = read(fd, buf, BUFFER_SIZE);
	cur = NULL;
	count = 0;
	while (!contains_newline(buf))
	{
		cur = copymem(cur, buf, &count, res);
		if (!cur)
			return (NULL);
		res = read(fd, buf, BUFFER_SIZE);
	}
	if (!res)
		return (NULL);
	return (cur);
}

short	contains_newline(const char *str)
{
	while (*str)
	{
		if (*str++ == '\n')
			return (1);
	}
	return (0);
}

void	*copymem(void *content, void *src, size_t *count, size_t newlen)
{
	size_t	i;
	void	*trunk;

	trunk = malloc(*count + newlen);
	if (!trunk)
		return (NULL);
	i = 0;
	while (i < *count)
	{
		*((char *)trunk + i) = *((char *)content + i);
		i++;
	}
	*count += newlen;
	while (i < *count)
	{
		*((char *)trunk + i) = *((char *)src + (size_t)(i - (*count - newlen)));
		i++;
	}
	free(content);
	return (trunk);
}
