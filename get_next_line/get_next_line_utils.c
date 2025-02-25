/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 22:02:11 by erian             #+#    #+#             */
/*   Updated: 2024/08/10 14:14:43 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_new_line(t_list *list)
{
	int	i;

	if (!list)
		return (0);
	while (list)
	{
		i = -1;
		while (list->str_buf[++i] && i < BUFFER_SIZE)
			if (list->str_buf[i] == '\n')
				return (1);
		list = list->next;
	}
	return (0);
}

t_list	*find_last_node(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

int	len_to_new_line(t_list *list)
{
	int	count;
	int	i;

	count = 0;
	while (list)
	{
		i = 0;
		while (list->str_buf[i])
		{
			if (list->str_buf[i] == '\n')
				return (count + i + 1);
			i++;
		}
		list = list->next;
		count += i;
	}
	return (count);
}

void	copy_str(t_list *list, char *str)
{
	int	i;
	int	k;

	k = 0;
	while (list)
	{
		i = 0;
		while (list->str_buf[i])
		{
			str[k++] = list->str_buf[i];
			if (list->str_buf[i++] == '\n')
			{
				str[k] = '\0';
				return ;
			}
		}
		list = list->next;
	}
	str[k] = '\0';
}

void	dealloc(t_list **list, t_list *clear_node, char *buf)
{
	t_list	*tmp;

	if (!*list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->str_buf);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (clear_node->str_buf[0])
		*list = clear_node;
	else
	{
		free(buf);
		free(clear_node);
	}
}
