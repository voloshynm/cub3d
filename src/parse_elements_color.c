/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_color.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <mvoloshy@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 22:59:44 by mvoloshy          #+#    #+#             */
/*   Updated: 2025/06/02 22:59:46 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_color(char *line, t_color *floor, t_color *ceiling)
{
	char	*trimmed;

	trimmed = trim_whitespace(line);
	if (!trimmed)
		return (0);
	if (ft_strncmp(trimmed, "F ", 2) == 0 && floor->r == -1)
		return (extract_rgb(trimmed + 2, floor));
	if (ft_strncmp(trimmed, "C ", 2) == 0 && ceiling->r == -1)
		return (extract_rgb(trimmed + 2, ceiling));
	return (0);
}

int	extract_rgb(char *str, t_color *color)
{
	char	*ptr;
	int		values[3];
	int		i;

	ptr = skip_whitespace(str);
	i = 0;
	while (i < 3)
	{
		values[i] = ft_atoi(ptr);
		if (values[i] < 0 || values[i] > 255)
			return (0);
		ptr = find_next_value(ptr, i);
		if (!ptr && i < 2)
			return (0);
		i++;
	}
	set_color_values(color, values);
	return (1);
}

void	set_color_values(t_color *color, int *values)
{
	color->r = values[0];
	color->g = values[1];
	color->b = values[2];
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
