NAME = minishell

LIBFT		:= libft.a
LIBFT_PATH	:= "libraries/libft"

CC = cc

CFLAGS =  -Wall -Wextra -Werror -g3 #-fsanitize=address

BUILTINS = srcs/builtins/builtins_utils.c srcs/builtins/cd.c srcs/builtins/echo.c srcs/builtins/env.c srcs/builtins/exit.c srcs/builtins/export.c srcs/builtins/pwd.c srcs/builtins/unset.c srcs/builtins/export_utils.c

INPUT_VALIDATION = 	srcs/input_validation/has_invalid_redirections.c srcs/input_validation/has_misplaced_operators.c srcs/input_validation/has_unclosed_parenthesis.c srcs/input_validation/has_unclosed_parenthesis_utils.c srcs/input_validation/has_unclosed_quotes.c \
					srcs/input_validation/syntax_checker.c srcs/input_validation/syntax_checker_utils.c 

PARSING = 	srcs/parsing/parse_tokens.c srcs/parsing/parse_command.c srcs/parsing/parse_cmd_sep_args.c srcs/parsing/ast_utils.c srcs/parsing/parse_parenthese.c \
			srcs/parsing/parse_pipeline.c srcs/parsing/parse_logical_operator.c srcs/parsing/parse_redirection.c srcs/parsing/parse_redirection_utils.c srcs/parsing/parse_redirection_utils_2.c

TOKENIZATION = srcs/tokenization/ft_tokenize_handler.c srcs/tokenization/ft_tokenize_utils.c srcs/tokenization/ft_tokenize.c

EXECUTION = 	srcs/execution/execution.c srcs/execution/check_if_builtin.c srcs/execution/here_doc.c srcs/execution/execution_utils.c srcs/execution/execute_command.c srcs/execution/redirect_files.c\
				srcs/execution/execute_pipe.c srcs/execution/execute_logical_operator.c srcs/execution/execute_redirection.c srcs/execution/execute_parenthesis.c srcs/execution/get_cmd_path.c\
				srcs/execution/here_doc_utils.c srcs/execution/handle_errors.c srcs/execution/redirect_files_buildin.c 

EXPANDER = srcs/expander/expander.c srcs/expander/expand_env_variable.c srcs/expander/expand_env_variable_utils.c srcs/expander/expand_quotes.c srcs/expander/expand_wildcards.c srcs/expander/expand_wildcards_utils.c


SRCS = srcs/initialize_environment_list.c srcs/initialize_environment_utils.c srcs/minishell.c srcs/signal.c $(BUILTINS) $(INPUT_VALIDATION) $(PARSING) $(TOKENIZATION) $(EXECUTION) $(EXPANDER)


OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):  $(OBJS) 
	@make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_PATH)/$(LIBFT) -o $(NAME) -lreadline


clean:
	@make -C $(LIBFT_PATH) clean
	rm -f $(OBJS)

fclean:
	@make -C $(LIBFT_PATH) fclean
	rm -f $(NAME) $(OBJS)

re : fclean all clean

.PHONY: all clean fclean re