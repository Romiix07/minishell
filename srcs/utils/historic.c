/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 11:45:48 by rmouduri          #+#    #+#             */
/*   Updated: 2021/05/27 14:24:15 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

int	free_hist(t_hist *hist)
{
	t_string	*tmp;

	if (!hist)
		return (0);
	while (hist->head)
	{
		tmp = hist->head;
		hist->head = hist->head->next;
		if (tmp && tmp->string)
			free(tmp->string);
		if (tmp)
			free(tmp);
	}
	free(hist);
	return (1);
}

int	add_hist(t_hist *hist, char *s)
{
	t_string	*string;

	if (!ft_calloc((void **)&string, sizeof(t_string) * 1))
		return (0);
	string->string = s;
	string->prev = 0;
	string->next = 0;
	if (!hist->head)
	{
		hist->head = string;
		hist->tail = string;
	}
	else
	{
		string->prev = hist->tail;
		hist->tail->next = string;
		hist->tail = string;
	}
	return (1);
}

t_hist	*init_historic(void)
{
	t_hist	*hist;

	if (!ft_calloc((void **)&hist, sizeof(t_hist) * 1))
		return (0);
	hist->head = 0;
	hist->tail = 0;
	return (hist);
}
