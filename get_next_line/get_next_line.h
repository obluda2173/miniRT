/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:38:08 by kfreyer           #+#    #+#             */
/*   Updated: 2025/02/25 16:58:35 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

#  define MAX_FD 1024

/* type definitions */
typedef enum _OP
{
	GET_STASH = 0,
	SET_STASH,
	UPDATE_STASH,
	DELETE_STASH
}		t_op;

char *get_next_line(int fd);
size_t	ft_strlen_kay(const char *s);
char	*ft_strdup(const char *s);
char	*ft_get_empty_str(size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);

# endif