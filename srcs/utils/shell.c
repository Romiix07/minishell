/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 12:08:38 by rmouduri          #+#    #+#             */
/*   Updated: 2021/05/31 11:19:06 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

int	free_shell(t_shell **shell)
{
	if (!shell)
		return (0);
	if ((*shell)->env)
		free_env((*shell)->env);
	if ((*shell)->hist)
		free_hist((*shell)->hist);
	if ((*shell)->input)
		free_tab((*shell)->input, -1);
	free(*shell);
	return (1);
}

int	init_shell(t_shell **shell, char **env)
{
	if (!ft_calloc((void **)shell, sizeof(t_shell) * 1))
		return (0);
	(*shell)->input = 0;
	(*shell)->hist = 0;
	(*shell)->env = 0;
	(*shell)->env = init_env(env);
	if (!(*shell)->env)
	{
		free_shell(shell);
		return (return_error("Error env initialization\n"));
	}
	(*shell)->hist = init_historic();
	if (!(*shell)->hist)
		free_shell(shell);
	return (1);
}
