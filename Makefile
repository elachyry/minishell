NAME = minishell

LIBFT		:= libft.a
LIBFT_PATH	:= "libraries/libft"

CC = cc

CFLAGS =  -Wall -Wextra -Werror -fsanitize=address -g3 

SRCS = $(wildcard srcs/*.c) $(wildcard srcs/builtins/*.c) $(wildcard srcs/input_validation/*.c) $(wildcard srcs/tokenization/*.c) $(wildcard srcs/parsing/*.c)

OBJS = $(SRCS:.c=.o)
LIBFT_OBJS = $(.c=.o)

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_PATH)/$(LIBFT) -o $(NAME) -L /Users/akaddour/readline/lib -lreadline -lncurses

clean:
	@make -C $(LIBFT_PATH) clean
	rm -f $(OBJS) $(LIBFT_OBJS)

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re