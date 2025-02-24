/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:22:59 by vgalloni          #+#    #+#             */
/*   Updated: 2025/02/20 18:11:42 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

int	ft_render(t_data *data, int ***map)
{
	t_co	co;

	if (!ft_background(data, data->b_gr))
		return (0);
	if (!ft_resized(data, data->img))
		return (mlx_delete_image(data->mlx, data->b_gr), 0);
	co.y = 0;
	while (co.y < data->map.rows)
	{
		co.x = 0;
		while (co.x < data->map.cols)
		{
			map[1][co.y][co.x] = mlx_image_to_window(data->mlx,
					data->img[map[0][co.y][co.x]], co.x * TILE, co.y * TILE);
			if (map[0][co.y][co.x] == 4 || map[0][co.y][co.x] == 6)
				ft_render_false(data, co, map);
			co.x++;
		}
		co.y++;
	}
	ft_player(data, data->img[IN_R_PL]->width, data->img[IN_R_PL]->height);
	return (1);
}

int	ft_background(t_data *data, mlx_image_t *img)
{
	uint32_t	i;
	uint32_t	j;
	int32_t		black;

	black = 0xFF000000;
	img = mlx_new_image(data->mlx, WIN_W, WIN_H);
	i = 0;
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
		{
			((int32_t *)img->pixels)[i * img->width + j] = black;
			j++;
		}
		i++;
	}
	mlx_image_to_window(data->mlx, img, 0, 0);
	return (1);
}

int	ft_resized(t_data *data, mlx_image_t **img)
{
	int		i;
	t_co	co;

	i = 0;
	while (i < MAX_TEXTURE)
	{
		co.x = data->tx[i]->width;
		co.y = data->tx[i]->height;
		img[i] = mlx_texture_to_image(data->mlx, data->tx[i]);
		if (!img[i])
			return (ft_delimg(data, img, i), 0);
		if (mlx_resize_image(img[i], co.x * 5, co.y * 5) == 0)
			return (ft_error(mlx_strerror(mlx_errno)), 0);
		i++;
	}
	return (1);
}

void	ft_player(t_data *data, const uint32_t width, const uint32_t height)
{
	t_co_s	off;

	off.x = (WIN_W / 2) - (width / 2);
	off.y = (WIN_H / 2) - (height / 2);
	data->pos.x = data->map.col;
	data->pos.y = data->map.row;
	mlx_image_to_window(data->mlx, data->img[8], off.x, off.y);
	mlx_image_to_window(data->mlx, data->img[9], off.x, off.y);
	data->img[9]->instances[0].enabled = 0;
}

void	ft_render_false(t_data *data, t_co co, int ***map)
{
	int	instance;

	instance = mlx_image_to_window(data->mlx,
			data->img[map[0][co.y][co.x] + 1], co.x * TILE, co.y * TILE);
	data->img[map[0][co.y][co.x] + 1]->instances[instance].enabled = 0;
}
