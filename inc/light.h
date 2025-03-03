/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:38:21 by erian             #+#    #+#             */
/*   Updated: 2025/03/03 11:55:54 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "data.h"
# include "operations.h"

int		color_to_int(t_color color);
t_color	int_to_color(int integer);
t_color	color_add(t_color a, t_color b);
t_color	color_scale(t_color c, double factor);
t_color	color_clamp(t_color c);
int		apply_ambient_light(t_color object_color, t_a_light *ambient);
int		apply_light_source(t_color object_color, t_s_light *light, t_vec hit_point, t_vec normal);
t_color	calculate_light(t_s_light *light, t_vec hit_point, t_vec normal, t_color obj_color);

#endif