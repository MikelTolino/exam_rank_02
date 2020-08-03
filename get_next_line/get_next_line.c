/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:57:50 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/30 23:56:48 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int					ft_strlen(char *s)
{
	int				len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int					ft_strchr(char *s, int c)
{
	int				len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] && s[len] != c)
		len++;
	if (s[len] != c && len == ft_strlen(s))
		return (0);
	return (1);
}

char				*ft_strdup(char *s)
{
	int				len;
	char			*str;

	len = ft_strlen(s);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	len = 0;
	while (s[len])
	{
		str[len] = s[len];
		len++;
	}
	str[len] = 0;
	return (str);
}

char				*ft_strjoin(char *s1, char *s2)
{
	int				len;
	char			*str;
	int				i;

	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	len = 0;
	while (s1[len])
	{
		str[len] = s1[len];
		len++;
	}
	i = 0;
	while (s2[i])
	{
		str[len + i] = s2[i];
		i++;
	}
	str[len + i] = 0;
	return (str);
}

char				*ft_substr(char *s, int start, int len)
{
	int				i;
	char			*str;

	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (len--)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}

int					read_line(char **line, char **s)
{
	int				len;
	char			*aux;

	len = 0;
	while ((*s)[len] && (*s)[len] != '\n')
		len++;
	if ((*s)[len] == '\n')
	{
		*line = ft_substr(*s, 0, len);
		aux = ft_strdup(&(*s)[len + 1]);
		free(*s);
		*s = aux;
	}
	else
	{
		*line = ft_strdup(*s);
		free(*s);
		*s = NULL;
		return (0);
	}
	return (1);
}

int					get_next_line(char **line)
{
	int				n_bytes;
	char			buff[BUFF_SIZE + 1];
	char			*aux;
	static char		*s;

	if (!line)
		return (-1);
	while (ft_strchr(s, '\n') == 0)
	{
		n_bytes = read(0, buff, BUFF_SIZE);
		if (n_bytes < 0)
			return (-1);
		if (n_bytes == 0)
			break ;
		buff[n_bytes] = 0;
		if (!s)
			s = ft_strdup(buff);
		else
		{
			aux = ft_strjoin(s, buff);
			free(s);
			s = aux;
		}
	}
	if (n_bytes == 0 && !s)
	{
		*line = ft_strdup("");
		return (0);
	}
	else
		return(read_line(line, &s));
}