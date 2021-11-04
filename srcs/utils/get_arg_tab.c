/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 14:00:49 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/03 23:10:27 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static int	get_size_arg_tab(char **tab, int j)
{
	int		i;
	int		size;

	i = -1;
	size = 0;
	if (!tab)
		return (-1);
	while (tab[++i] && (g_shell->ops[j + i] == 2
			|| (ft_strcmp(tab[i], ";") && ft_strcmp(tab[i], "&&")
				&& ft_strcmp(tab[i], ">") && ft_strcmp(tab[i], ">>")
				&& ft_strcmp(tab[i], "<") && ft_strcmp(tab[i], "<<")
				&& ft_strcmp(tab[i], "|"))))
		++size;
	return (size);
}

char	**get_arg_tab(char **input, int j)
{
	char	**arg_tab;
	int		i;
	int		size;

	size = get_size_arg_tab(input, j);
	if (size <= 0)
		return (0);
	if (!ft_calloc((void **)&arg_tab, sizeof(char *) * (size + 1)))
		return (0);
	i = -1;
	while (++i < size)
		arg_tab[i] = input[i];
	arg_tab[i] = 0;
	return (arg_tab);
}
