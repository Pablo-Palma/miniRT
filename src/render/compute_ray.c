/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 09:31:32 by pabpalma          #+#    #+#             */
/*   Updated: 2024/04/20 09:58:57 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	setup_ray_config(t_cam cam, t_ray_config *config)
{
	config->fov_rad = cam.fov * M_PI / 180.0;
	config->aspect_ratio = (double)WIN_WIDTH / (double)WIN_HEIGHT;
	config->scale = tan(config->fov_rad / 2);
	config->global_up = (t_vec3){0.0, 1.0, 0.0};
	if (cam.orientation.y == 1 || cam.orientation.y == -1)
		config->global_up = (t_vec3){1.0, 0.0, 0.0};
	config->right = vector_cross(config->global_up, cam.orientation);
	config->up = vector_cross(cam.orientation, config->right);
	config->right = normalize(config->right);
	config->up = normalize(config->up);
}

t_vec3	compute_ray_dir(int x, int y, t_cam cam)
{
	t_vec3			ray_dir;
	double			px;
	double			py;
	t_ray_config	config;

	setup_ray_config(cam, &config);
	ray_dir = cam.orientation;
	px = (2 * (x + 0.5) / (double)WIN_WIDTH - 1) * config.aspect_ratio
		* config.scale;
	py = (1 - 2 * (y + 0.5) / (double)WIN_HEIGHT) * config.scale;
	ray_dir.x += px * config.right.x + py * config.up.x;
	ray_dir.y += px * config.right.y + py * config.up.y;
	ray_dir.z += px * config.right.z + py * config.up.z;
	return (normalize(ray_dir));
}
