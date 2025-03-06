/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_robust_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:09:50 by erian             #+#    #+#             */
/*   Updated: 2025/03/06 17:11:09 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	valid_xpm(char *str)
{
	int		i;
	char	**xpm;

	i = -1;
	while (str[++i])
	{
		if (!ft_isprint(str[i]) || ft_str_chr_count(str, '.') != 1)
			return (false);
	}
	xpm = ft_split(str, '.');
	if (!xpm || array_size(xpm) != 2 || ft_strcmp(xpm[1], "xpm") != 0)
	{
		free_split(xpm);
		return (false);
	}
	free_split(xpm);
	return (true);
}

static bool	valid_rgb(char *str)
{
	int		i;
	char	**rgb;

	i = -1;
	while (str[++i])
	{
		if ((!ft_isdigit(str[i]) && str[i] != ',') || ft_str_chr_count(str, ',') != 2)
			return (false);
	}
	rgb = ft_split(str, ',');
	if (!rgb || array_size(rgb) != 3
		|| ft_strlen(rgb[0]) == 0 || ft_strlen(rgb[0]) > 3
		|| ft_strlen(rgb[1]) == 0 || ft_strlen(rgb[1]) > 3
		|| ft_strlen(rgb[2]) == 0 || ft_strlen(rgb[2]) > 3)
	{
		free_split(rgb);
		return (false);
	}
	free_split(rgb);
	return (true);
}

static bool	valid_range_1(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if ((!ft_isdigit(str[i]) && str[i] != '.') || ft_str_chr_count(str, '.') > 1)
			return (false);
	}
	return (true);
}

static bool	valid_range_2(char *str)
{
	int		i;
	char	**ranges;

	i = -1;
	while (str[++i])
	{
		if ((!ft_isdigit(str[i]) && str[i] != '.' && str[i] != ',' && str[i] != '-') || ft_str_chr_count(str, ',') != 2)
			return (false);
	}
	ranges = ft_split(str, ',');
	if (!ranges || array_size(ranges) != 3
		|| ft_strlen(ranges[0]) == 0 || ft_strlen(ranges[1]) == 0 || ft_strlen(ranges[2]) == 0)
	{
		free_split(ranges);
		return (false);
	}
	free_split(ranges);
	return (true);
}

static bool	valid_range_3(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
	}
	return (true);
}


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
	if (!valid_range_2(array[1]))
	{
		data->error = "Error: Invalid plane coordinates\n";
		return (false);
	}
	if (!valid_range_2(array[2]))
	{
		data->error = "Error: Invalid plane normal vector\n";
		return (false);
	}
	if (!valid_rgb(array[3]))
	{
		data->error = "Error: Invalid color format\n";
		return (false);
	}
	if (array_size(array) == 6)
	{
		if (!valid_xpm(array[4]) || !valid_xpm(array[5]))
		{
			data->error = "Error: Invalid texture format\n";
			return (false);
		}
	}
	return (true);
}

bool	cy_check(char **array, t_data *data)
{
	if (array_size(array) != 6)
	{
		data->error = "Error: Invalid line format\n";
		return (false);
	}
	if (!valid_range_2(array[1]))
	{
		data->error = "Error: Invalid cylinder coordinates\n";
		return (false);
	}
	if (!valid_range_2(array[2]))
	{
		data->error = "Error: Invalid cylinder orientation\n";
		return (false);
	}
	if (!valid_range_1(array[3]))
	{
		data->error = "Error: Invalid cylinder diameter\n";
		return (false);
	}
	if (!valid_range_1(array[4]))
	{
		data->error = "Error: Invalid cylinder height\n";
		return (false);
	}
	if (!valid_rgb(array[5]))
	{
		data->error = "Error: Invalid color format\n";
		return (false);
	}
	return (true);
}
