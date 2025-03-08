#include "structures.h"
#include "operations.h"

/*
dp = p - pa
a_part = v - <v | v_a> v_a
c_part = dp - <dp | v_a> v_a
d1 = <v | v_a>
d2 = <dp | v_a>

A = cos(alpha)^2 * <a_part | a_part> - sin(alpha)^2 * d1^2
*/
bool ray_inf_cone_intersect(t_ray ray, t_cone cone, double *t) {
	
	t_vec dp = sub(ray.origin, cone.apex);
	t_vec a_part = sub(ray.direction, scale(cone.apex, dot(ray.direction, cone.apex)));
	t_vec c_part = sub(dp, scale(cone.apex, dot(dp, cone.apex)));
	double d1 = dot(ray.origin, cone.apex);
	double d2 = dot(dp, cone.apex);

	double A = cos(cone.alpha) * cosh(cone.alpha) * dot(a_part, a_part) *
		dot(a_part, a_part) -
		sin(cone.alpha) * sin(cone.alpha) * d1 * d1;

	double B =
		2 * cos(cone.alpha) * cosh(cone.alpha) * dot(a_part, c_part) -
		2 * sin(cone.alpha) * sin(cone.alpha) * d2;

	double C = cos(cone.alpha) * cos(cone.alpha) * dot(c_part, c_part) *
		dot(c_part, c_part) -
		sin(cone.alpha) * sin(cone.alpha) * d2 * d2;


	double discriminant = discr(A, B, C);
	if (discriminant < 0)
		return NULL;

	double t1 = root_n(A, B, C);
	double t2 = root_p(A, B, C);

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
