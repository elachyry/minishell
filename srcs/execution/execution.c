/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:29:34 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/12 19:40:30 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_cmd_path(char	*args)
{
	char			*cmd;
	char			*path;
	
	// printf("path %s\n", g_shell_data.path[0]);
	// printf("cmd %s\n", args);
	cmd = ft_strrchr(args, '/');
	// printf("cmd %s\n", cmd);
	if (cmd)
	{
		if (access(cmd, X_OK) != -1 || access(args, X_OK) != -1)
		{
			g_shell_data.simple_cmd->cmd_path = args;
			return (1);
		}
	}
	else
	{
		cmd = args;
		while (*g_shell_data.path)
		{
			path = ft_strjoin(*g_shell_data.path, "/");
			path = ft_strjoin(path, cmd);
			if (access(path, X_OK) != -1)
			{
				g_shell_data.simple_cmd->cmd_path = path;
				return (1);
			}
			free(path);
			g_shell_data.path++;
		}
	}
	
	return (0);
}


t_files	*new_file_node(char *filename, t_token_type type)
{
	t_files	*node;

	node = malloc(sizeof(t_files));
	if (!node)
		return (NULL);
	node->filename = filename;
	node->type = type;
	node->next = NULL;
	node->is_opened = false;
	return (node);
}

char	*get_here_doc_name()
{
	char	*name;
	char	line[2];
	int		fd;
	int		c;
	
	name = malloc(sizeof(char) * 11);
	if (name == NULL)
		return (NULL);
	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
	{
		free(name);
		return (NULL);
	}
	c = 0;
	while (c < 11)
	{
		read(fd, line, 1);
		if (ft_isalpha(line[0]))
		{
			name[c] = line[0];
			c++;
		}
	}
	name[c] = '\0';
	close(fd);
	return (name);
}

// void	here_doc()
// {
// 	char	*str;
// 	int		infile;

// 	str = NULL;
// 	// infile = open(pipex.in_file_path, O_CREAT | O_RDWR, 0644);
// 	write(1, "> ", 2);
// 	while (1)
// 	{
// 		str = get_next_line(0);
// 		if (str)
// 		{
// 			if (ft_strcmp(pipex.delimiter, str) == 0)
// 			{
// 				free(str);
// 				break ;
// 			}
// 			write(1, "> ", 2);
// 			write(infile, str, ft_strlen(str));
// 			free(str);
// 		}
// 	}
// 	close(infile);
// }


t_files	*lst_file_last(t_files *head)
{
	if (!head)
		return (NULL);
	while (head->next != NULL)
	{
		// printf("head2 = %p\n", head);
		head = head->next;
	}
	return (head);
}

void	add_lst_file(t_files **head, t_files *node)
{
	t_files	*last;

	if (!head)
		return ;
	// printf("node = %p\n", node);
	// printf("head = %p\n", *head);
	if (!*head)
		*head = node;
	else
	{
		last = lst_file_last(*head);
		last->next = node;
	}
}


int execute_command(char **args)
{
	// dprintf(2, "execute_command %s\n", args[0]);
	// dprintf(2, "pre files %p\n", g_shell_data.simple_cmd->files);
	pid_t pid = fork();
	int status = 0;
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		t_files	*file = g_shell_data.simple_cmd->files;
		// dprintf(2, "1 files %p\n", file);
		while (file)
		{
			// dprintf(2, "file = %s\n", file->filename);
			// dprintf(2, "file type = %s\n", get_token_type_name(file->type));
			if (file->type == LessThanOperator)
			{
				// dprintf(2, "file in = %s\n", file->filename);
				int in_fd = open(file->filename, O_RDONLY);
				if (in_fd == -1)
				{
					if (!file->is_opened)
						perror(file->filename);
					close(in_fd);
					exit(EXIT_FAILURE);
				}
				if (dup2(in_fd, STDIN_FILENO) == -1)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
				close(in_fd);
			}
			else if (file->type == GreaterThanOperator)
			{
				// dprintf(2, "file out = %s\n", file->filename);
				int out_fd = open(file->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (out_fd == -1)
				{
					perror(file->filename);
					close(out_fd);
					exit(EXIT_FAILURE);
				}
				if (dup2(out_fd, STDOUT_FILENO) == -1)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
				close(out_fd);
			}
			else if (file->type == DoubleGreaterThanOperator)
			{
				// dprintf(2, "file appe = %s\n", file->filename);

				int fd = open(file->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (fd == -1)
				{
					perror(file->filename);
					exit(EXIT_FAILURE);
				}
				if (dup2(fd, STDOUT_FILENO) == -1)
				{
					perror("dup2");
					g_shell_data.simple_cmd->files = NULL;
					exit(EXIT_FAILURE);
				}
				close(fd);
			}
			file = file->next;
		}
		if (!get_cmd_path(args[0]))
		{
			ft_putstr_fd("command not found: ", 2);
			ft_putstr_fd(args[0], 2);
			ft_putstr_fd("\n", 2);
			exit(127);
		}
		execve(g_shell_data.simple_cmd->cmd_path, args, g_shell_data.environment);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		// printf("parent\n");
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			// dprintf(2, "status in wait %d\n", WEXITSTATUS(status));
			if (WEXITSTATUS(status) != 0)
				g_shell_data.simple_cmd->files = NULL;
		}
		// dup2(g_shell_data.saved_stdin, STDIN_FILENO);
		// // Restore stdout to original
		// dup2(g_shell_data.saved_stdout, STDOUT_FILENO);
	}
	return (WEXITSTATUS(status));
}


void execute_ast(t_ast_node *node) 
{
	if (node == NULL)
		return;
	// printf("cmd = %s\n", get_token_type_name(node->type));
	// int status = 0; 
		//dprintf(2, "node->arg %s | node->value %s\n", node->args != NULL ? node->args[0]: "NULL" , get_token_type_name(node->type));
	
	if (node->type == IDENTIFIER)
	{
		// dprintf(2, "before\n");
		g_shell_data.status = execute_command(node->args);
		// dprintf(2, "status in IDENTIFIER %d\n", g_shell_data.status);
	}
	else if (node->type == PipeSymbol)
	{
		// dprintf(2, "PipeSymbol\n");
		int pipefd[2];
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid_t left_pid = fork();
		if (left_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (left_pid == 0)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
			//dprintf(2, "left node pipe %s\n", get_token_type_name(node->left->type));
			// dprintf(2, "left %s\n", node->left->args[0]);
			execute_ast(node->left);
			// dprintf(2, "status in left %d\n", g_shell_data.status);
			exit(g_shell_data.status);
		}
		
		pid_t right_pid = fork();
		if (right_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (right_pid == 0)
		{
			close(pipefd[1]); 
			dup2(pipefd[0], STDIN_FILENO); 
			close(pipefd[0]); 
			// dprintf(2, "right %s\n", get_token_type_name(node->right->type));
			execute_ast(node->right); 
			// dprintf(2, "status in right %d\n", g_shell_data.status);
			exit(g_shell_data.status);
		}

		close(pipefd[0]); 
		close(pipefd[1]); 
		int left_status, right_status;
		waitpid(left_pid, &left_status, WCONTINUED);
		waitpid(right_pid, &right_status, WCONTINUED);

		if (WIFEXITED(right_status))
			g_shell_data.status = right_status;
		else
			g_shell_data.status = 1; 

	}
	else if (node->type == LogicalAnd)
	{
		// dprintf(2, "LogicalAnd\n");
		execute_ast(node->left);
		
		g_shell_data.simple_cmd->files = NULL;
		int left_status = g_shell_data.status;
		// dprintf(2, "status %d\n", left_status);
		if (left_status == 0)
			execute_ast(node->right);
		else if (node->right
			&& (node->right->type == LogicalAnd || node->right->type == LogicalOr))
		{
			// dprintf(2, "yesss %s\n", get_token_type_name(node->right->type));
			if (node->right->type == LogicalAnd)
			{
				if (left_status == 0)
					execute_ast(node->right->left);
			}
			if (node->right->type == LogicalOr)
			{
				if (left_status != 0)
					execute_ast(node->right->right);
			}
		}
	}
	else if (node->type == LogicalOr)
	{
		// dprintf(2, "LogicalOr\n");

		execute_ast(node->left);
		g_shell_data.simple_cmd->files = NULL;
		int left_status = g_shell_data.status;
		// dprintf(2, "status %d\n", left_status);
		if (left_status != 0)
		{
			// dprintf(2, "hiii\n");
			execute_ast(node->right);
		}
		else if (node->right
			&& (node->right->type == LogicalAnd || node->right->type == LogicalOr))
		{
			dprintf(2, "yesss %s\n", get_token_type_name(node->right->type));
			if (node->right->type == LogicalAnd)
			{
				if (left_status == 0)
					execute_ast(node->right->right);
			}
			if (node->right->type == LogicalOr)
			{
				if (left_status != 0)
					execute_ast(node->right->left);
			}
		}
		
	}
	else if (node->type == LessThanOperator)
	{
		// int saved_stdin = dup(STDIN_FILENO);
		// int saved_stdout = dup(STDOUT_FILENO);
		// dprintf(2, "LessThanOperator\n");
		// int fd = open(node->right->args[0], O_RDONLY);
		// dprintf(2, "fd = %d\n", fd);
		// g_shell_data.simple_cmd->in_file = node->right->args[0];
		t_files	*file = new_file_node(node->right->args[0], LessThanOperator);
		// printf("file2 = %p\n", file);
		add_lst_file(&g_shell_data.simple_cmd->files, file);
		g_shell_data.simple_cmd->is_first++;
		// if (!node->right->right && !node->left && g_shell_data.simple_cmd->is_first == 1)
		// {
			int fd = open(node->right->args[0], O_RDONLY);
			if (fd == -1)
			{
				t_files	*last = lst_file_last(g_shell_data.simple_cmd->files);
				last->is_opened = true;
				perror(node->right->args[0]);
				close(fd);
				g_shell_data.status = 1;
				return ;
			}
			close(fd);
		// }
		// g_shell_data.simple_cmd->in_fd = fd;
		// if (fd == -1) {
		// 	perror(node->right->args[0]);
		// 	return ;
		// }
		// dprintf(2, "in %s = %d\n", node->right->args[0], fd);
		// dup2(fd, STDIN_FILENO);
		// close(fd); 
		// dprintf(2, "right right %s \n" , get_token_type_name(node->right->right->type));
		execute_ast(node->right->right);
		execute_ast(node->left);
		// dup2(saved_stdin, STDIN_FILENO);
		// Restore stdout to original
		// dup2(saved_stdout, STDOUT_FILENO);
	}
	else if (node->type == GreaterThanOperator)
	{
		// dprintf(2, "GreaterThanOperator \n" );
		// int saved_stdin = dup(STDIN_FILENO);
		// int saved_stdout = dup(STDOUT_FILENO);
		// int fd = open(node->right->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		// g_shell_data.simple_cmd->out_file = node->right->args[0];
		t_files	*file = new_file_node(node->right->args[0], GreaterThanOperator);
		// printf("file = %p\n", file);
		add_lst_file(&g_shell_data.simple_cmd->files, file);
		g_shell_data.simple_cmd->is_first++;
		// if (!node->right->right && !node->left && g_shell_data.simple_cmd->is_first == 1)
		// {
			// printf("inside if\n");
			int fd = open(node->right->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			close(fd);
		// }
		// g_shell_data.simple_cmd->out_fd = fd;
		// if (fd == -1) {
		// 	perror(node->right->args[0]);
		// 	return ;
		// }
		// dprintf(2, "out %s = %d\n", node->right->args[0], fd);
		// dup2(fd, STDOUT_FILENO);
		// close(fd); 
		// dprintf(2, "right right %s \n" , get_token_type_name(node->right->right->type));
		execute_ast(node->right->right);
		execute_ast(node->left); 
		// dup2(saved_stdin, STDIN_FILENO);
		// Restore stdout to original
		// dup2(saved_stdout, STDOUT_FILENO);
	}
	else if (node->type == DoubleLessThanOperator)
	{
		// dprintf(2, "DoubleLessThanOperator\n");
		
		
		// t_files
		// execute_ast(node->left);
		
	}
	else if (node->type == DoubleGreaterThanOperator)
	{
		// dprintf(2, "DoubleGreaterThanOperator\n");

		// int saved_stdin = dup(STDIN_FILENO);
		// int saved_stdout = dup(STDOUT_FILENO);
		// g_shell_data.simple_cmd->out_file = node->right->args[0];
		t_files	*file = new_file_node(node->right->args[0], DoubleGreaterThanOperator);
		add_lst_file(&g_shell_data.simple_cmd->files, file);
		g_shell_data.simple_cmd->is_first++;
		// if (!node->right->right && !node->left && g_shell_data.simple_cmd->is_first == 1)
		// {
			int fd = open(node->right->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
			close(fd);
		// }
		// int fd = open(node->right->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
		// if (fd == -1) {
		// 	perror("open");
		// 	exit(EXIT_FAILURE);
		// }
		// dup2(fd, STDOUT_FILENO);
		// close(fd); 
		execute_ast(node->right->right);
		execute_ast(node->left); 
		// dup2(saved_stdin, STDIN_FILENO);
		// // Restore stdout to original
		// dup2(saved_stdout, STDOUT_FILENO);
	}
	else if (node->type == OpeningParenthesis)
	{
		
		execute_ast(node->left);
	}

	// g_shell_data.status = status;
}


void	execution(void)
{
	// printf("nbr cmd = %d\n", g_shell_data.nbr_cmd);
	// if (g_shell_data.nbr_cmd == 1)
	// {
	// 	if (check_if_builtin(g_shell_data.ast->args[0]))
	// 		execute_builtin(g_shell_data.ast->args);
	// 	else
	// 		execute_single_cmd();
	// }
	g_shell_data.simple_cmd->files = NULL;
	g_shell_data.simple_cmd->is_first = 0;
	execute_ast(g_shell_data.ast); 
}
