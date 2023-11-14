/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:28:47 by lhojoon           #+#    #+#             */
/*   Updated: 2023/11/14 17:59:27 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	contains_newline(char *str);
void	*copymem(void *content, void *src, size_t *count, size_t newlen);
size_t	manage_remains(void *buf, char **cur, size_t *count, size_t newlen);
void	*freeandgo(void *buf, char *cur);
size_t	verify_start(void *buf, size_t *remain_count, char **cur);
void	removefront(void *buf, size_t len, size_t maxlen);

void	*freeandgo(void *buf, char *cur)
{
	free(buf);
	return (cur);
}

char	*get_next_line(int fd)
{
	static void		*buf = NULL;
	static size_t	remain_count = 0;
	char			*cur;
	int				res;
	size_t			count;

	cur = NULL;
	count = 0;
	// printf("\n\nBUFFER\n___\n%s\n__\n", (char *)buf);
	if (buf == NULL)
		buf = malloc(BUFFER_SIZE);
	if (remain_count > 0)
	{
		count = verify_start(buf, &remain_count, &cur);
		if (count == 2)
			return (cur);
		if (count == 1)
			return (freeandgo(buf, NULL));
		if (count == 0)
			count = remain_count;
	}
	res = read(fd, buf, BUFFER_SIZE);
	while (contains_newline(((char *)buf)) == 0 && res != 0)
	{
		cur = copymem(cur, buf, &count, res);
		if (!cur)
			return (NULL);
		res = read(fd, buf, BUFFER_SIZE);
	}
	if (res == 0)
		return (freeandgo(buf, cur));
	remain_count = manage_remains(buf, &cur, &count, (size_t)res);
	return (cur);
}

size_t	manage_remains(void *buf, char **cur, size_t *count, size_t newlen)
{
	char	*s;
	size_t	i;

	i = 0;
	s = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	while (i < newlen && *((char *)buf + i - 1) != '\n')
	{
		*((char *)s + i) = *((char *)buf + i);
		i++;
	}
	*cur = copymem(*cur, s, count, i);
	removefront(buf, *count, BUFFER_SIZE);
	free(s);
	return (newlen - i);
}

size_t	contains_newline(char *str)
{
	char	*sp;

	sp = (char *)str;
	while (*sp)
	{
		if (*sp++ == '\n')
			return (sp - str);
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
