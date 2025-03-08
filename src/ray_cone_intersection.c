/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cone_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:28/56 by kfreyer           #+#    #+#             */
/*   Updated: 2025/03/08 16:28:56 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "operations.h"
#include "raytracing.h"
#include "structures.h"

/*
X = O - C
a_part = v - <v | v_a> v_a
c_part = dp - <dp | v_a> v_a
d1 = <v | v_a>
d2 = <dp | v_a>

A = cos(alpha)^2 * <a_part | a_part> - sin(alpha)^2 * d1^2
*/
t_quadratic_coeff	calc_coeff(t_ray ray, t_cone *cone)
{
	t_quadratic_coeff	coeff;
	t_vec				dp;
	double				one_plus_k_squared;

	dp = sub(ray.origin, cone->apex);
	one_plus_k_squared = (1 + (tan(cone->alpha) * tan(cone->alpha)));
	coeff.a = dot(ray.direction, ray.direction) - one_plus_k_squared
		* dot(ray.direction, cone->axis) * dot(ray.direction, cone->axis);
	coeff.b = 2 * (dot(ray.direction, dp) - one_plus_k_squared
			* dot(ray.direction, cone->axis) * dot(dp, cone->axis));
	coeff.c = dot(dp, dp) - one_plus_k_squared * dot(dp, cone->axis) * dot(dp,
			cone->axis);
	return (coeff);
}

bool	ray_inf_cone_intersect(t_ray ray, t_cone *cone, double *t)
{
	t_quadratic_coeff	coeff;
	double				discriminant;
	double				t1;
	double				t2;

	coeff = calc_coeff(ray, cone);
	discriminant = discr(coeff);
	if (discriminant < 0)
		return (NULL);
	t1 = root_n(coeff);
	t2 = root_p(coeff);
	if (t1 > EPSILON && t2 > EPSILON)
		*t = fmin(t1, t2);
	else if (t1 > EPSILON)
		*t = t1;
	else if (t2 > EPSILON)
		*t = t2;
	else
		return (false);
	return (true);
}
