/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmateo-t <mmateo-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 23:10:43 by mmateo-t          #+#    #+#             */
/*   Updated: 2020/01/29 10:50:17 by mmateo-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int is_not_repeated(char **argv, int i, int str)
{
	int j;

	j = i;
	while (i > 0)
	{
		if (argv[str][j] == argv[str][i - 1])
			return (0);
		i--;
	}
	return (1);
}

int is_repeated_str1(char **argv, int j)
{
	int i;

	i = 0;
	while (argv[1][i])
	{
		if (argv[1][i] == argv[2][j])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	int i;
	int j;

	i = 0;
	if (argc != 3)
	{
		write(1, "\n", 1);
		return (0);
	}
	while (argv[1][i])
	{
		j = 0;
		while (argv[2][j])
		{
			if (is_not_repeated(argv, i, 1))
			{
				write(1, &argv[1][i], 1);
				break;
			}
			j++;
		}
		i++;
	}
	j = 0;
	while (argv[2][j])
	{
		i = 0;
		while (argv[1][i])
		{
			if (is_not_repeated(argv, j, 2) && !is_repeated_str1(argv, j))
			{
				write(1, &argv[2][j], 1);
				break;
			}
			i++;
		}
		j++;
	}
	write(1, "\n", 1);
	return (0);
}
