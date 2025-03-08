/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:38:08 by kfreyer           #+#    #+#             */
/*   Updated: 2025/03/08 10:28:54 by erian            ###   ########.fr       */
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

# define MAX_FD 1024

/* type definitions */
typedef enum _OP
{
	GET_STASH = 0,
	SET_STASH,
	UPDATE_STASH,
	DELETE_STASH,
	FREE_STASH
}		t_op;

char	*get_next_line(int fd);
size_t	ft_strlen_kay(const char *s);
char	*ft_strdup_kay(const char *s);
char	*ft_get_empty_str(size_t n);
size_t	ft_strlcat_kay(char *dst, const char *src, size_t size);
void	*ft_memcpy_kay(void *dest, const void *src, size_t n);
char	*ft_strjoin_kay(char const *s1, char const *s2);
char	*ft_strchr_kay(const char *s, int c);
char	*ft_substr_kay(char const *s, unsigned int start, size_t len);
void	free_stash(int fd);

#endif