/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:26:25 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/12 17:11:39 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static	int	parse_line(char *line, t_scene	*scene)
{
	if (line[0] == 'A')
		return(parse_ambient(line, scene));
//	else if (line[0] == 'C')
//		return(parse_cam(line, scene));
//	else if (line[0] == 'L')
//		return(parse_light(line, scene));
//	else if (ft_strncmp(line, "sp", 2) == 0)
//		return(parse_sphere(line, scene));
//	else if (ft_strncmp(line, "pl", 2) == 0)
//		return(parse_plane(line, scene));
//	else if (ft_strncmp(line, "cy", 2) == 0)
//		return(parse_cylinder(line, scene));
	return (1);
}

int	parse_file(char *file, t_scene	*scene)
{
	int	fd;
	char *line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror ("Error opening file");
		return (0);
	}
	while ((line = get_next_line(fd)) > 0)
	{
		if (!parse_line(line, scene))
		{
			free(line);
			close(fd);
			return(0);
		}
		free(line);
	}
	free(line);
	close(fd);
	return(1);
}
