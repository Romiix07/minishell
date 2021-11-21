/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:40:46 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/20 16:53:52 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "minishell.h"

t_shell	*g_shell;

int	main(__attribute__((unused))int ac, __attribute__((unused))
		char **av, char **env)
{
	if (!env)
		return (1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sighandler);
	if (init_shell(env) == 1)
		return (1);
	while (1)
	{
		while (!g_shell->input)
		{
			if (g_shell->ops)
			{
				free(g_shell->ops);
				g_shell->ops = 0;
			}
			g_shell->input = get_input();
		}
		go_to_function(0, -1);
		free_tab(g_shell->input, -1);
		g_shell->input = 0;
	}
	if (g_shell)
		free_shell();
	return (0);
}
