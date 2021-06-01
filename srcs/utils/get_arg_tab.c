/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 14:00:49 by rmouduri          #+#    #+#             */
/*   Updated: 2021/05/27 11:33:30 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static int	get_size_arg_tab(char **tab)
{
	int		i;
	int		size;

	i = -1;
	size = 0;
	if (!tab)
		return (-1);
	while (tab[++i] && ft_strcmp(tab[i], ";") && ft_strcmp(tab[i], "&&"))
		++size;
	return (size);
}

char	**get_arg_tab(char **tab)
{
	char	**arg_tab;
	int		i;
	int		size;

	size = get_size_arg_tab(tab);
	if (size <= 0)
		return (0);
	if (!ft_calloc((void **)&arg_tab, sizeof(char *) * (size + 1)))
		return (0);
	i = -1;
	while (++i < size)
		arg_tab[i] = tab[i];
	arg_tab[i] = 0;
	return (arg_tab);
}
