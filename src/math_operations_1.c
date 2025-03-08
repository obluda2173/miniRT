/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_operations_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 11:05:53 by erian             #+#    #+#             */
/*   Updated: 2025/03/08 11:26:41 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"

t_vec	vec(double x, double y, double z)
{
	t_vec	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec	add(t_vec v1, t_vec v2)
{
	return (vec(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vec	sub(t_vec v1, t_vec v2)
{
	return (vec(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

double	dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec	cross(t_vec v1, t_vec v2)
{
	return (vec(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x));
}
