NAME = minishell

LIBFT		:= libft.a
LIBFT_PATH	:= "libraries/libft"

CC = cc

CFLAGS =  -Wall -Wextra -Werror -fsanitize=address -g3 

BUILTINS = srcs/builtins/builtins_utils.c srcs/builtins/cd.c srcs/builtins/echo.c srcs/builtins/env.c srcs/builtins/exit.c srcs/builtins/export.c srcs/builtins/pwd.c srcs/builtins/unset.c

INPUT_VALIDATION = srcs/input_validation/has_invalid_redirections.c srcs/input_validation/has_misplaced_operators.c srcs/input_validation/has_unclosed_parenthesis.c srcs/input_validation/has_unclosed_quotes.c srcs/input_validation/syntax_checker.c

PARSING = srcs/parsing/parse_tokens.c srcs/parsing/print_asp.c

TOKENIZATION = srcs/tokenization/ft_tokenize_handler.c srcs/tokenization/ft_tokenize_utils.c srcs/tokenization/ft_tokenize.c

EXECUTION = srcs/execution/execution.c

SRCS = srcs/initialize_environment_list.c srcs/minishell.c srcs/signal.c $(BUILTINS) $(INPUT_VALIDATION) $(PARSING) $(TOKENIZATION) $(EXECUTION)

# SRCS = $(wildcard srcs/*.c) $(wildcard srcs/builtins/*.c) $(wildcard srcs/input_validation/*.c) $(wildcard srcs/tokenization/*.c) $(wildcard srcs/parsing/*.c)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):  $(OBJS) 
#@make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_PATH)/$(LIBFT) -o $(NAME) -L /Users/akaddour/readline/lib -lreadline -lncurses


clean:
	@make -C $(LIBFT_PATH) clean
	rm -f $(OBJS)

fclean: clean
#@make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re : fclean all 

.PHONY: all clean fclean re