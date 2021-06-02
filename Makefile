NAME = libftprintf.a

FUNCS =		utils/ft_printf.c				utils/ft_printf_utils.c\
			utils/parsing.c 				utils/distributor.c\
			output/d_i_u_output.c			output/s_output.c\
			output/percent_char_output.c	output/p_output.c\
			output/x_lower_output.c			output/x_upper_output.c

O_OBJS = $(patsubst %.c,%.o, $(FUNCS))

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(O_OBJS)
	ar rcs $(NAME) $?

%.o:%.c
	gcc $(FLAGS) -c $< -o $@

clean:
	@rm -f $(O_OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
