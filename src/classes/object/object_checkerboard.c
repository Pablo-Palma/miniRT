/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_checkerboard.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:50:41 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/04/18 20:34:59 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	checkerboard_pl(t_vec3 point)
{
	const double	scale = 0.5;
	int	x = abs((int)floor(point.x * scale)) % 2;
	int	y = abs((int)floor(point.y * scale)) % 2;
	int	z = abs((int)floor(point.z * scale)) % 2;

	int	decision = (x ^ y ^ z);
	if (decision == 0)
		return(WHITE);
	else
		return(BLACK);
}

int	apply_checkerboard_sp(double u, double v)
{
	const double scale = 10.0;
	int x = (int)(floor(u * scale)) % 2;
	int y = (int)(floor(v * scale)) % 2;
	int	color;

	if (x == y)
		color = WHITE;
	else
		color = BLACK;
	return (color);
}

static int	checkerboard_sp(t_sphere sphere, t_vec3 point)
{
	double	u;
	double	v;
	t_vec3	p = normalize(vector_sub(point, sphere.center));

	double	phi = atan2(p.z, p.x);
	double	theta = asin(p.y);

	u = 1 - (phi + M_PI) / (2 * M_PI);
	v = (theta + M_PI / 2) / M_PI;
	return (apply_checkerboard_sp(u, v));
}

int	apply_checkerboard_cyl(double u, double v, t_cyl cyl)
{
    double cuadroSize = cyl.radius / 2; // Esto determina el tamaño de los cuadros basado en el radio del cilindro

    // Calcular la repetición del patrón basado en el tamaño del cuadro
    double u_repeats = (2 * M_PI * cyl.radius) / cuadroSize; // Cuántos cuadros caben alrededor del cilindro
    double v_repeats = cyl.h / cuadroSize; // Cuántos cuadros caben a lo largo de la altura del cilindro

    // Aplicar la textura de tablero de ajedrez
    int x = (int)(floor(u * u_repeats)) % 2;
    int y = (int)(floor(v * v_repeats)) % 2;
    int color;
	if  (x == y) 
		color = WHITE;
	else
		color = BLACK;

    return (color);
}

int	cap_uv(t_vec3 hit_point, t_cyl cyl)
{
	double	u;
	double	v;
	t_vec3 local_point = vector_sub(hit_point, cyl.center); // Convertir a coordenadas locales de la tapa
	
	u = (local_point.x / cyl.radius + 1) / 2; // Normalizar entre 0 y 1
	v = (local_point.y / cyl.radius + 1) / 2;
	return (apply_checkerboard_cyl(u, v, cyl));
}
static int	checkerboard_cyl(t_cyl cyl, t_vec3 point)
{
	double	u;
	double	v;
	t_vec3 cyl_dir_normalized = normalize(cyl.dir);
	
	t_vec3 point_vector = vector_sub(point, cyl.center);
	double proj_length = vector_dot_product(point_vector, cyl_dir_normalized);
	t_vec3 proj_on_cyl_axis = vector_scale(cyl_dir_normalized, proj_length);
	t_vec3 point_on_cyl_surface = vector_sub(point_vector, proj_on_cyl_axis);
	
	// Calcula el ángulo usando atan2 y asegúrate de que se use el plano correcto
	double angle = atan2(point_on_cyl_surface.y, point_on_cyl_surface.x);  // Ajusta esto según la orientación del cilindro
	
	u = (angle + M_PI) / (2 * M_PI);	//	lo escalamos de (-pi, pi) a (0, 1).
	u = fmod(u, 1.0);	//Aseguramos que es de 0 a 1.
	
	// Calcula la coordenada V basada en la proyección a lo largo del eje del cilindro
	double height = proj_length + (cyl.h / 2.0);  // Ajusta para que 0 esté en la base del cilindro, osea hayar la altura.
	v = height / cyl.h;
	v = fmod(v, 1.0);
	if (cyl.caps == 1)
		return (cap_uv(point, cyl));
	return (apply_checkerboard_cyl(u, v, cyl));
}

int	checkerboard(t_obj *obj, t_vec3 point)
{
	int	ret;

    if (is_child(obj, "pl"))
        ret = checkerboard_pl(point);
    else if (is_child(obj, "sp"))
        ret = checkerboard_sp(*(t_sphere *)(obj->child), point);
	else if (is_child(obj, "cy"))
        ret = checkerboard_cyl(*(t_cyl *)(obj->child), point);
	// else if (is_child(obj, "L"))
    //     ret = checkerboard_light(*(t_light *)(obj->child), ray);
	else
		ret = 0;
	if (ret)
	{
		return (ret);
	}
	return (0);
}
