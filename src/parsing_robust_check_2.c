/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_robust_check_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:09:50 by erian             #+#    #+#             */
/*   Updated: 2025/03/08 12:35:10 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	a_check(char **array, t_data *data)
{
	if (array_size(array) != 3)
	{
		data->error = "Error: Invalid line format\n";
		return (false);
	}
	if (!valid_range_1(array[1]))
	{
		data->error = "Error: Invalid ambient light ratio range\n";
		return (false);
	}
	if (!valid_rgb(array[2]))
	{
		data->error = "Error: Invalid color format\n";
		return (false);
	}
	return (true);
}

bool	c_check(char **array, t_data *data)
{
	if (array_size(array) != 4)
	{
		data->error = "Error: Invalid line format\n";
		return (false);
	}
	if (!valid_range_2(array[1]))
	{
		data->error = "Error: Invalid camera coordinates\n";
		return (false);
	}
	if (!valid_range_2(array[2]))
	{
		data->error = "Error: Invalid camera orientation\n";
		return (false);
	}
	if (!valid_range_3(array[3]))
	{
		data->error = "Error: Invalid camera fov\n";
		return (false);
	}
	return (true);
}

bool	l_check(char **array, t_data *data)
{
	if (array_size(array) != 4)
	{
		data->error = "Error: Invalid line format\n";
		return (false);
	}
	if (!valid_range_2(array[1]))
	{
		data->error = "Error: Invalid source light coordinates\n";
		return (false);
	}
	if (!valid_range_1(array[2]))
	{
		data->error = "Error: Invalid source light ratio range\n";
		return (false);
	}
	if (!valid_rgb(array[3]))
	{
		data->error = "Error: Invalid color format\n";
		return (false);
	}
	return (true);
}

bool	sp_check(char **array, t_data *data)
{
	if (array_size(array) != 4)
	{
		data->error = "Error: Invalid line format\n";
		return (false);
	}
	if (!valid_range_2(array[1]))
	{
		data->error = "Error: Invalid sphere coordinates\n";
		return (false);
	}
	if (!valid_range_1(array[2]))
	{
		data->error = "Error: Invalid sphere diameter\n";
		return (false);
	}
	if (!valid_rgb(array[3]))
	{
		data->error = "Error: Invalid color format\n";
		return (false);
	}
	return (true);
}

bool	pl_check(char **array, t_data *data)
{
	if (array_size(array) != 4 && array_size(array) != 6)
	{
		data->error = "Error: Invalid line format\n";
		return (false);
	}
	if (!valid_range_2(array[1]) || !valid_range_2(array[2]))
	{
		data->error = "Error: Invalid plane coordinates \
			OR Invalid plane normal vector\n";
		return (false);
	}
	if (!valid_rgb(array[3]))
	{
		data->error = "Error: Invalid color format\n";
		return (false);
	}
	if ((array_size(array) == 6) && (!valid_xpm(array[4])
			|| !valid_xpm(array[5])))
	{
		data->error = "Error: Invalid texture format\n";
		return (false);
	}
	return (true);
}
