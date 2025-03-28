/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:18:50 by pabpalma          #+#    #+#             */
/*   Updated: 2024/04/20 09:58:01 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct s_sphere
{
	char			identifier[3];
	t_vec3			center;
	double			radius;
	int				color;
	double			diameter;
}					t_sphere;

typedef struct s_cyl
{
	char			id[2];
	t_vec3			center;
	t_vec3			dir;
	double			radius;
	double			h;
	int				color;
	int				caps;
}					t_cyl;

typedef struct s_plane
{
	char			id[2];
	t_vec3			point;
	t_vec3			normal;
	int				color;
}					t_plane;

typedef struct s_circle
{
	char			id[2];
	t_vec3			center;
	t_vec3			normal;
	double			radius;
	int				color;
}					t_circle;

typedef struct s_light
{
	char			id[2];
	t_vec3			pos;
	double			brigthness;
	int				color;
}					t_light;

typedef struct light_params
{
	t_vec3			view_dir;
	t_vec3			light_dir;
	t_vec3			norm;
}					t_light_params;

typedef struct s_ambient_light
{
	char			id[2];
	double			intensity;
	int				color;
}					t_ambient_light;

typedef struct s_cam
{
	char			identifier[2];
	t_vec3			view_point;
	t_vec3			orientation;
	int				fov;
}					t_cam;

typedef struct s_obj
{
	char			*line;
	void			*child;
	t_vec3			**origin;
	int				*color;
	double			reflective;
}					t_obj;

typedef struct s_ray
{
	t_vec3			origin;
	t_vec3			direction;
	double			t;
	t_obj			**obj;
	t_list			**next;
	ssize_t			reflect_level;
	bool			img_trace;
}					t_ray;

typedef struct s_bhaskara
{
	double			a;
	double			b;
	double			c;
	double			discriminant;
	double			sqrt_discriminant;
	double			t0;
	double			t1;
}					t_bhaskara;

typedef struct s_raysum
{
	t_list			*ray_list;
	t_ray			*next_ray;
	t_vec3			pxl_light;
	t_vec3			temp;
	t_vec3			view_dir;
	t_vec3			light_dir;
	t_vec3			norm;
	double			diffuse;
	double			specular;
	t_ambient_light	ambient_light;
	t_vec3			alight;
}					t_raysum;

typedef struct s_ray_config
{
	double	fov_rad;
	double	aspect_ratio;
	double	scale;
	t_vec3	global_up;
	t_vec3	right;
	t_vec3	up;

}			t_ray_config;

#endif
