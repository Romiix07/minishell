/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:14:24 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/03 13:14:39 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	free_tab(char **tab, int limit)
{
	int	i;

	i = -1;
	if (tab)
	{
		while (tab[++i] && (i < limit || limit == -1))
			free(tab[i]);
		free(tab);
	}
	return (0);
}
