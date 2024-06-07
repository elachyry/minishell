/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:47:58 by melachyr          #+#    #+#             */
/*   Updated: 2024/06/07 00:57:07 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_listt
{
	char			*content;
	struct s_listt	*next;
}	t_listt;

int		ft_fetsh_new_line(t_listt *lst);
char	*ft_extract_line(t_listt *lst);
void	ft_get_string(t_listt *list, char *str);
int		ft_get_next_line_len(t_listt *lst);
void	ft_fix_lst(t_listt **lst);
char	*get_next_line(int fd);
void	ft_free_lst(t_listt **lst, t_listt *clean_node, char *buf);
void	ft_fill_lst(t_listt **lst, int fd, t_listt *last_node);
t_listt	*ft_lstlastt(t_listt *lst);
t_listt	*ft_lstneww(char *content);
void	ft_lstclearr(t_listt **lst);

#endif
