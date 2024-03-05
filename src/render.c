/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:14:03 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/04 15:17:23 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	put_pixel_to_image(t_graph *graph, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = graph->addr + (y * graph->line_lenght + x * (graph->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

t_vec3	normalize(t_vec3 v)
{
	double	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z); // Calculamos la longitud(magnitud) del vector v con la formula eucladiana
	t_vec3	normalized;	//dividimos cada componente del vector por su logitud, manteniendo la dirección del vector original pero ajustando
	normalized.x = v.x / len;	//su magnitud a 1.
	normalized.y = v.y / len;
	normalized.z = v.z / len;
	return (normalized);
}

int intersect_ray_sphere(t_vec3 origin, t_vec3 direction, t_sphere sphere, double *t)
{	//Esta funcion determina si un rayo intersecta con un esfera.
    t_vec3 oc = {origin.x - sphere.center.x, origin.y - sphere.center.y, origin.z - sphere.center.z};	//calcula vector desde origen del rayo a centro
	//de la esfera
    double a = direction.x * direction.x + direction.y * direction.y + direction.z * direction.z;
    double b = 2.0 * (oc.x * direction.x + oc.y * direction.y + oc.z * direction.z);
    double c = oc.x * oc.x + oc.y * oc.y + oc.z * oc.z - sphere.radius * sphere.radius;
    double discriminant = b * b - 4 * a * c; //Discriminant para determinar si hay intersección.

    if (discriminant < 0) {
        return 0; // No intersection
    }

    double t0 = (-b - sqrt(discriminant)) / (2.0 * a);	//Dos posibles solucciones de la ecuación cudarática.
    double t1 = (-b + sqrt(discriminant)) / (2.0 * a);

    // Usamos el valor de t más pequeño positivo como la distnacia al punto de intersección
    if (t0 > 0 && (t0 < *t || *t < 0)) {
        *t = t0;
    } else if (t1 > 0 && (t1 < *t || *t < 0)) {
        *t = t1;
    } else {
        return 0; // No intersection in the positive t direction
    }

    return 1; // Intersection occurred
}

t_vec3	compute_ray_dir(int x, int y, t_cam cam)
{
	double	fov_rad = cam.fov * M_PI / 180.0;	//Lo convertimo a Radianes para poder utilizar funciones trigonométricas.
	// (para converir a radian = alguno del campo de vision * pi / 180)
	double	aspect_ratio = (double)WIN_WIDTH / (double)WIN_HEIGHT; //relacción aspecto, (ancho venta / alto ventana), MANTENER ESCALA.
	double	scale = tan(fov_rad / 2.0);	//tamaño de imagen a escala
	//CALCULAR LAS CORDENADAS EN EL ESPACIO DE LA IMAGEN-----
	double	image_x = (2 * (x + 0.5) / (double)WIN_WIDTH - 1) * aspect_ratio * scale; //
	double	image_y = (1 - 2 * (y + 0.5) / (double)WIN_HEIGHT) * scale;
	//-----------
	t_vec3	ray_dir = {image_x, image_y, -1};
	ray_dir = normalize(ray_dir);
	return (ray_dir);
}


void	render_scene(t_graph *graph, t_scene *scene)
{
	int	x;
	int	y;
	t_vec3	ray_dir;
	double	t;	//Variable para almacenar la distancia al objeto interceptado.

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			t = 1000000;
			ray_dir = compute_ray_dir(x, y , scene->cam);	//Calcular dirección del rayo desde la camara hasta el pixel actual.
			if (intersect_ray_sphere(scene->cam.view_point, ray_dir, scene->sphere, &t)) // Verificar si el rayo intersecta con la esfera
				put_pixel_to_image(graph, x, y, 0xFFFFFF);	//Si hay intersección colocamos un pixel en blanco.
			x++;
		}
		y++;
	}
}
