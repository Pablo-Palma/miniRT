/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:28:25 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/09 13:02:59 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h" 

t_vec3	cylinder_normal(t_vec3 hit_point, t_cyl cyl)
{
	t_vec3 center_to_hit = vector_sub(hit_point, cyl.center);

    // Proyección de este vector sobre la dirección del cilindro
    // Esto da la distancia a lo largo del eje del cilindro desde la base hasta el punto de proyección
    double projection_length = vector_dot_product(center_to_hit, cyl.dir);

    // Punto en el eje del cilindro que corresponde a la proyección
    t_vec3 projected_point = vector_add(cyl.center, vector_scale(cyl.dir, projection_length));

    // La normal es el vector desde este punto proyectado en el eje hasta el punto de intersección
    t_vec3 normal = vector_sub(hit_point, projected_point);

    // Normalizamos la normal para obtener su dirección unitaria
    return normalize(normal);
}

int	intersect_ray_cyl(t_vec3 origin, t_vec3 dir, t_cyl cyl, double *t)
{
	t_vec3 diff = vector_sub(origin, cyl.center);
    t_vec3 dir_cross_cyl_dir = vector_cross(dir, cyl.dir);
    t_vec3 diff_cross_cyl_dir = vector_cross(diff, cyl.dir);

    double a = vector_dot_product(dir_cross_cyl_dir, dir_cross_cyl_dir);
    double b = 2 * vector_dot_product(dir_cross_cyl_dir, diff_cross_cyl_dir);
    double c = vector_dot_product(diff_cross_cyl_dir, diff_cross_cyl_dir) - (cyl.radius * cyl.radius);

    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return 0; // No intersection
    }

    double sqrt_discriminant = sqrt(discriminant);
    double t0 = (-b - sqrt_discriminant) / (2 * a);
    double t1 = (-b + sqrt_discriminant) / (2 * a);

    // Sort t0 and t1 so t0 is the smaller
    if (t0 > t1) {
        double temp = t0;
        t0 = t1;
        t1 = temp;
    }

    // Check if t0 and t1 are within the height of the cylinder
    double h0 = vector_dot_product(vector_add(diff, vector_scale(dir, t0)), cyl.dir);
    double h1 = vector_dot_product(vector_add(diff, vector_scale(dir, t1)), cyl.dir);

    if (h0 < 0) {
        if (h1 < 0) {
            return 0; // Both intersections are below the bottom cap of the cylinder
        } else {
            // t0 intersection is below the cylinder, check t1
            *t = t1;
            return h1 <= cyl.h;
        }
    } else if (h0 > cyl.h) {
        if (h1 > cyl.h) {
            return 0; // Both intersections are above the top cap of the cylinder
        } else {
            // t0 intersection is above the cylinder, check t1
            *t = t1;
            return 1;
        }
    } else {
        // t0 is within the height of the cylinder
        *t = t0;
        return 1;
    }
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
		t_vec3 light_dir = normalize(vector_sub(scene->light.pos, hit_point));
        double diffuse = calculate_diffuse(light_dir, normal, scene->light.brigthness);
        t_vec3 view_dir = normalize(vector_sub(scene->cam.view_point, hit_point));
        double specular = calculate_specular(view_dir, light_dir, normal, 1.0, 10.0); // Intensidad y brillo arbitrarios

        // Combina los componentes de iluminación para determinar el color final
        int color = mix_colors(cyl.color, diffuse, specular, 0.1); // Ambient light contribution set to 0.1 arbitrarily

        put_pixel_to_image(graph, x, y, color);
        return 1; // Intersección encontrada
	}
    return 0; // No hubo intersección
}
