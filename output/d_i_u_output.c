#include "../ft_printf.h"

static int	len_digit(long num)
{
	int	result;

	result = 1;
	if (num / 10 != 0)
		result += len_digit(num / 10);
	return (result);
}

static int	ft_putnbr(long n)
{
	int		result;
	long	num;

	num = n;
	if (num / 10 != 0)
		ft_putnbr(num / 10);
	result = num % 10 + 48;
	write(1, &result, 1);
	return (len_digit(n));
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
	if (total_len > len_digit(n))
	{
		while (total_len - len_digit(n) > 0)
		{
			write(1, "0", 1);
			total_len--;
			counter++;
		}
		return (counter + ft_putnbr(n));
	}
	return (counter + ft_putnbr(n));
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

int	d_i_u_print(t_flags *flags, va_list ap)
{
	int		count;
	long	n;
	int		total_len;

	count = 0;
	if (flags->sym == 'u')
		n = va_arg(ap, unsigned int);
	else
		n = va_arg(ap, int);
	if (flags->prec == 0 && n == 0)
	{
		while (count++ < flags->width)
			write(1, " ", 1);
		return (count - 1);
	}
	if (flags->prec > len_digit(n))
		total_len = flags->prec;
	else
		total_len = len_digit(n);
	return (final_number_print(n, flags, total_len));
}
