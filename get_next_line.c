/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:28:47 by lhojoon           #+#    #+#             */
/*   Updated: 2023/11/15 14:21:31 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	contains_newline(char buf[], size_t limit);
void	*copymem(void *content, void *src, size_t *count, size_t newlen);
size_t	manage_remains(char buf[], char **cur, size_t *count, size_t newlen);
void	*free_and_go(char *cur, size_t count, size_t *remain_count);
size_t	verify_start(char buf[], size_t *remain_count, char **cur);
void	removefront(char buf[], size_t len, size_t maxlen);
void	putzero(char buf[], size_t size);
char	*inner_gnl(char buf[], size_t *remain_count, size_t count, int fd);

char	*get_next_line(int fd)
{
	static char		buf[BUFFER_SIZE];
	static short	isnew = 1;
	static size_t	remain_count = 0;
	size_t			count;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_and_go(NULL, 0, NULL));
	if (isnew == 1)
	{
		isnew = 0;
		putzero(buf, BUFFER_SIZE);
	}
	count = 0;
	return (inner_gnl(buf, &remain_count, count, fd));
}

void	*return_by_count(char *cur, size_t count)
{
	if (count == 2)
		return (cur);
	if (count == 1)
		return (free_and_go(NULL, 0, NULL));
	return (NULL);
}

char	*inner_gnl(char buf[], size_t *remain_count, size_t count, int fd)
{
	char			*cur;
	int				res;

	cur = NULL;
	if (*remain_count > 0)
	{
		count = verify_start(buf, remain_count, &cur);
		if (count == 2 || count == 1)
			return (return_by_count(cur, count));
		if (count == 0)
			count = *remain_count;
	}
	res = read(fd, buf, BUFFER_SIZE);
	while (res > 0 && contains_newline(buf, res) == 0)
	{
		cur = copymem(cur, buf, &count, res);
		if (!cur)
			return (NULL);
		res = read(fd, buf, BUFFER_SIZE);
	}
	if (res <= 0)
		return (free_and_go(cur, count, remain_count));
	*remain_count = manage_remains(buf, &cur, &count, (size_t)res);
	return (cur);
}

size_t	manage_remains(char buf[], char **cur, size_t *count, size_t newlen)
{
	char	*s;
	size_t	i;

	i = 0;
	s = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	while (i < newlen && *(buf + i) != '\n')
	{
		*((char *)s + i) = *(buf + i);
		i++;
	}
	if (i != BUFFER_SIZE)
		*((char *)s + i++) = '\n';
	*cur = copymem(*cur, s, count, i);
	removefront(buf, i, BUFFER_SIZE);
	free(s);
	return (newlen - i);
}

void	*copymem(void *content, void *src, size_t *count, size_t newlen)
{
	size_t	i;
	void	*trunk;

	trunk = malloc(*count + newlen + 1);
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
	*((char *)trunk + i++) = '\0';
	free(content);
	return (trunk);
}
