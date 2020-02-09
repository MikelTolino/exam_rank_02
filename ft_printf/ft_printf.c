/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmateo-t <mmateo-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 20:26:35 by mmateo-t          #+#    #+#             */
/*   Updated: 2020/01/30 10:11:39 by mmateo-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

typedef struct parameters
{
	char type;
	unsigned int len;
	unsigned int width;
	unsigned int precision;
	unsigned int precision_width;
	char *str;
	char *final_str;
	unsigned int int_neg;
	va_list ap;

} parameters;

void print_char(parameters *param, int count, char c)
{
	int i;

	i = 0;
	while (i < count)
	{
		write(1, &c, 1);
		param->len++;
		i++;
	}
	
}

void print_str(parameters *param, int count)
{
	while (count--)
	{
		write(1, param->final_str++, 1);
		param->len++;
	}
}

unsigned int ft_strlen(char *str)
{
	unsigned int len;

	len = 0;
	while (str[len])
	{
		len++;
	}
	return (len);
}

void calculate_print_fields(parameters *param)
{
	unsigned int zeros;
	unsigned int spaces;
	unsigned int size;
	unsigned int higher;

	zeros = 0;
	spaces = 0;
	higher = 0;
	size = ft_strlen(param->final_str);

	if (param->type == 's')
	{
		if (param->precision)
		{
			if (!param->precision_width)
			{
				size = 0;
			}
			if (param->precision_width < size)
			{
				size = param->precision_width;
			}
		}
		if (param->width > size)
		{
			spaces = param->width - size;
		}
	}
	else
	{
		if (param->precision)
		{
			if (!param->precision_width && param->final_str[0] == '0')
			{
				size = 0;
			}
			if (param->precision_width > size)
			{
				zeros = param->precision_width - size;
				higher = param->precision_width;
			}
			else
			{
				higher = size;
			}
			if (param->width > higher)
			{
				spaces = param->width - higher;
			}
		}
		else
		{
			spaces = param->width - size;
		}
	}
	print_char(param, spaces, ' ');
	if (param->int_neg)
		print_char(param, 1, '-');
	print_char(param, zeros, '0');
	print_str(param, size);
	
}

char *ft_itoa(long int nb)
{
	long int num;
	unsigned int len;
	char *str;

	len = 0;
	num = nb;
	if (!num)
		len++;
	while (num)
	{
		len++;
		num /= 10;
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	num = nb;
	str[len] = '\0';
	if (!num)
	{
		str[0] = '0';
	}
	while (num)
	{
		str[--len] = num % 10 + '0';
		num /= 10;
	}
	return (str);
}

char *ft_itoa_base(unsigned int nb)
{
	unsigned int num;
	unsigned int len;
	char *str;
	char *base;

	base = "0123456789abcdef";
	len = 0;
	num = nb;
	if (!num)
		len++;
	while (num)
	{
		len++;
		num /= 16;
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	num = nb;
	str[len] = '\0';
	if (!num)
	{
		str[0] = '0';
	}
	while (num)
	{
		str[--len] = base[num % 16];
		num /= 16;
	}
	return (str);
}

void get_width(parameters *param)
{
	param->width = 0;
	while (*param->str <= '9' && *param->str >= '0')
	{
		param->width = param->width * 10 + (*param->str - '0');
		param->str++;
	}
}

void get_precision(parameters *param)
{
	param->precision = 0;
	param->precision_width = 0;
	if (*param->str == '.')
	{
		param->precision = 1;
		param->str++;
		while (*param->str <= '9' && *param->str >= '0')
		{
			param->precision_width = param->precision_width * 10 + (*param->str - '0');
			param->str++;
		}
	}
}

void convert_to_char(parameters *param)
{
	param->type = *param->str;
	param->int_neg = 0;
	if (*param->str == 's')
	{
		param->final_str = va_arg(param->ap, char *);
		if (!param->final_str)
			param->final_str = "(null)";
	}
	if (*param->str == 'd')
	{
		long int num;

		num = (long int)va_arg(param->ap, int);
		if (num < 0)
		{
			num = num * -1;
			param->int_neg = 1;
		}
		param->final_str = ft_itoa(num);
	}
	if (*param->str == 'x')
	{
		unsigned int num;

		num = va_arg(param->ap, unsigned int);
		param->final_str = ft_itoa_base(num);
	}
	param->str++;
}

void format(parameters *param)
{
	get_width(param);
	get_precision(param);
	convert_to_char(param);
	calculate_print_fields(param);
}

int ft_printf(const char *string, ...)
{
	parameters param;

	param.len = 0;
	param.str = (char*)string;
	va_start((param.ap), string);
	while (*param.str)
	{
		while (*param.str == '%')
		{
			param.str++;
			format(&param);
			if (!*param.str)
				return (param.len);
		}
		write(1, param.str++, 1);
		param.len++;
	}
	va_end(param.ap);
	return (param.len);
}