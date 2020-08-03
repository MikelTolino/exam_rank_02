/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 03:59:56 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/30 02:30:02 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include<unistd.h>
# include<stdarg.h>
# include<stdlib.h>
# include<fcntl.h>
# include<stdio.h>
# define BUFF_SIZE 256

int get_next_line(char **line);

#endif