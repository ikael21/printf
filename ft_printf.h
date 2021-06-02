#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

typedef struct s_struct
{
	int		adjust;
	int		zero_pad;
	int		width;
	int		prec;
	char	sym;
}	t_flags;

t_flags	init_flags(void);
int		ft_printf(const char *string, ...);
int		parse_flags(char *ptr, t_flags *flags, va_list ap);
int		distributor(t_flags *flags, va_list ap);
int		d_i_u_print(t_flags *flags, va_list ap);
int		ft_atoi(const char *str);
int		ft_strlen(const char *str);
int		s_print(t_flags *flags, va_list ap);
int		persent_char_print(t_flags *flags, va_list ap);
int		p_print(t_flags *flags, va_list ap);
int		x_lower_print(t_flags *flags, va_list ap);
int		x_upper_print(t_flags *flags, va_list ap);
int		check_sym(t_flags *flags);

#endif
