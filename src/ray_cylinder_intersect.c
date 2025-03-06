#include "minirt.h"
#include "operations.h"
#include "raytracing.h"
#include "structures.h"


bool check_between_caps(t_ray ray, t_cylinder cy, double t);
bool check_inside_bottom_cap(t_ray ray, t_cylinder cy, double t);
bool ray_caps_intersection(t_ray ray, t_cylinder cy, double *t);


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

bool ray_inf_cylinder_intersect(t_ray ray, t_cylinder cy, double *t) {
	t_vec dp = sub(ray.origin, cy.coordinates);
	t_vec a_part = sub(ray.direction, scale(ray.direction, dot(ray.direction, cy.axis_vector)));
	t_vec c_part = sub(dp, scale(cy.axis_vector, dot(dp, cy.axis_vector)));

	double A = dot(a_part, a_part);
	double B = 2 * dot(a_part, c_part);
	double r_squared = ((cy.diameter / 2) * (cy.diameter / 2));
	double C = dot(c_part, c_part) - r_squared;

	double discriminant = discr(A, B, C);
	if (discriminant < 0)
		return (false);

	double t1 = root_n(A, B, C);
	double t2 = root_p(A, B, C);

	if (t1 > EPSILON && t2 > EPSILON) {
		bool t1_valid = check_between_caps(ray, cy, t1);
		bool t2_valid = check_between_caps(ray, cy, t2);
		if (t1_valid && t2_valid) {
			*t = fmin(t1, t2);
			return true;
		}
		if (t1_valid) {
			*t = t1;
			return true;
		}
		if (t2_valid) {
			*t = t2;
			return true;
		}
		return false;
	}
	if (t1 > EPSILON) {
		bool t1_valid = check_between_caps(ray, cy, t1);
		if (t1_valid) {
			*t = t1;
			return true;
		}
		return false;
	}
	if (t2 > EPSILON) {
		bool t2_valid = check_between_caps(ray, cy, t2);
		if (t2_valid) {
			*t = t2;
			return true;
		}
		return false;
	}
	return false;
}

bool check_between_caps(t_ray ray, t_cylinder cy, double t)
{
	t_vec p1 = cy.coordinates;
	t_vec p2 = add(cy.coordinates, scale(normalize(cy.axis_vector), cy.height));

	t_vec q = add(ray.origin, scale(ray.direction, t));
	if (dot(cy.axis_vector, sub(q, p1)) <= 0)
		return false;
	if (dot(cy.axis_vector, sub(q, p2)) >= 0)
		return false;
	return true;
}

bool check_inside_bottom_cap(t_ray ray, t_cylinder cy, double t) {
	t_vec q = add(ray.origin, scale(ray.direction, t));
	double d = dot(sub(q, cy.coordinates), sub(q, cy.coordinates));
	if (d < ((cy.diameter * cy.diameter) / 4))
		return true;
	return false;
}

bool ray_caps_intersection(t_ray ray, t_cylinder cy, double *t) {
	t_plane bottom_cap_plane = {cy.coordinates, normalize(cy.axis_vector), cy.color};
	t_plane top_cap_plane = {cy.coordinates, normalize(cy.axis_vector), cy.color};
	double bottom_t;
	double top_t;
	if (ray_plane_intersect(ray, &bottom_cap_plane, &bottom_t)) {

	};
	ray_plane_intersect(ray, &top_cap_plane, &top_t);
}

