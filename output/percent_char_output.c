#include "../ft_printf.h"

static int	print_spaces(int start, int end)
{
	int	count;

	count = 0;
	while (start < end)
	{
		write(1, " ", 1);
		start++;
		count++;
	}
	return (count);
}

static int	print_zero(int start, int end)
{
	int	count;

	count = 0;
	while (start < end)
	{
		write(1, "0", 1);
		start++;
		count++;
	}
	return (count);
}

static int	print_persent(char c, t_flags *flags)
{
	int	count;

	count = 0;
	if (flags->width > 1)
	{
		if (flags->adjust > 0)
		{
			write(1, &c, 1);
			count++;
			return (count + print_spaces(count, flags->width));
		}
		if (flags->zero_pad > 0)
		{
			count += print_zero(count, flags->width - 1);
			write(1, &c, 1);
			return (count + 1);
		}
		count += print_spaces(count, flags->width - 1);
		write(1, &c, 1);
		return (count + 1);
	}
	write(1, &c, 1);
	return (1);
}

static int	print_character(char c, t_flags *flags)
{
	int	count;

	count = 0;
	if (flags->width > 1)
	{
		if (flags->adjust > 0)
		{
			write(1, &c, 1);
			count++;
			return (count + print_spaces(count, flags->width));
		}
		count += print_spaces(count, flags->width - 1);
		write(1, &c, 1);
		return (count + 1);
	}
	write(1, &c, 1);
	return (1);
}

int	persent_char_print(t_flags *flags, va_list ap)
{
	char	c;

	if (flags->sym != '%')
		c = va_arg(ap, int);
	else
		c = '%';
	if (c != '%')
		return (print_character(c, flags));
	return (print_persent(c, flags));
}
