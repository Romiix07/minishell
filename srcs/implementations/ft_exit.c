/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:28:14 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/10 17:34:23 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

static unsigned char	get_ret_val(void)
{
	unsigned char	i;

	i = 0;
	if (g_shell->input[1][0] == '-' || g_shell->input[1][0] == '+')
		++i;
	while (g_shell->input[1][i]
		&& is_charset(g_shell->input[1][i], "0123456789"))
		++i;
	if (g_shell->input[1][i] != 0)
	{
		return_error("minishell: exit", g_shell->input[1],
			"numeric argument required", 0);
		i = 255;
	}
	else
		i = ft_atoi(g_shell->input[1]);
	return (i);
}

void	ft_exit(int *pipefd)
{
	int	i;

	i = 0;
	write(STDERR_FILENO, "exit\n", 5);
	if (g_shell->fct && g_shell->fct[1])
		i = get_ret_val();
	if (pipefd)
		free(pipefd);
	free_shell();
	exit(i);
}
