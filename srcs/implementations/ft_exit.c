/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:28:14 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/02 13:50:12 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

void	ft_exit(void)
{
	int	i;

	i = 0;
	write(STDERR_FILENO, "exit\n", 5);
	if (g_shell->fct && g_shell->fct[1])
	{
		if (g_shell->input[1][0] == '-')
			++i;
		while (g_shell->input[1][i]
			&& is_charset(g_shell->input[1][i], "0123456789"))
			++i;
		if (g_shell->input[1][i] != 0)
			return_error("minishell: exit", g_shell->input[1],
				"numeric argument required", 0);
		else
			i = ft_atoi(g_shell->input[1]);
	}
	free_shell();
	exit(i);
}
