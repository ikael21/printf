#include "../ft_printf.h"

int	distributor(t_flags *flags, va_list ap)
{
	if (flags->sym == 'd' || flags->sym == 'i' || flags->sym == 'u')
		return (d_i_u_print(flags, ap));
	if (flags->sym == 's')
		return (s_print(flags, ap));
	if (flags->sym == 'c' || flags->sym == '%')
		return (persent_char_print(flags, ap));
	if (flags->sym == 'p')
		return (p_print(flags, ap));
	if (flags->sym == 'x')
		return (x_lower_print(flags, ap));
	if (flags->sym == 'X')
		return (x_upper_print(flags, ap));
	return (0);
}
