#include "../ft_printf.h"

static int	len_hex_digit(unsigned long n)
{
	int	result;

	result = 1;
	if (n / 16 != 0)
		result += len_hex_digit(n / 16);
	return (result);
}

static int	decimal_to_hex(unsigned int n)
{
	unsigned int	num;
	int				temp;

	num = n;
	if (n > 15)
		decimal_to_hex(n / 16);
	if (n % 16 == 10)
		write(1, "A", 1);
	if (n % 16 == 11)
		write(1, "B", 1);
	if (n % 16 == 12)
		write(1, "C", 1);
	if (n % 16 == 13)
		write(1, "D", 1);
	if (n % 16 == 14)
		write(1, "E", 1);
	if (n % 16 == 15)
		write(1, "F", 1);
	if (n % 16 < 10)
	{
		temp = (n % 16) + 48;
		write(1, &temp, 1);
	}
	return (len_hex_digit(num));
}

static int	printing_total_num(long n, t_flags *flags, int total_len)
{
	int	counter;

	counter = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		counter++;
		n *= -1;
		if (flags->zero_pad > 0 && flags->prec < 0)
			total_len--;
	}
	if (total_len > len_hex_digit(n))
	{
		while (total_len - len_hex_digit(n) > 0)
		{
			write(1, "0", 1);
			total_len--;
			counter++;
		}
		return (counter + decimal_to_hex(n));
	}
	return (counter + decimal_to_hex(n));
}

static int	final_number_print(long n, t_flags *flags, int total_len)
{
	int	counter;

	counter = 0;
	if (flags->width > total_len)
	{
		if (flags->adjust > 0)
		{
			counter += printing_total_num(n, flags, total_len);
			while (counter++ < flags->width)
				write(1, " ", 1);
			return (counter - 1);
		}
		if (flags->prec < 0 && flags->zero_pad > 0)
			return (printing_total_num(n, flags, flags->width));
		if (n < 0)
			flags->width--;
		while (counter++ < flags->width - total_len)
			write(1, " ", 1);
		return (counter + printing_total_num(n, flags, total_len) - 1);
	}
	return (counter + printing_total_num(n, flags, total_len));
}

int	x_upper_print(t_flags *flags, va_list ap)
{
	int		count;
	long	n;
	int		total_len;

	count = 0;
	n = va_arg(ap, unsigned int);
	if (flags->prec == 0 && n == 0)
	{
		while (count++ < flags->width)
			write(1, " ", 1);
		return (count - 1);
	}
	if (flags->prec > len_hex_digit(n))
		total_len = flags->prec;
	else
		total_len = len_hex_digit(n);
	return (final_number_print(n, flags, total_len));
}
