/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:30:17 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/11 11:22:53 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "libft.h"
# include "struct.h"

# define	WIN_WIDTH 800
# define WIN_HEIGHT 800
//EVENTS
# define KEY_ESC 53
// COLORS
# define WHITE		0xFFFFFF
# define BLACK		0x000000
# define GREEN   	0x00FF00
# define BLUE    	0x0000FF
# define YELLOW	0xFFFF00
# define CIAN    	0x00FFFF
# define MAGENTA 	0xFF00FF
# define GREY    	0x808080
# define ORANGE 	0xFFA500
# define BROWN  	0xA52A2A
# define PINK    	0xFFC0CB
# define VIOLET 	0x8A2BE2
# define LIME    	0x00FF00

# define EPSILON 1e-6 //As a convetion for RT, eviting calculation error from floats.


typedef struct s_graph
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_lenght;
	int			endian;
	int			color_mode;
	//t_mini_RT	*miniRT;
}				t_graph;

typedef struct s_scene
{
	t_cam		cam;
	t_sphere	sphere;
	t_plane		plane;
	t_cyl		cyl;
	t_light		light;
}				t_scene;

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  GUI                                      //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
int		setup_gui(t_graph *graph);
int		cleanup(t_graph *graph);
void	init_img(t_graph *graph);
int 	handle_close(void *param);
void	setup_hooks(t_graph *graph);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  SCENE                                    //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
void	render_scene(t_graph *graph, t_scene *scene);
void	init_scene(t_scene *scene);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  SPHERE                                   //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
int intersect_ray_sphere(t_vec3 origin, t_vec3 direction, t_sphere sphere, double *t);
int	handle_sphere_intersec(t_vec3	ray_dir, t_scene *scene, int x, int y, t_graph *graph);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  CYL                                      //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
int	handle_cyl_intersec(t_vec3	ray_dir, t_scene *scene, int x, int y, t_graph *graph);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  PLANE                                    //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
int	handle_plane_intersec(t_vec3 ray_dir, t_scene *scene, int x, int y, t_graph *graph);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  VECTOR                                   //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
t_vec3	normalize(t_vec3 v);
double vector_length(t_vec3 v);
t_vec3	vector_add(t_vec3 v1, t_vec3 v2);
t_vec3	vector_sub(t_vec3 v1, t_vec3 v2);
double	vector_dot_product(t_vec3 v1, t_vec3 v2);
t_vec3	vector_negate(t_vec3 v);
t_vec3	vector_scale(t_vec3 v, double s);
t_vec3	vector_cross(t_vec3 v1, t_vec3	v2);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  BRIGHT                                   //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
int	shadow(t_scene *scene, t_vec3 hit_point, t_light light, t_vec3 normal);
int shadow_plane(t_scene *scene, t_vec3 hit_point);
double	calculate_specular(t_vec3 view_dir, t_vec3 ligh_dir, t_vec3 normal, double intensity, double shine);
double	calculate_diffuse(t_vec3 light_dir, t_vec3	normal, double light_brightness);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  COLORS                                   //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
void	put_pixel_to_image(t_graph *graph, int x, int y, int color);
int	mix_colors(int	base_color, double diffuse, double specular, double ambient);

#endif
