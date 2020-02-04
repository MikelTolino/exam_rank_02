/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmateo-t <mmateo-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:59:18 by mmateo-t          #+#    #+#             */
/*   Updated: 2020/01/30 10:17:20 by mmateo-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

unsigned int ft_strlen(char *s)
{
	unsigned int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strchr(char *str, int c)
{
	unsigned int i; 
	unsigned int len;

	i = 0;
	if (!str)
		return (0);
	len = ft_strlen(str);
	while (str[i] && str[i] != c)
	{
		i++;
	}
	if (str[i] != c && i == len)
		return (0);
	return (1);
}

char *ft_strdup(char *str)
{
	int len;
	char *str2;

	len = 0;
	while (str[len])
	{
		len++;
	}
	str2 = (char *)malloc(sizeof(char) * (len + 1));
	len = 0;
	while (str[len])
	{
		str2[len] = str[len];
		len++;
	}
	str2[len] = '\0';
	return (str2);
}

char *ft_strjoin(char *str1, char *str2)
{
	int i;
	int j;
	char *str3;

	i = 0;
	j = 0;
	while (str1[i])
	{
		i++;
	}
	while (str2[j])
	{
		j++;
	}
	str3 = (char *)malloc(sizeof(char) * (i + j + 1));
	i = 0;
	while (str1[i])
	{
		str3[i] = str1[i];
		i++;
	}
	j = 0;
	while (str2[j])
	{
		str3[i + j] = str2[j];
		j++;
	}
	str3[i + j] = '\0';
	return (str3);
}

char *ft_substr(char *str, int start, int len)
{
	int i;
	char *str2;

	str2 = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	while (len--)
	{
		str2[i] = str[start + i];
		i++;
	}
	str2[i] = '\0';
	return (str2);
}


int read_line(char **line, char **s)
{
	int len;
	char *aux;

	len = 0;
	while ((*s)[len] != '\0' && (*s)[len] != '\n')
	{
		len++;
	}
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

int get_next_line(char **line)
{
	int n_bytes;
	static char *s;
	char buff[BUFFER_SIZE + 1];
	char *aux;

	if (!line)
		return (-1);
	while (ft_strchr(s, '\n') == 0)
	{
		n_bytes = read(0, buff, BUFFER_SIZE);
		if (n_bytes < 0)
			return (-1);
		if (n_bytes == 0)
			break;
		buff[n_bytes] = '\0';
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
		return (read_line(line, &s));
}