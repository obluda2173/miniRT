/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:29:20 by erian             #+#    #+#             */
/*   Updated: 2025/02/27 20:21:44 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	polish_list(t_liste **list)
{
	t_liste	*last_node;
	t_liste	*clean_node;
	int		i;
	int		k;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_liste));
	if (!buf || !clean_node)
		return ;
	last_node = find_last_node(*list);
	i = 0;
	k = 0;
	while (last_node->str_buf[i] && last_node->str_buf[i] != '\n')
		++i;
	while (last_node->str_buf[i] && last_node->str_buf[++i])
		buf[k++] = last_node->str_buf[i];
	buf[k] = '\0';
	clean_node->str_buf = buf;
	clean_node->next = NULL;
	dealloc(list, clean_node, buf);
}

char	*get_line_cstm(t_liste *list)
{
	int		str_len;
	char	*next_str;

	if (!list)
		return (NULL);
	str_len = len_to_new_line(list);
	next_str = malloc(str_len + 1);
	if (!next_str)
		return (NULL);
	copy_str(list, next_str);
	return (next_str);
}

void	append(t_liste **list, char *buf)
{
	t_liste	*new_node;
	t_liste	*last_node;

	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_liste));
	if (!new_node)
		return ;
	if (!last_node)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->str_buf = buf;
	new_node->next = NULL;
}

void	create_list(t_liste **list, int fd)
{
	int		char_read;	
	char	*buf;

	while (!found_new_line(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (!char_read)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		append(list, buf);
	}
}

char	*get_next_line(int fd)
{
	static t_liste	*list = NULL;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	create_list(&list, fd);
	if (!list)
		return (NULL);
	next_line = get_line_cstm(list);
	polish_list(&list);
	return (next_line);
}

// int main(void)
// {
// 	char	*line;
// 	int		fd = open("file.txt", O_RDONLY);

// 	if (fd < 0)
// 		printf("File was not open.\n");

// 	line = get_next_line(-1);
// 	printf("fd = -1: %s\n", line);
// 	free(line);

// 	line = get_next_line(fd);
// 	printf("Line 1: %s", line);
// 	free(line);

// 	line = get_next_line(fd);
// 	printf("Line 2: %s", line);
// 	free(line);

// 	line = get_next_line(fd);
// 	printf("Line 3: %s", line);
// 	free(line);

// 	line = get_next_line(fd);
// 	printf("Line 4: %s", line);
// 	free(line);

// 	close(fd);
// 	return (0);
// }