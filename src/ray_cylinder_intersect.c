/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder_intersect.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:40/55 by kfreyer           #+#    #+#             */
/*   Updated: 2025/03/08 15:40:55 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "operations.h"
#include "raytracing.h"
#include "structures.h"

/*
p1 ... center of the cylinder (center of bottom cap)
p2 ... center of the cylinder at the other end (center of top cap)
q  ... candidate point lying surface of infinite cylinder
q is inbetween the caps if
<v_a | q-p_1> > 0 && <v_a, q-p_2> < 0
*/
bool	check_between_caps(t_ray ray, t_cylinder cy, double t)
{
	t_vec	q;
	t_vec	p1;
	t_vec	p2;

	p1 = cy.coordinates;
	p2 = add(cy.coordinates, scale(cy.axis_vector, cy.height));
	q = add(ray.origin, scale(ray.direction, t));
	if (dot(cy.axis_vector, sub(q, p1)) > 0 && dot(cy.axis_vector, sub(q,
				p2)) < 0)
		return (true);
	return (false);
}

/*
cylinder around line p_a + t * v_a
||q - p_a - <v_a | q - p_a>v_a||_{2}^{2} - r^2 = 0
q = (x, y, z)

intersection between cylinder and ray: p + t*v

p      ... ray origin
pa     ... cylinder origins
v      ... direction vectory of the ray
v_a    ... direction vector of the cylinder
dp = p - pa
a_part = v - <v | v_a> v_a
c_part = dp - <dp | v_a> v_a

A = <a_part | a_part>
C = <c_part | c_part> - r^2
*/

bool	calc_t1_and_t2(double *t1, double *t2, t_ray ray, t_cylinder cy)
{
	t_vec				dp;
	t_vec				a_part;
	t_vec				c_part;
	double				discriminant;
	t_quadratic_coeff	coeff;

	dp = sub(ray.origin, cy.coordinates);
	a_part = sub(ray.direction, scale(cy.axis_vector, dot(ray.direction,
					cy.axis_vector)));
	c_part = sub(dp, scale(cy.axis_vector, dot(dp, cy.axis_vector)));
	coeff.a = dot(a_part, a_part);
	coeff.b = 2 * dot(a_part, c_part);
	coeff.c = dot(c_part, c_part) - ((cy.diameter / 2) * (cy.diameter / 2));
	discriminant = discr(coeff);
	if (discriminant < 0)
		return (false);
	*t1 = root_n(coeff);
	*t2 = root_p(coeff);
	return (true);
}

t_list	*ray_inf_cylinder_intersect(t_ray ray, t_cylinder cy)
{
	double	t1;
	double	t2;
	t_list	*candidates;

	if (!calc_t1_and_t2(&t1, &t2, ray, cy))
		return (NULL);
	candidates = NULL;
	if (t1 > EPSILON && check_between_caps(ray, cy, t1))
		add_t_to_cy_candidates(&candidates, t1, SURFACE);
	if (t2 > EPSILON && check_between_caps(ray, cy, t2))
		add_t_to_cy_candidates(&candidates, t2, SURFACE);
	return (candidates);
}

/*
Calculating possible intersection points of ray with caps
*/
t_list	*ray_caps_intersection(t_ray ray, t_cylinder cy, t_list **candidates)
{
	t_plane	bottom_cap_plane;
	t_vec	p2;
	t_plane	top_cap_plane;
	double	t;

	bottom_cap_plane = (t_plane){cy.coordinates, cy.axis_vector, cy.color, NULL,
		NULL};
	p2 = add(cy.coordinates, scale(cy.axis_vector, cy.height));
	top_cap_plane = (t_plane){p2, cy.axis_vector, cy.color, NULL, NULL};
	if (ray_plane_intersect(ray, &bottom_cap_plane, &t))
		if (check_pt_inside_bottom_cap(ray, cy, t))
			add_t_to_cy_candidates(candidates, t, BOTTOM_CAP);
	if (ray_plane_intersect(ray, &top_cap_plane, &t))
		if (check_pt_inside_top_cap(ray, cy, t))
			add_t_to_cy_candidates(candidates, t, TOP_CAP);
	return (*candidates);
}

t_cy_inter	*ray_inter_cylinder(t_ray ray, t_cylinder cy)
{
	t_list		*candidates;
	t_cy_inter	*cy_inter;

	cy.axis_vector = normalize(cy.axis_vector);
	candidates = ray_inf_cylinder_intersect(ray, cy);
	ray_caps_intersection(ray, cy, &candidates);
	if (!candidates)
		return (NULL);
	cy_inter = find_smallest_cy_inter_t(candidates);
	ft_lstclear(&candidates, free);
	return (cy_inter);
}
