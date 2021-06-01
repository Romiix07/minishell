/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_items.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 09:45:36 by rmouduri          #+#    #+#             */
/*   Updated: 2021/05/26 10:55:37 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*free_items(void **item_1, int size_1, void **item_2, int size_2)
{
	int	i;

	i = -1;
	if (item_1 && size_1 == 1)
		free(*item_1);
	if (item_1 && size_1 == 2)
	{
		while (item_1[++i])
			free(item_1[i]);
		free(item_1);
	}
	i = -1;
	if (item_2 && size_2 == 1)
		free(*item_2);
	if (item_2 && size_2 == 2)
	{
		while (item_2[++i])
			free(item_2[i]);
		free(item_2);
	}
	return (0);
}
