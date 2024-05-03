NAME = minishell

CC = cc

CFLAGS =  -fsanitize=address -g3 -Wall -Wextra -Werror 

LIBFT_SRCS = srcs/libft/ft_strlen.c srcs/libft/ft_strjoin.c srcs/libft/ft_strtrim.c srcs/libft/ft_strchr.c\
			 srcs/libft/ft_strlcpy.c srcs/libft/ft_strrchr.c
SRCS =  srcs/minishell.c srcs/parsing/syntax/syntax_checker.c srcs/parsing/syntax/has_invalid_redirections.c srcs/parsing/syntax/has_unclosed_quotes.c\
		srcs/parsing/syntax/has_misplaced_operators.c srcs/parsing/tokenization/ft_tokenize.c srcs/parsing/tokenization/ft_tokenize_handler.c\
		srcs/parsing/tokenization/ft_tokenize_utils.c srcs/parsing/ast/print_asp.c srcs/parsing/ast/parse_tokens.c

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