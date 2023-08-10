/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:52:08 by fgrea             #+#    #+#             */
/*   Updated: 2021/04/21 16:49:22 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*dst;
	char	*ret;

	dst = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	ret = dst;
	dst = ft_memcpy(dst, s1, ft_strlen(s1));
	dst += ft_strlen(s1);
	dst = ft_memcpy(dst, s2, ft_strlen(s2));
	dst += ft_strlen(s2);
	*dst = '\0';
	return (ret);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	if (n == 0)
		return (NULL);
	while (--n > 0 && *(unsigned char *)s != (unsigned char)c)
		s++;
	if (n == 0 && *(unsigned char *)s != (unsigned char)c)
		return (NULL);
	else
		return ((void *)s);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*ret;

	if (!src && !dst)
		return (NULL);
	ret = dst;
	while (n-- > 0)
		*(unsigned char *)dst++ = *(unsigned char *)src++;
	return (ret);
}

int	la_norme_cette_sale_grande_tante(int fd, char **r, char **eol)
{
	char		buf[BUFFER_SIZE + 1];
	ssize_t		read_ret;
	char		*tmp;

	read_ret = -2;
	*eol = ft_memchr(*r, '\n', ft_strlen(*r));
	while (read_ret != 0 && !*eol)
	{
		read_ret = read(fd, buf, BUFFER_SIZE);
		if (read_ret < 0)
			return (-1);
		buf[read_ret] = 0;
		tmp = ft_strjoin(*r, buf);
		free(*r);
		*r = tmp;
		if (!*r)
			return (-1);
		*eol = ft_memchr(*r, '\n', ft_strlen(*r));
	}
	return (read_ret);
}

int	get_next_line(int fd, char **line)
{
	static char	*r;
	ssize_t		read_ret;
	char		*tmp;
	char		*eol;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	read_ret = la_norme_cette_sale_grande_tante(fd, &r, &eol);
	if (read_ret == -1)
		return (-1);
	if (!eol)
	{
		*line = ft_substr(r, 0, ft_strlen(r));
		free(r);
		r = NULL;
		return (0);
	}
	*line = ft_substr(r, 0, eol - r);
	tmp = ft_substr(r, (eol - r) + 1, ft_strlen(r) - (eol - r));
	free(r);
	r = NULL;
	r = tmp;
	return (1);
}
