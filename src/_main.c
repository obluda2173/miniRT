/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:29:44 by erian             #+#    #+#             */
/*   Updated: 2025/02/27 18:50:33 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parsing.h"

// allocating memory for data

int main(int ac, char **av)
{
	t_data *data;

	data = ft_calloc(sizeof(t_data), 1);
	
	if (ac != 2)
	{
		ft_putstr_fd("Wrong number of arguments\n", STDERR_FILENO);
		return (1);
	}

	parse_scene(av[1], data);

	printf("success!!!\n");

	free_data(data);

	return 0;
}
