/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:30:51 by erian             #+#    #+#             */
/*   Updated: 2025/02/25 17:48:44 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>

# include "libft.h"
# include "get_next_line.h"

typedef struct s_data
{
	void	*obj_lst;
}			t_data;

// data.c
void free_split(char **array);
void    free_data(t_data *data);
void free_and_exit(t_data *data, char *error_msg);

#endif