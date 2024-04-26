NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror

LIBFT_SRCS = srcs/libft/ft_strlen.c srcs/libft/ft_strjoin.c
SRCS = srcs/minishell.c srcs/parsing/syntax_checker.c

OBJS = $(SRCS:.c=.o)
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_OBJS)
	$(CC) $(CFLAGS) $(LIBFT_OBJS) $(OBJS) -o $(NAME) -lreadline

clean:
	rm -f $(OBJS) $(LIBFT_OBJS)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re