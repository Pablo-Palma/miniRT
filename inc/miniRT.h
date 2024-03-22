/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:30:17 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/22 01:34:03 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "libft/inc/libft.h"
# include "scene.h"
# include "object.h"
# include "light.h"
# include "events.h"

# define	WIN_WIDTH 800
# define WIN_HEIGHT 800
// COLORS
# define WHITE		0xFFFFFF
# define BLACK		0x000000
# define GREEN   	0x00FF00
# define BLUE    	0x0000FF
# define YELLOW		0xFFFF00
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
	t_list		*obj_list;
}				t_graph;

typedef struct	s_pixel
{
	int			y;
	int			x;
	int			color;
	double		diffuse;
	double		specular;
}				t_pixel;

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  GUI                                      //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
int		setup_gui(t_graph *graph);
int		cleanup(t_graph *graph);
void	init_img(t_graph *graph);
int 	handle_close(void *param);
void	setup_hooks(t_graph *graph, t_list *obj_list);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  SCENE                                    //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
void	render_scene(t_graph *graph, t_list *obj);

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
// int	shadow(t_scene *scene, t_vec3 hit_point, t_light light, t_vec3 normal);
// int shadow_plane(t_scene *scene, t_vec3 hit_point);
double	calculate_specular(t_vec3 view_dir, t_vec3 ligh_dir, t_vec3 normal, double intensity, double shine);
double	calculate_diffuse(t_vec3 light_dir, t_vec3	normal, double light_brightness);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  COLORS                                   //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
void	put_pixel_to_image(t_graph *graph, int x, int y, int color);
int		mix_colors(t_ambient_light	ambient_light, int	base_color, double diffuse, double specular);
int		convert_rgb_to_int(char *rgb_str);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  UTILS                                    //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
int	cleanup_and_exit(char **parts, char *error_msg, int r_value);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  PARSE                                    //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
// int	parse_file(char *file, t_scene	*scene);
int	convert_to_int(char *str, int min, int max);
// int	parse_ambient(char *line, t_scene *scene);
char **split_and_validate(char *line, int expected, char delim);
// int	convert_to_int(char *str, int min, int max);
double	convert_to_double(char *str, double min, double max);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  OBJECT		                             //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

t_list	*get_objects(int fd);
t_list	*objchr(t_list *obj, char *str);
int		obj_next(t_list **obj_ptr, char *str);
void	print_obj(void *self);
void 	intersect(t_obj *obj, t_ray *ray);
int 	trace_light(t_list *obj, t_ray *ray);
t_vec3	get_normal(t_obj *obj, t_vec3 point);
bool	is_child(t_obj *self, char *str);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  CONSTRUCTORS                             //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

void	a_light(void *parent);
void	camera(void *parent);
void	light(void *parent);
void	sphere(void *parent);
void	plane(void *parent);
void	cylinder(void *parent);

t_ray	*new_ray(t_vec3 origin, t_vec3 direction);
void	delete_ray(void *param);
void	ray_trace_light(t_ray *ray, t_list *obj_list);
void	ray_sum(t_ray *ray, t_pixel *pix, t_ambient_light ambient_light);
void	print_ray(t_ray *ray);
void	print_ray_list(t_list *ray, int level);

#endif
