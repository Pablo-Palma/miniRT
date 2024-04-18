/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_cyl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:28:25 by pabpalma          #+#    #+#             */
/*   Updated: 2024/04/18 12:29:39 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h" 

t_vec3	cylinder_normal(t_vec3 hit_point, t_cyl cyl)
{
	t_vec3 center_to_hit = vector_sub(hit_point, cyl.center);
	double proj_length = vector_dot_product(center_to_hit, cyl.dir);
	t_vec3 proj_point = vector_add(cyl.center, vector_scale(cyl.dir, proj_length));
	t_vec3 normal = vector_sub(hit_point, proj_point);
	return normalize(normal);
}

int	intersect_cyl_caps(t_vec3 origin, t_vec3 dir, t_cyl cyl, double *t_cap)
{
	t_vec3	cap_normal = cyl.dir;
	double	cap_t[2] = {INFINITY, INFINITY};
	int		hit = 0;
	int		i = 0;
	double	sign = 1.0;

	while(i < 2)
	{
		t_vec3	cap_center = vector_add(cyl.center, vector_scale(cap_normal, sign * (cyl.h / 2)));
		double d = vector_dot_product(vector_sub(cap_center, origin), cap_normal) / vector_dot_product(dir, cap_normal);
		if (d >= 0 && d < *t_cap)
		{
			t_vec3	p = vector_add(origin, vector_scale(dir, d));
			double	distance = vector_length(vector_sub(p, cap_center));
			if (distance <= cyl.radius)
			{
				cap_t[i] = d;
				hit = 1;
			}
		}
		i++;
		sign = -sign;
	}

	if (hit)
	{
		double	closest_t = cap_t[0];
		if (cap_t[1] < cap_t[0])
			closest_t = cap_t[1];
		*t_cap = closest_t;
	}
	return(hit);


}

int	intersect_ray_cyl(t_vec3 origin, t_vec3 dir, t_cyl cyl, double *t)
{
	t_vec3 diff = vector_sub(origin, cyl.center);	//	vecot Origen-centro cilindro
	t_vec3 dir_cross_cyl_dir = vector_cross(dir, cyl.dir); //Cruz entre el rayo y el cilindro
	t_vec3 diff_cross_cyl_dir = vector_cross(diff, cyl.dir); // Cruz entre diff y el cilindro
	
	double a = vector_dot_product(dir_cross_cyl_dir, dir_cross_cyl_dir); // Cuadrado del cruz de direcciones (rayo x cilindro)
	double b = 2 * vector_dot_product(dir_cross_cyl_dir, diff_cross_cyl_dir); // 2 producto punto  ((cruz de rayo-cilindor) * (cruz de diff-cilindro))
	double c = vector_dot_product(diff_cross_cyl_dir, diff_cross_cyl_dir) - (cyl.radius * cyl.radius); //cuadrado de (cruz de diff-cilindro) - (radio^2)
	
	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	    return 0; // No intersection
	
	double sqrt_discriminant = sqrt(discriminant);
	double t0 = (-b - sqrt_discriminant) / (2 * a);		//Distancia desde el rayo al primer punto de interseccion
	double t1 = (-b + sqrt_discriminant) / (2 * a);		//Distancia desde el rayo al segundo punto de interseccion
	
	double t_body = INFINITY;
	int body_hit = 0;
	//////******	t0	******///////
	if (t0 >= EPSILON) //Evitar errores.
	{
	    double h0 = vector_dot_product(vector_add(diff, vector_scale(dir, t0)), cyl.dir); // medida desde la base sobre el eje hasta el hitpoint
	    if (fabs(h0) <= cyl.h / 2) //Si está entre 0 y la altura máxima
		{
	        t_body = t0;	//SI Pertenece, almacenamos ese punto en t_body
	        body_hit = 1;	//Pertenece
	    }
	}
	
	//////******	t1	******///////		t1 es un punto más lejano que t0
	if (t1 >= EPSILON && t1 < t_body)	// si t1 es mayor que t_body, ya tenemos un punto más cercano, por tanto el lejano ya no nos interesa
	{
	    double h1 = vector_dot_product(vector_add(diff, vector_scale(dir, t1)), cyl.dir);
	    if (fabs(h1) <= cyl.h / 2)
		{
			t_body = t1;
			body_hit = 1;
	    }
	}
	
	// Intersección con las tapas del cilindro
	double t_cap = INFINITY;
	int cap_hit = intersect_cyl_caps(origin, dir, cyl, &t_cap);
	
	// calcular la intersección más cercana
	if (cap_hit && (t_cap < t_body || !body_hit))
	{
		*t = t_cap;
		return 1;
	}
	else if (body_hit)
	{
		*t = t_body;
		return 1;
	}
	return 0;
}

int	handle_cyl_intersec(t_vec3	ray_dir, t_scene *scene, int x, int y, t_graph *graph)
{
	t_cyl	cyl = scene->cyl;
	t_vec3	ray_origin = scene->cam.view_point;
	double	t;
	
	if (intersect_ray_cyl(ray_origin, ray_dir, cyl, &t))
	{
		t_vec3	hit_point = vector_add(ray_origin, vector_scale(ray_dir, t));
		t_vec3	normal = cylinder_normal(hit_point, cyl);
		int	shadowed = shadow_plane(scene, hit_point);
		double	diffuse = 0;
		double	specular = 0;
		if (!shadowed)
		{
			t_vec3 light_dir = normalize(vector_sub(scene->light.pos, hit_point));
			diffuse = calculate_diffuse(light_dir, normal, scene->light.brigthness);
			t_vec3 view_dir = normalize(vector_sub(scene->cam.view_point, hit_point));
    		specular = calculate_specular(view_dir, light_dir, normal, 1.0, 10.0); // Intensidad y brillo arbitrarios
		}

    	int color = mix_colors(cyl.color, diffuse, specular, *scene); // Ambient light contribution set to 0.1 arbitrarily

    	put_pixel_to_image(graph, x, y, color);
    	return 1; // Intersección encontrada
	}
	return 0; // No hubo intersección
}
