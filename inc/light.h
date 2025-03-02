/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:38:21 by erian             #+#    #+#             */
/*   Updated: 2025/03/02 15:08:10 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "data.h"
# include "operations.h"

int color_to_int(t_color color);
t_color int_to_color(int integer);
int	apply_ambient_light(t_color object_color, t_a_light *ambient);
int	apply_light_source(t_color object_color, t_s_light *light, t_vec hit_point, t_vec normal);

#endif