/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_robust_check_3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:09:50 by erian             #+#    #+#             */
/*   Updated: 2025/03/08 12:40:17 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	cy_check(char **array, t_data *data)
{
	if (array_size(array) != 6)
	{
		data->error = "Error: Invalid line format\n";
		return (false);
	}
	if (!valid_range_2(array[1]) || !valid_range_2(array[2]))
	{
		data->error = "Error: Invalid cylinder coordinates \
			OR Invalid cylinder orientation\n";
		return (false);
	}
	if (!valid_range_1(array[3]) || !valid_range_1(array[4]))
	{
		data->error = "Error: Invalid cylinder diameter \
			OR Invalid cylinder height\n";
		return (false);
	}
	if (!valid_rgb(array[5]))
	{
		data->error = "Error: Invalid color format\n";
		return (false);
	}
	return (true);
}

bool	co_check(char **array, t_data *data)
{
	if (array_size(array) != 5)
	{
		data->error = "Error: Invalid line format\n";
		return (false);
	}
	if (!valid_range_2(array[1]) || !valid_range_2(array[2]))
	{
		data->error = "Error: Invalid cone coordinates \
			OR Invalid cone orientation\n";
		return (false);
	}
	if (!valid_range_1(array[3]))
	{
		data->error = "Error: Invalid cone angle\n";
		return (false);
	}
	if (!valid_rgb(array[4]))
	{
		data->error = "Error: Invalid color format\n";
		return (false);
	}
	return (true);
}
