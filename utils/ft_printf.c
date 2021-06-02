#include "../ft_printf.h"

int	ft_printf(const char *string, ...)
{
	t_flags	flags;
	va_list	ap;
	char	*temp;
	int		counter;

	counter = 0;
	temp = (char *)string;
	va_start(ap, string);
	while (*temp != '\0')
	{
		if (*temp == '%' && *(temp + 1) != '\0')
		{
			flags = init_flags();
			temp += parse_flags(temp + 1, &flags, ap) + 2;
			counter += distributor(&flags, ap);
		}
		else
		{
			write(1, &*temp, 1);
			temp++;
			counter++;
		}
	}
	va_end(ap);
	return (counter);
}
