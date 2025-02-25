/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:33:05 by erian             #+#    #+#             */
/*   Updated: 2024/08/10 14:16:40 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif 

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_list
{
	char			*str_buf;
	struct s_list	*next;
}	t_list;

/* ************************************************************************** */
/* get_next_line_utils                                                      * */
/* ************************************************************************** */
int		found_new_line(t_list *list);
int		len_to_new_line(t_list *list);
void	copy_str(t_list *list, char *str);
void	dealloc(t_list **list, t_list *clear_node, char *buf);
t_list	*find_last_node(t_list *list);
/* ************************************************************************** */
/* get_next_line                                                            * */
/* ************************************************************************** */
void	polish_list(t_list **list);
void	append(t_list **list, char *buf);
void	create_list(t_list **list, int fd);
char	*get_next_line(int fd);
char	*get_line(t_list *list);

#endif