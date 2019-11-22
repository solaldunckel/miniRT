#include "mini_rt.h"

static	void	inter_cone(t_mini_rt *rt, t_element *cone, t_solve s,
t_mini_rt rtt)
{
	t_element	plan;
	t_vec		inter;
	double		t;

	s.t1 = (-s.b - sqrt(s.det)) / (2 * s.a);
	s.t2 = (-s.b + sqrt(s.det)) / (2 * s.a);
	t = INT_MAX;
	if (s.t1 >= 0 && rt->t > s.t1)
		t = s.t1;
	else if (s.t2 >= 0 && rt->t > s.t2)
		t = s.t2;
	if (t == INT_MAX)
		return ;
	inter = vec_add(rtt.ray.ori, vec_mul(rtt.ray.dir, t));
	plan.orient = cone->orient;
	plan.point = cone->point;
	rtt.t = INT_MAX;
	plane(&rtt, &plan, inter, vec_mul(cone->orient, 1));
 	rtt.t <= cone->height ? rt->t = t : 0;
}

void			cone(t_mini_rt *rt, t_element *cone, t_vec ori, t_vec dir)
{
	t_solve		s;
	t_mini_rt	rtt;
	t_vec		w;
	t_vec		theta;
	float		m;

	rtt.ray.ori = ori;
	rtt.ray.dir = dir;
	theta = vec_normalize(cone->orient);
	m = pow(cone->diameter / 2, 2) / pow(cone->height, 2);
	w = vec_sub(rtt.ray.ori, cone->point);
	s.a = VEC_ADD(vec_dot(rtt.ray.dir, rtt.ray.dir)) - m *
	pow(VEC_ADD(vec_dot(rtt.ray.dir, theta)), 2) -
	pow(VEC_ADD(vec_dot(rtt.ray.dir,theta)), 2);
	s.b = 2 * (VEC_ADD(vec_dot(rtt.ray.dir, w)) - m *
	VEC_ADD(vec_dot(rtt.ray.dir, theta)) *
	VEC_ADD(vec_dot(w, theta)) -
	VEC_ADD(vec_dot(rtt.ray.dir, theta)) *
	VEC_ADD(vec_dot(w, theta)));
	s.c = VEC_ADD(vec_dot(w,w)) - m * pow(VEC_ADD(vec_dot(w,theta)),2) -
	pow(VEC_ADD(vec_dot(w,theta)),2);
	s.det = pow(s.b, 2) - (4 * s.a * s.c);
	if (s.det < 0)
		return ;
	inter_cone(rt, cone, s, rtt);
}
