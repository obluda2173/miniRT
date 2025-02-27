/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:33:05 by erian             #+#    #+#             */
/*   Updated: 2025/02/27 20:22:29 by erian            ###   ########.fr       */
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
# include <stdio.h>

typedef struct s_liste
{
	char			*str_buf;
	struct s_liste	*next;
}	t_liste;

/* ************************************************************************** */
/* get_next_line_utils                                                      * */
/* ************************************************************************** */
int		found_new_line(t_liste *list);
int		len_to_new_line(t_liste *list);
void	copy_str(t_liste *list, char *str);
void	dealloc(t_liste **list, t_liste *clear_node, char *buf);
t_liste	*find_last_node(t_liste *list);
/* ************************************************************************** */
/* get_next_line                                                            * */
/* ************************************************************************** */
void	polish_list(t_liste **list);
void	append(t_liste **list, char *buf);
void	create_list(t_liste **list, int fd);
char	*get_next_line(int fd);
char	*get_line_cstm(t_liste *list);

#endif