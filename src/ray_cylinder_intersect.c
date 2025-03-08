#include "libft.h"
#include "minirt.h"
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
bool check_between_caps(t_ray ray, t_cylinder cy, double t)
{
	t_vec p1 = cy.coordinates;	/* check */
	t_vec p2 = add(cy.coordinates, scale(cy.axis_vector, cy.height)); /* check */

	t_vec q = add(ray.origin, scale(ray.direction, t));
	
	if (dot(cy.axis_vector, sub(q, p1)) > 0 && dot(cy.axis_vector, sub(q, p2)) < 0)
		return true;
	return false;
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
t_list* ray_inf_cylinder_intersect(t_ray ray, t_cylinder cy) {
	t_vec dp = sub(ray.origin, cy.coordinates); /* check */
	t_vec a_part = sub(ray.direction, scale(cy.axis_vector, dot(ray.direction, cy.axis_vector))); /* check */
	t_vec c_part = sub(dp, scale(cy.axis_vector, dot(dp, cy.axis_vector))); /* check */

	double A = dot(a_part, a_part); /* check */
	double B = 2 * dot(a_part, c_part); /* check */
	double r_squared = ((cy.diameter / 2) * (cy.diameter / 2));
	double C = dot(c_part, c_part) - r_squared;

	double discriminant = discr(A, B, C);
	if (discriminant < 0)
		return NULL;

	double t1 = root_n(A, B, C);
	double t2 = root_p(A, B, C);

	t_list* candidates = NULL;
	if (t1 > EPSILON && check_between_caps(ray, cy, t1)) {
		t_cy_inter* cy_inter = malloc(sizeof(t_cy_inter));
		if (!cy_inter)
			return NULL;
		cy_inter->t = t1;
		cy_inter->type = SURFACE;
		ft_lstadd_back(&candidates, ft_lstnew(cy_inter));
	}
	if (t2 > EPSILON && check_between_caps(ray, cy, t2)) {
		t_cy_inter* cy_inter = malloc(sizeof(t_cy_inter));
		if (!cy_inter)
			return NULL;
		cy_inter->t = t2;
		cy_inter->type = SURFACE;
		ft_lstadd_back(&candidates, ft_lstnew(cy_inter));
	}
	return candidates;
}


/*
||q - p1||_2^2 < r_2
*/
bool check_pt_inside_bottom_cap(t_ray ray, t_cylinder cy, double t) {
	t_vec pt = add(ray.origin, scale(ray.direction, t)); /* check */
	t_vec pt_minux_p1 = sub(pt, cy.coordinates);		 /* check */
	double len_pt_mins_p1_squared = dot(pt_minux_p1, pt_minux_p1); /* check */
	double r_squared = ((cy.diameter / 2) * (cy.diameter / 2));	   /* check */
	if (len_pt_mins_p1_squared < r_squared)						   /* check */
		return true;
	return false;
}


/*
||q - p2||_2^2 < r_2
*/
bool check_pt_inside_top_cap(t_ray ray, t_cylinder cy, double t) {
	t_vec p2 = add(cy.coordinates, scale(cy.axis_vector, cy.height)); /* check */
	t_vec pt = add(ray.origin, scale(ray.direction, t)); /* check */
	t_vec pt_minus_p2 = sub(pt,p2);						 /* check */
	double len_pt_minux_p2_squared = dot(pt_minus_p2, pt_minus_p2); /* check */
	double r_squared = ((cy.diameter / 2) * (cy.diameter / 2));		/* check */
	if (len_pt_minux_p2_squared < r_squared)
		return true;
	return false;
}

/*
Calculating possible intersection points of ray with caps
*/
t_list* ray_caps_intersection(t_ray ray, t_cylinder cy, t_list** candidates) {
	t_plane bottom_cap_plane = {cy.coordinates, cy.axis_vector, cy.color, NULL, NULL};
	t_vec p2 = add(cy.coordinates, scale(cy.axis_vector, cy.height));
	t_plane top_cap_plane = {p2, cy.axis_vector, cy.color, NULL, NULL};

	double t;
	if (ray_plane_intersect(ray, &bottom_cap_plane, &t)) {
		if (check_pt_inside_bottom_cap(ray, cy, t)) {
			t_cy_inter* cy_inter = malloc(sizeof(t_cy_inter));
			if (!cy_inter) {
				return NULL;
			}
			cy_inter->t = t;
			cy_inter->type = BOTTOM_CAP;
			ft_lstadd_back(candidates, ft_lstnew(cy_inter));
		}
	};

	if (ray_plane_intersect(ray, &top_cap_plane, &t)) {
		if (check_pt_inside_top_cap(ray, cy, t)) {
			t_cy_inter* cy_inter = malloc(sizeof(t_cy_inter));
			if (!cy_inter) {
				return NULL;
			}
			cy_inter->t = t;
			cy_inter->type = TOP_CAP;
			ft_lstadd_back(candidates, ft_lstnew(cy_inter));
		}
	};
	return *candidates;
}

t_cy_inter *ray_inter_cylinder(t_ray ray, t_cylinder cy) {
	cy.axis_vector = normalize(cy.axis_vector);
	t_list* candidates = ray_inf_cylinder_intersect(ray, cy);
	ray_caps_intersection(ray, cy, &candidates);

	if (!candidates)
		return NULL;

	t_cy_inter* cy_inter = malloc(sizeof(t_cy_inter));
	if (!cy_inter)
		return NULL;

	t_list* head = candidates;
	cy_inter->t = ((t_cy_inter*)head->content)->t;
	cy_inter->type = ((t_cy_inter*)head->content)->type;
	head = head->next;
	while (head) {
		if (cy_inter->t > ((t_cy_inter*)head->content)->t) {
			cy_inter->t = ((t_cy_inter*)head->content)->t;
			cy_inter->type = ((t_cy_inter*)head->content)->type;
		}
		head = head->next;
	}
	ft_lstclear(&candidates, free);
	return cy_inter;
}

t_vec calc_normal_cy(t_ray ray, t_cylinder *cy, t_cy_inter *cy_inter) {
	if (cy_inter->type == TOP_CAP)
		return normalize(cy->axis_vector);
	if (cy_inter->type == BOTTOM_CAP)
		return scale(normalize(cy->axis_vector), -1);

	t_vec hit_p = add(ray.origin, scale(ray.direction, cy_inter->t));

	double new_t = dot(sub(hit_p, cy->coordinates), normalize(cy->axis_vector));
	t_vec pt = add(cy->coordinates, scale(normalize(cy->axis_vector), new_t));

	return normalize(sub(hit_p, pt));
}
