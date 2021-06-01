/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 11:03:29 by rmouduri          #+#    #+#             */
/*   Updated: 2021/05/25 16:01:49 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
void	*ft_calloc(void **ptr, int size)
{
	if (size <= 0)
		return (0x0);
	*ptr = malloc(size);
	if (!*ptr)
		return (0x0);
	while (--size >= 0)
		((char *)*ptr)[size] = 0x0;
	return (*ptr);
}
