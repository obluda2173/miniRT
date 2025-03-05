#include "minirt.h"
#include "operations.h"
#include "structures.h"

/*
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
{
	bool

}

bool ray_inf_cylinder_intersect(t_ray ray, t_cylinder cy, double *t) {
	t_vec dp = sub(ray.origin, cy.coordinates);

	t_vec a_part = sub(ray.direction, scale(ray.direction, dot(ray.direction, cy.axis_vector)));
	t_vec c_part = sub(dp, scale(cy.axis_vector, dot(dp, cy.axis_vector)));

	double a = dot(a_part, a_part);
	double b = 2 * dot(a_part, c_part);
	double c = dot(c_part, c_part) - (cy.diameter / 2)* (cy.diameter / 2);

	double discriminant = discr(a, b, c);
	if (discriminant < 0)
		return (false);

	double t1 = root_n(a, b, c);
	double t2 = root_p(a, b, c);
	t_vec p1 = cy.coordinates;
	t_vec p2 = add(cy.coordinates, scale(normalize(cy.axis_vector), cy.height));

	if (t1 > EPSILON && t2 > EPSILON) {
		bool t1_valid = check_validity()
	}
	if (t1 < EPSILON && t2 < EPSILON)
		return false;
	if (t1 > EPSILON) {
		bool t1_valid = true;
		t_vec q_1 = add(ray.origin, scale(ray.direction, t1));
		if (dot(cy.axis_vector, sub(q_1, p1)) <= 0)
			t1_valid = false;
		if (dot(cy.axis_vector, sub(q_1, p2)) >= 0)
			t1_valid = false;
	}

}

bool ray_cylinder_intersect(t_ray ray, t_cylinder cy, double *t) {
	double t_inf_cy;

	bool valid_inf_cy_found = ray_inf_cylinder_intersect(ray, cy, &t_inf_cy);


}
