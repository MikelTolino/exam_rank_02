/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmateo-t <mmateo-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 21:50:57 by mmateo-t          #+#    #+#             */
/*   Updated: 2020/01/29 10:46:44 by mmateo-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int is_not_repeated(char **argv, int i)
{
	int j;

	j = i;
	while (i > 0)
	{
		if (argv[1][i - 1] == argv[1][j])
			return (0);
		i--;
	}
	return (1);
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
			if (argv[1][i] == argv[2][j] && is_not_repeated(argv, i))
			{
				write(1, &argv[1][i], 1);
				break;
			}
			j++;
		}
		i++;
	}
	write(1, "\n", 1);
	return (0);
}
