/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_man.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:07:54 by vgalloni          #+#    #+#             */
/*   Updated: 2025/02/20 18:05:18 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	ft_free_tx(mlx_texture_t **texture, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		if (texture[i])
		{
			mlx_delete_texture(texture[i]);
			texture[i] = NULL;
		}
		i++;
	}
}

void	ft_free_da(int ***temp, int max)
{
	ft_free_arr((void **)temp[0], max);
	ft_free_arr((void **)temp[1], max);
}

void	ft_err(void)
{
	ft_printf("%s", mlx_strerror(mlx_errno));
}

void	ft_delimg(t_data *data, mlx_image_t **img, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		mlx_delete_image(data->mlx, img[i]);
		img[i] = NULL;
		i++;
	}
}

void	ft_on_exit(t_data *data)
{
	if (data->img[0])
		ft_delimg(data, data->img, MAX_TEXTURE);
	ft_free_tx(data->tx, MAX_TEXTURE);
	ft_free_da(data->i_map, data->map.rows);
	mlx_terminate(data->mlx);
	exit (EXIT_SUCCESS);
}
