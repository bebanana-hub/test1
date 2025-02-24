/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:21:33 by vgalloni          #+#    #+#             */
/*   Updated: 2025/02/20 17:35:11 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

int	ft_map_check(char *map_file, char ***map, t_data *start)
{
	t_check	pos;
	int		fd;
	int		collec;
	int		exit;

	collec = 0;
	exit = 0;
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (perror("infile open"), 0);
	*map = ft_get_map(&pos, fd, *map);
	if (!(*map))
		return (close(fd), 0);
	ft_clean_map(map, pos.rows);
	if (!ft_is_rectangle(&pos, *map, &collec, &exit) || exit != 1)
		return (ft_free_arr(*(void **)map, pos.rows), close(fd), 0);
	if (!ft_validate_map(*map, &pos, collec, exit))
	{
		ft_free_arr((void **)pos.visited, pos.rows);
		return (ft_free_arr(*(void **)map, pos.rows), close(fd), 0);
	}
	ft_cp(start, &pos);
	start->inventory = 0;
	start->collec = collec;
	return (close (fd), ft_free_arr((void **)pos.visited, pos.rows), 1);
}

char	**ft_get_map(t_check *pos, int fd, char **map)
{
	int		i;
	char	*temp;

	if (ft_countfd_lines(fd) <= 0)
		return (close(fd), NULL);
	i = 0;
	map = malloc((ft_countfd_lines(fd) + 1) * sizeof(char *));
	if (!map)
		return (close(fd), NULL);
	temp = get_next_line(fd);
	if (!temp)
		return (free (map), close(fd), NULL);
	while (temp != NULL)
	{
		map[i] = temp;
		if (!map[i])
			return (ft_free_arr((void **)map, i), close(fd), NULL);
		temp = get_next_line(fd);
		i++;
	}
	map[i] = NULL;
	pos->rows = i;
	pos->cols = ft_strclen(map[0], '\n');
	return (map);
}

bool	ft_is_rectangle(t_check *pos, char **map, int *collec, int *exit)
{
	size_t	i;

	i = 0;
	while (i < pos->rows)
	{
		if (ft_strlen(map[i]) != pos->cols)
			return (false);
		if (ft_strchr(map[i], 'P'))
			ft_get_start(pos, i, map[i]);
		*collec += ft_count_occ(map[i], 'C');
		*exit += ft_count_occ(map[i], 'E');
		i++;
	}
	ft_init_visited(pos);
	if (!pos->visited)
		return (ft_error("init_visited fail"), false);
	return (true);
}

void	ft_init_visited(t_check *pos)
{
	unsigned int	i;

	i = 0;
	pos->visited = ft_calloc(pos->rows, sizeof(bool *));
	if (!pos->visited)
		return ;
	while (i < pos->rows)
	{
		pos->visited[i] = ft_calloc(pos->cols, sizeof(bool));
		if (!pos->visited[i])
		{
			while (i > 0)
				free(pos->visited[--i]);
			free(pos->visited);
			return ;
		}
		i++;
	}
}

void	ft_get_start(t_check *pos, int i, char *temp)
{
	pos->row = i;
	pos->col = 0;
	while (temp[pos->col] && temp[pos->col] != 'P')
		pos->col++;
}
