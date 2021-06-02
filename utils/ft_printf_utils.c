#include "../ft_printf.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	isminus;
	int	result;

	i = 0;
	isminus = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			isminus = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result * isminus);
}

t_flags	init_flags(void)
{
	t_flags	flags;

	flags.adjust = 0;
	flags.zero_pad = 0;
	flags.width = 1;
	flags.prec = -1;
	flags.sym = ' ';
	return (flags);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	check_sym(t_flags *flags)
{
	if (flags->sym == 'd' || flags->sym == 'i' || flags->sym == 'u')
		return (1);
	if (flags->sym == 's')
		return (1);
	if (flags->sym == 'c' || flags->sym == '%')
		return (1);
	if (flags->sym == 'p')
		return (1);
	if (flags->sym == 'x')
		return (1);
	if (flags->sym == 'X')
		return (1);
	return (0);
}
