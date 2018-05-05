/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 18:35:00 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/05 16:45:15 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdlib.h>

int		main(int ac, char **av)
{
	t_tetri *test;

	test = NULL;
	if (ac == 2)
	{
		if (get_list_if_file_is_valid(av[1], &test) <= 0)
			ft_putstr("error\n");
		else
			ft_putstr("Success\n");
	}
	int i = 0;
	t_tetri *ptr = test;
	while (ptr != NULL)
	{
		//ft_putchar(ptr->name);
		ptr = ptr->next;
		//ft_putchar('\n');
		i++;
	}
	tetri_del(&test);
	//else
	//	PRINT_USAGE
	//ft_strdel(&tmp);
	return (0);
}
