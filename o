GITEX24MR_Confirmation_6397014639.pdf
GITEX24MR_Confirmation_6397015084.pdf
Makefile
ast.dot
commands_faild.txt
includes
init.sh
libraries
lol.c
minishell
p
srcs
NAME = minishell

LIBFT		:= libft.a
LIBFT_PATH	:= "libraries/libft"

CC = cc

CFLAGS =  -Wall -Wextra -Werror -fsanitize=address -g3 

BUILTINS = srcs/builtins/builtins_utils.c srcs/builtins/cd.c srcs/builtins/echo.c srcs/builtins/env.c srcs/builtins/exit.c srcs/builtins/export.c srcs/builtins/pwd.c srcs/builtins/unset.c

INPUT_VALIDATION = srcs/input_validation/has_invalid_redirections.c srcs/input_validation/has_misplaced_operators.c srcs/input_validation/has_unclosed_parenthesis.c srcs/input_validation/has_unclosed_quotes.c srcs/input_validation/syntax_checker.c

PARSING = 	srcs/parsing/parse_tokens.c srcs/parsing/parse_command.c srcs/parsing/parse_cmd_sep_args.c srcs/parsing/ast_utils.c srcs/parsing/parse_parenthese.c srcs/parsing/print_asp.c\
			srcs/parsing/parse_pipeline.c srcs/parsing/parse_logical_operator.c srcs/parsing/parse_redirection.c

TOKENIZATION = srcs/tokenization/ft_tokenize_handler.c srcs/tokenization/ft_tokenize_utils.c srcs/tokenization/ft_tokenize.c

EXECUTION = 	srcs/execution/execution.c srcs/execution/check_if_builtin.c srcs/execution/here_doc.c srcs/execution/execution_utils.c srcs/execution/execute_command.c srcs/execution/redirect_files.c\
				srcs/execution/execute_pipe.c srcs/execution/execute_logical_operator.c srcs/execution/execute_redirection.c srcs/execution/execute_parenthesis.c srcs/execution/get_cmd_path.c\
				srcs/execution/here_doc_utils.c

EXPANDER = srcs/expander/expander.c

GET_NEXT_LINE = libraries/get_next_line/get_next_line.c libraries/get_next_line/get_next_line_utils.c

SRCS = srcs/initialize_environment_list.c srcs/minishell.c srcs/signal.c $(BUILTINS) $(INPUT_VALIDATION) $(PARSING) $(TOKENIZATION) $(EXECUTION) $(EXPANDER) $(GET_NEXT_LINE)

# SRCS = $(wildcard srcs/*.c) $(wildcard srcs/builtins/*.c) $(wildcard srcs/input_validation/*.c) $(wildcard srcs/tokenization/*.c) $(wildcard srcs/parsing/*.c)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):  $(OBJS) 
#@make -C $(LIBFT_PATH)
#$(CC) $(CFLAGS) $(OBJS) $(LIBFT_PATH)/$(LIBFT) -o $(NAME) -L /Users/akaddour/readline/lib -lreadline -lncurses
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_PATH)/$(LIBFT) -o $(NAME) -L /Users/melachyr/readline/lib -lreadline -lncurses


clean:
#@make -C $(LIBFT_PATH) clean
	rm -f $(OBJS)

fclean:
#@make -C $(LIBFT_PATH) fclean
	rm -f $(NAME) $(OBJS)

re : fclean all clean

.PHONY: all clean fclean re