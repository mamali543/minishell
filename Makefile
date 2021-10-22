NAME = minishell

LIBDIR = ft_libft

LIB = ft_libft/*.c

MINIFILES = minishell.c env_tools.c expander.c tools.c list_function.c parser_tools.c red_tools.c print_functions.c echo.c

FLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) :
	gcc $(MINIFILES) $(FLAGS) $(LIB) -o $(NAME) -L/usr/include -lreadline -fsanitize=address -g
fclean:
	rm -rf minishell

re: fclean all