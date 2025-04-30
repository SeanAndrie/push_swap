/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:12:11 by sgadinga          #+#    #+#             */
/*   Updated: 2025/01/17 15:56:36 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_parse_by_spec(t_formatspec *fs, va_list args)
{
	int	len;

	len = 0;
	if (fs->specifier == 'c')
		len = ft_parse_char(fs, va_arg(args, int));
	else if (fs->specifier == 's')
		len = ft_parse_str(fs, va_arg(args, char *));
	else if (fs->specifier == 'd' || fs->specifier == 'i')
		len = ft_parse_dec_int(fs, va_arg(args, int));
	else if (fs->specifier == 'p')
		len = ft_parse_hex(fs, va_arg(args, void *));
	else if (fs->specifier == 'u')
		len = ft_parse_uint(fs, va_arg(args, unsigned int));
	else if (fs->specifier == 'x' || fs->specifier == 'X')
		len = ft_parse_hex(fs, va_arg(args, void *));
	else if (fs->specifier == '%')
		len = ft_putchar_len('%');
	else
		len = ft_putchar_len(fs->specifier);
	return (len);
}

int	ft_parse_format(const char *format, va_list args)
{
	int				len;
	t_formatspec	*fs;

	len = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			fs = ft_create_fs(&format);
			if (!fs)
			{
				len += ft_putchar_len('%');
				continue ;
			}
			len += ft_parse_by_spec(fs, args);
			free(fs);
		}
		else
			len += ft_putchar_len(*format);
		format++;
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int		len;
	va_list	args;

	if (!format)
		return (0);
	len = 0;
	va_start(args, format);
	len = ft_parse_format(format, args);
	va_end(args);
	return (len);
}

// int	main(void)
// {
// 	int		my_len;
// 	int		og_len;
// 	char	*format;
// 	int		n;

// 	n = 42;
// 	format = "%p\n";
// 	printf("\n");
// 	my_len = ft_printf(format, n);
// 	og_len = printf(format, n);
// 	printf("\nft_printf (No. of Chars Printed): %d\n", my_len);
// 	printf("printf (No. of Chars Printed): %d\n\n", og_len);
// 	return (0);
// }
