/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 11:05:53 by erian             #+#    #+#             */
/*   Updated: 2025/03/02 10:36:17 by erian            ###   ########.fr       */
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

t_vec add(t_vec v1, t_vec v2)
{
	return (vec(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vec sub(t_vec v1, t_vec v2)
{
	return (vec(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

double	dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec	cross(t_vec v1, t_vec v2)
{
	return (vec(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x));
}

t_vec	scale(t_vec v, double scalar)
{
	return (vec(v.x * scalar, v.y * scalar, v.z * scalar));
}

double	length(t_vec v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double	discr(double a, double b, double c)
{
	return (b * b - 4 * a * c);
}

double	root_n(double a, double b, double c)
{
	return ((-b - sqrt(discr(a, b, c))) / (2 * a));
}

double	root_p(double a, double b, double c)
{
	return ((-b + sqrt(discr(a, b, c))) / (2 * a));
}

t_vec	normalize(t_vec v)
{
	double	len;

	len = length(v);
	if (len == 0)
		return (vec(0, 0, 0));
	return (vec(v.x / len, v.y / len, v.z / len));
}
