/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:40:46 by rmouduri          #+#    #+#             */
/*   Updated: 2021/06/01 11:26:23 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;

	if (!init_shell(&shell, env))
		return (0);
	while (1)
	{
		while (!shell->input)
			shell->input = get_input(shell);
		// for (int i = 0; input[i]; ++i)
			// printf("input[%d] = %s\n", i, input[i] ? input[i] : 0);
		go_to_function(shell);
			//break ;
		free_tab(shell->input, -1);
		shell->input = 0;
	}
	if (shell)
		free_shell(&shell);
	return (1);
}
