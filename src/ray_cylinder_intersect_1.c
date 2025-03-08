/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder_intersect_1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:47/55 by kfreyer           #+#    #+#             */
/*   Updated: 2025/03/08 15:47:55 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"
#include "raytracing.h"
#include "structures.h"

/*
||q - p1||_2^2 < r_2
*/
bool	check_pt_inside_bottom_cap(t_ray ray, t_cylinder cy, double t)
{
	t_vec	pt;
	t_vec	pt_minux_p1;
	double	len_pt_mins_p1_squared;
	double	r_squared;

	pt = add(ray.origin, scale(ray.direction, t));
	pt_minux_p1 = sub(pt, cy.coordinates);
	len_pt_mins_p1_squared = dot(pt_minux_p1, pt_minux_p1);
	r_squared = ((cy.diameter / 2) * (cy.diameter / 2));
	if (len_pt_mins_p1_squared < r_squared)
		return (true);
	return (false);
}

/*
||q - p2||_2^2 < r_2
*/
bool	check_pt_inside_top_cap(t_ray ray, t_cylinder cy, double t)
{
	t_vec	p2;
	t_vec	pt;
	t_vec	pt_minus_p2;
	double	len_pt_minux_p2_squared;
	double	r_squared;

	p2 = add(cy.coordinates, scale(cy.axis_vector, cy.height));
	pt = add(ray.origin, scale(ray.direction, t));
	pt_minus_p2 = sub(pt, p2);
	len_pt_minux_p2_squared = dot(pt_minus_p2, pt_minus_p2);
	r_squared = ((cy.diameter / 2) * (cy.diameter / 2));
	if (len_pt_minux_p2_squared < r_squared)
		return (true);
	return (false);
}

void	add_t_to_cy_candidates(t_list **candidates, double t,
		t_cy_inter_type type)
{
	t_cy_inter	*cy_inter;

	cy_inter = malloc(sizeof(t_cy_inter));
	if (!cy_inter)
		return ;
	cy_inter->t = t;
	cy_inter->type = type;
	ft_lstadd_back(candidates, ft_lstnew(cy_inter));
	return ;
}

t_vec	calc_normal_cy(t_ray ray, t_cylinder *cy, t_cy_inter *cy_inter)
{
	t_vec	hit_p;
	double	new_t;
	t_vec	pt;

	if (cy_inter->type == TOP_CAP)
		return (normalize(cy->axis_vector));
	if (cy_inter->type == BOTTOM_CAP)
		return (scale(normalize(cy->axis_vector), -1));
	hit_p = add(ray.origin, scale(ray.direction, cy_inter->t));
	new_t = dot(sub(hit_p, cy->coordinates), normalize(cy->axis_vector));
	pt = add(cy->coordinates, scale(normalize(cy->axis_vector), new_t));
	return (normalize(sub(hit_p, pt)));
}

t_cy_inter	*find_smallest_cy_inter_t(t_list *candidates)
{
	t_cy_inter	*cy_inter;
	t_list		*head;

	cy_inter = malloc(sizeof(t_cy_inter));
	if (!cy_inter)
		return (NULL);
	head = candidates;
	cy_inter->t = ((t_cy_inter *)head->content)->t;
	cy_inter->type = ((t_cy_inter *)head->content)->type;
	head = head->next;
	while (head)
	{
		if (cy_inter->t > ((t_cy_inter *)head->content)->t)
		{
			cy_inter->t = ((t_cy_inter *)head->content)->t;
			cy_inter->type = ((t_cy_inter *)head->content)->type;
		}
		head = head->next;
	}
	return (cy_inter);
}
