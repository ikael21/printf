#include "../ft_printf.h"

static int	len_to_sym(char *ptr, char c)
{
	int		i;

	i = 0;
	while (ptr[i] != c && ptr[i] != '\0')
		i++;
	return (i);
}

static char	*parse_minus_zero(char *ptr, t_flags *flags)
{
	while (*ptr == '-' || *ptr == '0')
	{
		if (*ptr == '-')
			flags->adjust = 1;
		else if (flags->adjust < 1)
			flags->zero_pad = 1;
		ptr++;
	}
	return (ptr);
}

static char	*parse_precision(char *ptr, t_flags *flags, va_list ap)
{
	int	i;

	i = 0;
	if (*(ptr + 1) == '*')
	{
		i = va_arg(ap, int);
		flags->prec = i;
		return (ptr + 2);
	}
	(void)ap;
	flags->prec = ft_atoi(ptr + 1);
	ptr++;
	while (*ptr >= 48 && *ptr <= 57)
		ptr++;
	return (ptr);
}

static char	*parse_width(char *ptr, t_flags *flags, va_list ap)
{
	int	width;

	width = 0;
	if (*ptr == '*')
	{
		width = va_arg(ap, int);
		flags->width = width;
		return (ptr + 1);
	}
	(void)ap;
	flags->width = ft_atoi(ptr);
	while (*ptr >= 48 && *ptr <= 57)
		ptr++;
	return (ptr);
}

int	parse_flags(char *ptr, t_flags *flags, va_list ap)
{
	char	*temp;

	temp = parse_minus_zero(ptr, flags);
	temp = parse_width(temp, flags, ap);
	if (*temp == '.')
		temp = parse_precision(temp, flags, ap);
	flags->sym = *temp;
	if (flags->width < 0)
	{
		flags->width *= -1;
		flags->adjust = 1;
	}
	if (check_sym(flags) < 1)
		return (len_to_sym(ptr, flags->sym) - 1);
	return (len_to_sym(ptr, flags->sym));
}
