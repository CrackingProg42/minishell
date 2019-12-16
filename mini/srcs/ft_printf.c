/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 09:53:24 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/03 09:54:11 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <stdarg.h>

int		ft_conv_d(long long  nbr , int mode);
int 	ft_conv_s(char *str, int point, int offset);
int		ft_conv_x(unsigned int nbr , int mode);

int		ft_atoi(char **str)
{
	int i;
	char *dest;
	int nbr;

	nbr = 0;
	dest = *str;
	i = 0;
	while (dest[i] >= '0' && dest[i] <= '9')
	{
		nbr *= 10;
		nbr += dest[i++] - '0';
	}
	*str = *str + i;
	return (nbr);
}

int 	ft_conv_s(char *str, int point,int  offset)
{
	int i;
	int	count;

	if (str == NULL)
		str = "(null)";
	i = 0;
	while (str[i])
		i++;
	offset = point < i && point != -1 ? offset - point : offset - i;
	count = offset >= 0 ? offset : 0;
	while(offset-- > 0)
			write(1, " ", 1);
	i = 0;
	if (point == -1)
		while (str[i])
				write(1, &str[i++],1);
	else
		while(str[i] && point--)
			write(1, &str[i++], 1);
	return (i + count);
}

int		ft_conv_x(unsigned int nbr , int mode)
{
	int i;
	char *c;

	c = "0123456789abcdef";
	i = 0;
	if (nbr > 15)
		i += ft_conv_x(nbr /16, mode);
	if (mode)
		write(1, &c[nbr % 16], 1);
	return (i +1);
}

int		ft_conv_d(long long  nbr , int mode)
{
	int i;
	char c;
	int moins;

	moins = nbr < 0 ? -1 : 1;
	nbr = nbr < 0 ? -nbr : nbr;
	i = 0;
	if (nbr > 9)
		i += ft_conv_d(nbr / 10, mode);
	c = nbr % 10 + '0';
	if (mode)
		write(1, &c, 1);
	return ((i + 1) * moins);
}

int 	ft_offset(int offset, int point, int i)
{
	int count;
 	int moins;
	
	count = 0;
	moins = i < 0 ? 1 : 0;
	i = i < 0 ? -i : i;
	if (point != -1 && point > i)
		offset -= point - i; 
	while (offset - count - moins  > i)
	{
		write(1," ",1);
		count++;
	}
	if(moins)
		write(1, "-", 1);
	while (point-- > i)
	{
		write(1,"0",1);
		count++;
	}
	return (count + moins);
}
	

int		ft_conv(va_list ap, char c, int offset, int point)
{
	int i;
	char *str;
	long long nd;
	unsigned int nx;
	int nbr;

	i = 0;
	nbr = 0;
	if (c == 's')
	{
		str = va_arg(ap, char *);
		i = ft_conv_s(str, point, offset);
	}
	if (c == 'd')
	{
		nd = (long long)va_arg(ap, int);
		i = ft_conv_d(nd, 0);
		nbr = ft_offset(offset, point , i);
		i = i < 0 ? -i : i;
		ft_conv_d(nd, i);
	}
	if (c == 'x')
	{
		nx =(unsigned int)va_arg(ap, int);
		i = ft_conv_x(nx, 0);
		i += ft_offset(offset, point , i);
		ft_conv_x(nx, i);
	}
	return (i + nbr);
}

int	ft_dete(va_list ap, char **str)
{
	int offset;
	int point;
	
	point = -1;
	offset = ft_atoi(str);
	if (**str == '.')
	{
		*str = *str +1;
		point = ft_atoi(str);
	}
	return(ft_conv(ap, **str, offset, point));
}

int		ft_printf(char *str, ...)
{
	va_list ap;
	int i;

	i = 0;
	va_start(ap, str);
	while(*str)
	{
		if (*str == '%')
		{
			str++;
			i += ft_dete(ap, &str);
			str++;
		}
		else
		{
			write(1, str++,1);
			i++;
		}
	}
	va_end(ap);
	return (i);
}
