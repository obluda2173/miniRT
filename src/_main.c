/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:29:44 by erian             #+#    #+#             */
/*   Updated: 2025/02/25 18:18:15 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parsing.h"

// allocating memory for data

int main(int ac, char **av)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (ac != 2)
	{
		ft_putstr_fd("Wrong number of arguments\n", STDERR_FILENO);
		return (1);
	}

	parse(av[1], data);

	printf("success!!!\n");

	free_data(data);

	return 0;
}

/*
what I left on:

fix the leaks if I pass " " in the .rt file
check values on rgb and other values (like ration for example) given their values range

*/
