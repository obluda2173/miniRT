/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_robust_check_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:09:50 by erian             #+#    #+#             */
/*   Updated: 2025/03/08 12:31:30 by erian            ###   ########.fr       */
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

bool	valid_rgb(char *str)
{
	int		i;
	char	**rgb;

	i = -1;
	while (str[++i])
	{
		if ((!ft_isdigit(str[i]) && str[i] != ',')
			|| ft_str_chr_count(str, ',') != 2)
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

bool	valid_range_1(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if ((!ft_isdigit(str[i]) && str[i] != '.')
			|| ft_str_chr_count(str, '.') > 1)
			return (false);
	}
	return (true);
}

bool	valid_range_2(char *str)
{
	int		i;
	char	**ranges;

	i = -1;
	while (str[++i])
	{
		if ((!ft_isdigit(str[i]) && str[i] != '.' && str[i] != ','
				&& str[i] != '-') || ft_str_chr_count(str, ',') != 2)
			return (false);
	}
	ranges = ft_split(str, ',');
	if (!ranges || array_size(ranges) != 3
		|| ft_strlen(ranges[0]) == 0 || ft_strlen(ranges[1]) == 0
		|| ft_strlen(ranges[2]) == 0)
	{
		free_split(ranges);
		return (false);
	}
	free_split(ranges);
	return (true);
}

bool	valid_range_3(char *str)
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
