/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:30:17 by pabpalma          #+#    #+#             */
/*   Updated: 2024/04/19 17:03:07 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "libft/inc/libft.h"
# include "structs.h"
# include "events.h"

# define	WIN_WIDTH 800
# define	WIN_HEIGHT 800
# ifndef	MAX_REFLECT_LEVEL
#  define	MAX_REFLECT_LEVEL 0
# endif
# ifndef	CHECKERBOARD
#  define	CHECKERBOARD 0
# endif


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


typedef struct s_scene
{
	t_cam			cam;
	t_sphere		sphere;
	t_plane			plane;
	t_cyl			cyl;
	t_light			light;
	t_ambient_light	ambient_light;
	int				checkerboard;
}				t_scene;

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
void	setup_hooks(t_graph *graph);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  SCENE                                    //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
void	render_scene(t_graph *graph, t_list *obj_list);
void	init_scene(t_scene *scene, t_list *obj);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  SPHERE                                   //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
int 	intersect_ray_sphere(t_vec3 origin, t_vec3 direction, t_sphere sphere, double *t);
int		handle_sphere_intersec(t_vec3	ray_dir, t_scene *scene, int x, int y, t_graph *graph);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  CYL                                      //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
int		handle_cyl_intersec(t_vec3	ray_dir, t_scene *scene, int x, int y, t_graph *graph);
int		intersect_ray_cyl(t_vec3 origin, t_vec3 dir, t_cyl cyl, double *t);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  PLANE                                    //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
int		handle_plane_intersec(t_vec3 ray_dir, t_scene *scene, int x, int y, t_graph *graph);
int		intersect_ray_plane(t_vec3 ray_origin, t_vec3 ray_dir, t_plane plane, double *t);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  VECTOR                                   //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
t_vec3	normalize(t_vec3 v);
double	vector_length(t_vec3 v);
t_vec3	vector_add(t_vec3 v1, t_vec3 v2);
t_vec3	vector_sub(t_vec3 v1, t_vec3 v2);
t_vec3	vector_multiply(t_vec3 v1, t_vec3 v2);
double	vector_dot_product(t_vec3 v1, t_vec3 v2);
t_vec3	vector_negate(t_vec3 v);
t_vec3	vector_scale(t_vec3 v, double s);
t_vec3	vector_cross(t_vec3 v1, t_vec3	v2);
t_vec3	vector_projection(t_vec3 v, t_vec3 u);
t_vec3	vector_reflect(t_vec3 v, t_vec3 n);
t_vec3	vector_proportion(t_vec3 v1, t_vec3 v2, double percent);
t_vec3	vector_fmax(t_vec3 v1, t_vec3 v2);
t_vec3	vector_fmin(t_vec3 v1, t_vec3 v2);
t_vec3	color_to_vec(int color);
bool	vector_cmp(t_vec3 v1, t_vec3 v2);
int		vec_to_color(t_vec3 vec);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  BRIGHT                                   //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
// int	shadow(t_scene *scene, t_vec3 hit_point, t_light light, t_vec3 normal);
// int shadow_plane(t_scene *scene, t_vec3 hit_point);
double  calculate_specular(t_light_params params, double intensity, double shine);
double	calculate_diffuse(t_vec3 light_dir, t_vec3	normal, double light_brightness);
t_vec3	reflect(t_vec3 v, t_vec3 n);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  COLORS                                   //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
void	put_pixel_to_image(t_graph *graph, int x, int y, int color);
int		mix_colors(t_ambient_light ambient_light, int  base_color, double diffuse, double specular);
int		convert_rgb_to_int(char *rgb_str);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  UTILS                                    //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
int	cleanup_and_exit(char **parts, char *error_msg, int r_value);
void get_bhaskara(t_bhaskara *eq);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  PARSE                                    //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
// int	parse_file(char *file, t_scene	*scene);
int		convert_to_int(char *str, int min, int max);
// int	parse_ambient(char *line, t_scene *scene);
char 	**split_and_validate(char *line, int expected, char delim);
// int	convert_to_int(char *str, int min, int max);
double	convert_to_double(char *str, double min, double max);

int		parse(t_graph *graph, int fd);
int 	check_all_obj(t_list *obj_list);
char	**nsplit(char *line, char delim, int expected);
void	dbfree(char **str);
void	onfail_clean(char *line, void *self);



///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  EXTRA LIST                               //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
t_list	*lst_strip_back(t_list **list);
t_list	*lst_strip_front(t_list **list);
t_list  *lst_strip_node(t_list **list, t_list *node);
t_list  **lst_create(void);
t_list  *lst_getpool_node(t_list **pool, void *(*new)(void *), void (*update)(void *, void *), void *content);
void    lst_mv_one_to_pool(t_list **pool, t_list *node, void (*clean)(void *node));
void    lst_mv_all_to_pool(t_list **pool, t_list **list, void (*clean)(void *node));

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  OBJECT		                             //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

t_list	*get_objects(int fd);
t_list	*objchr(t_list *obj, char *str);
int		obj_next(t_list **obj_ptr, char *str);
bool	is_child(t_obj *self, char *str);

void	constructor(void *self);
int		constructor_color(int *color, char *line);
int		constructor_vec(t_vec3 *vec, char *line);
void	a_light(void *parent);
void	camera(void *parent);
void	light(void *parent);
void	sphere(void *parent);
void	plane(void *parent);
void	cylinder(void *parent);

int		check(t_obj *obj);
int		check_pl(t_plane *plane);
int		check_sp(t_sphere *sphere);
int		check_cyl(t_cyl *cylinder);
int		check_light(t_light *light);
int		check_a_light(t_ambient_light *a_light);
int		check_cam(t_cam *cam);
int		check_color(int color);
int 	check_light_brightness(double b);
int		check_direction(t_vec3 vec);
int 	check_fov(int fov);
int 	check_unitary_vec(t_vec3 *vec);

void	print_obj(void *self);
void	print_a_light(void *obj);
void	print_camera(void *obj);
void	print_light(void *obj);
void	print_sphere(void *obj);
void	print_plane(void *obj);
void	print_cylinder(void *obj);

void 	intersect(t_obj *obj, t_ray *ray);
int		intersect_pl(t_plane plane, t_ray *ray);
int		intersect_sp(t_sphere sphere, t_ray *ray);
int		intersect_cyl(t_cyl *cyl, t_ray *ray);
int		intersect_light(t_light light, t_ray *ray);
int		intersect_circle(t_circle circle, t_ray *ray);

t_vec3	get_normal(t_obj *obj, t_vec3 point);
t_vec3	normal_pl(t_plane *plane, t_vec3 point);
t_vec3	normal_sp(t_sphere *sphere, t_vec3 point);
t_vec3	normal_cyl(t_cyl *cyl, t_vec3 point);

int		checkerboard(t_obj *obj, t_vec3 point);
int		checkerboard_pl(t_vec3 point);
int		checkerboard_sp(t_sphere sphere, t_vec3 point);
int		checkerboard_cyl(t_cyl cyl, t_vec3 point);


///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  RAY			                             //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
t_ray	ray_generic(t_vec3 origin, t_vec3 direction);
void	*ray_new(void *ray);
void	ray_delete(void *param);
void	ray_clean(void *self);
void	ray_cpy(void *self, void *ray);
void	ray_mv_to_pool(t_list **pool, t_list **ray_list);
void	ray_print(t_ray *ray);
void	ray_print_list(t_list *ray, int level);
void	ray_trace_light(t_ray *ray, t_list *obj_list, t_list **pool);
void	ray_trace_img(t_ray *ray, t_list **pool);
t_vec3	ray_sum(t_ray *ray, t_vec3 alight);


///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  BONUS                                    //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

int			apply_checkerboard_texture(t_vec3 point);
int			apply_checkerboard_texture_uv(double u, double v);
// void	cap_uv(t_vec3 hit_point, t_cyl cyl, double *u, double *v);
int		apply_checkerboard_texture_uv_cyl(double u, double v, t_cyl cyl);
int		calculate_reflection(t_vec3	hit_point, t_vec3 normal, t_scene *scene,
	t_vec3 incident_ray);
//int	trace_ray(t_vec3 origin, t_vec3 dir, t_scene *scene);
int		mix_colors_reflect(int	reflected_color, int base_color, double reflectivity);
int		trace_ray_for_reflection(t_vec3 origin, t_vec3 dir, t_scene *scene, int depth);
int		bonus_colors(int material_color, int reflected_color, float reflective);


#endif
