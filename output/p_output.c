#include "../ft_printf.h"

static int	len_hex_digit(unsigned long n)
{
	int	result;

	result = 1;
	if (n / 16 != 0)
		result += len_hex_digit(n / 16);
	return (result);
}

static int	decimal_to_hex(unsigned long n)
{
	unsigned long	num;
	int				temp;

	num = n;
	if (n > 15)
		decimal_to_hex(n / 16);
	if (n % 16 == 10)
		write(1, "a", 1);
	if (n % 16 == 11)
		write(1, "b", 1);
	if (n % 16 == 12)
		write(1, "c", 1);
	if (n % 16 == 13)
		write(1, "d", 1);
	if (n % 16 == 14)
		write(1, "e", 1);
	if (n % 16 == 15)
		write(1, "f", 1);
	if (n % 16 < 10)
	{
		temp = (n % 16) + 48;
		write(1, &temp, 1);
	}
	return (len_hex_digit(num));
}

static int	definitely_printing(t_flags *flags, void *ptr)
{
	int		count;

	count = 0;
	if (flags->width > len_hex_digit((unsigned long)ptr))
	{
		if (flags->adjust > 0)
		{
			write(1, "0x", 2);
			count += 2;
			count += decimal_to_hex((unsigned long)ptr);
			while (count++ < flags->width)
				write(1, " ", 1);
			return (count - 1);
		}
		while (count++ < flags->width - len_hex_digit((unsigned long)ptr) - 2)
			write(1, " ", 1);
		write(1, "0x", 2);
		count += 2;
		return (count + decimal_to_hex((unsigned long)ptr) - 1);
	}
	write(1, "0x", 2);
	return (decimal_to_hex((unsigned long)ptr) + 2);
}

static int	zero_prec_pointer(t_flags *flags)
{
	int	count;

	count = 0;
	if (flags->width > 2)
	{
		if (flags->adjust > 0)
		{
			write(1, "0x", 2);
			count += 2;
			while (count++ < flags->width)
				write(1, " ", 1);
			return (count - 1);
		}
		while (count++ < flags->width - 2)
			write(1, " ", 1);
		write(1, "0x", 2);
		return (count + 1);
	}
	write(1, "0x", 2);
	return (2);
}

int	p_print(t_flags *flags, va_list ap)
{
	int		count;
	void	*ptr;

	count = 0;
	ptr = va_arg(ap, void *);
	if (flags->prec == 0 && ptr == NULL)
		return (zero_prec_pointer(flags));
	return (definitely_printing(flags, ptr));
}
