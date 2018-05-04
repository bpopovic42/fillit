/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 18:05:31 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/04 20:41:09 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

t_tetri		*parse_input(char *file)
{
	char		buff[BUFF_SIZE];
	int			fd;
	int			tetri_count;
	t_tetri		*list;
	t_tetri		*tetri;

	tetri_count = 0;
	if ((fd = open(file, O_RDONLY)) <= 0)
		return (NULL);
	list = NULL;
	ft_bzero(buff, BUFF_SIZE);
	while (get_input(fd, buff))
	{
		ts_print_tetri_map(buff);
		if (tetri_count >= 27)
			return (NULL);
		if (!(tetri = get_tetri(buff, tetri_count++)))
			return (NULL);
		tetri_push(&list, tetri);
		ft_bzero(buff, BUFF_SIZE);
	}
	close(fd);
	return (list);
}

t_tetri		*get_tetri(char buff[BUFF_SIZE], int tetri_count)
{
	int		i;
	int		blocks;
	int		coord[8];
	t_tetri	*tetri;

	i = 0;
	blocks = 0;
	tetri = NULL;
	while (i < 21)
	{
		if (((i && (i + 1) % 5 == 0) || i == 20))
		{
			if (buff[i] != '\n')
				return (NULL);
		}
		else if ((buff[i] && buff[i] != '.' && buff[i] != '#'))
		{
			return (NULL);
		}
		if (buff[i] == '#')
		{
			set_coord(coord, blocks++, i);
		}
		i++;
	}
	if (blocks != 4)
		return (NULL);
	trim_offset(coord);
	tetri = new_tetri(coord, 'A' + tetri_count);
	return (tetri);
}

/*
** Find lowest x and y coordinates, substract every x and y coordinates from it
*/
int		*trim_offset(int *coord)
{
	int i;
	int x;
	int y;

	i = 0;
	x = 3;
	y = 3;
	while (i < 8)
	{
		if (coord[i] < x)
			x = coord[i];
		if (coord[i + 1] < y)
			y = coord[i + 1];
		i += 2;
	}
	i = 0;
	while (i < 8)
	{
		if (x > 0)
			coord[i] -= x;
		if (y > 0)
			coord[i + 1] -= y;
		i += 2;
	}
	return (coord);
}

void	set_coord(int *coord, int blocks, int pos)
{
	coord[blocks * 2] = pos / 5;
	coord[(blocks * 2) + 1] = pos % 5;
}

/*
**
*/
int		get_input(int fd, char buff[BUFF_SIZE])
{
	int		bytes;

	bytes = read(fd, &(*buff), BUFF_SIZE - 1);
	buff[bytes] = '\0';
	return (bytes);
}
