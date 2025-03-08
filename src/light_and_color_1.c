/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_and_color_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:37:19 by erian             #+#    #+#             */
/*   Updated: 2025/03/08 11:09:05 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

int	color_to_int(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

t_color	int_to_color(int integer)
{
	return ((t_color){(integer >> 16) & 0xFF,
		(integer >> 8) & 0xFF, integer & 0xFF});
}

t_color	color_clamp(t_color c)
{
	return ((t_color){
		.r = fmax(0, fmin(c.r, 255)),
		.g = fmax(0, fmin(c.g, 255)),
		.b = fmax(0, fmin(c.b, 255))});
}

t_color	color_add(t_color a, t_color b)
{
	return (color_clamp((t_color){
			.r = a.r + b.r,
			.g = a.g + b.g,
			.b = a.b + b.b}));
}

t_color	color_scale(t_color c, double factor)
{
	t_color	scaled_color;

	scaled_color.r = c.r * factor;
	scaled_color.g = c.g * factor;
	scaled_color.b = c.b * factor;
	return (color_clamp(scaled_color));
}
