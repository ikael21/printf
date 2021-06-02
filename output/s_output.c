#include "../ft_printf.h"

static void	fill_in_null(char *ptr)
{
	ptr[0] = '(';
	ptr[1] = 'n';
	ptr[2] = 'u';
	ptr[3] = 'l';
	ptr[4] = 'l';
	ptr[5] = ')';
	ptr[6] = '\0';
}

static int	ft_putstr(char *s, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

static int	now_definitely_printing(char *str, t_flags *flags, int total_len)
{
	int	count;

	count = 0;
	if (flags->width > total_len)
	{
		if (flags->adjust > 0)
		{
			count += ft_putstr(str, total_len);
			while (count++ < flags->width)
				write(1, " ", 1);
			return (count - 1);
		}
		if (flags->zero_pad > 0)
		{
			while (count++ < flags->width - total_len)
				write(1, "0", 1);
			return (count + ft_putstr(str, total_len) - 1);
		}
		while (count++ < flags->width - total_len)
			write(1, " ", 1);
		return (count + ft_putstr(str, total_len) - 1);
	}
	return (ft_putstr(str, total_len));
}

int	s_print(t_flags *flags, va_list ap)
{
	char	*str;
	int		total_len;
	char	null[7];

	fill_in_null(null);
	str = va_arg(ap, char *);
	if (str == NULL)
		str = null;
	if (flags->prec < ft_strlen(str) && flags->prec > -1)
		total_len = flags->prec;
	else
		total_len = ft_strlen(str);
	return (now_definitely_printing(str, flags, total_len));
}
