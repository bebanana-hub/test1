/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_man2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:30:40 by vincent           #+#    #+#             */
/*   Updated: 2025/02/20 21:59:55 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

int	check_format(char *str)
{
	char	*ber;

	if (str)
	{
		ber = ft_strrchr(str, '.');
		if (!ber || ft_strlen(ber) != 4)
			return (0);
		if (ft_strncmp(ber, ".ber", 4) == 0)
			return (1);
	}
	return (0);
}

void	status_pos(char **map, t_check *pos, t_coll *coll)
{
	if (map[pos->row][pos->col] == 'C')
		coll->collec++;
	else if (map[pos->row][pos->col] == 'E')
		coll->exit++;
	else if (map[pos->row][pos->col] == 'P')
		coll->pos++;
}
