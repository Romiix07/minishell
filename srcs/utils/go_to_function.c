/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 15:05:24 by rmouduri          #+#    #+#             */
/*   Updated: 2021/05/31 12:29:51 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

static int	incr_i(char **input, int i)
{
	while (input[i] && ft_strcmp(input[i], ";") && ft_strcmp(input[i], "&&"))
		++i;
	if (input[i])
		++i;
	return (i);
}

int	print_hist(t_hist *tmp)
{
	t_string	*hist;

	hist = tmp->head;
	while (hist)
	{
		printf("hist = %s\n", hist->string);
		hist = hist->next;
	}
	return (1);
}

int	go_to_function(t_shell *shell)
{
	int		i;

	i = 0;
	while (shell->input[i])
	{
		// tab = get_arg_tab(&input[i]);
		// for (int j = 0; tab && tab[j]; ++j)
			// printf("tab[%d] = %s\n", j, tab[j]);
		// if (tab)
			// free(tab);
		// tab = 0;
		if (!ft_strcmp(shell->input[i], "echo"))
			shell->return_value = ft_echo(get_arg_tab(&shell->input[i]), 0);
		else if (!ft_strcmp(shell->input[i], "cd"))
			shell->return_value = 0;
		else if (!ft_strcmp(shell->input[i], "pwd"))
			shell->return_value = 0;
		else if (!ft_strcmp(shell->input[i], "export"))
			shell->return_value = ft_export(shell->input, shell->env);
		else if (!ft_strcmp(shell->input[i], "unset"))
			shell->return_value = 0;
		else if (!ft_strcmp(shell->input[i], "env"))
			shell->return_value = print_env(shell->env);
		else if (!ft_strcmp(shell->input[i], "exit"))
			shell->return_value = 0;
		else if (!ft_strcmp(shell->input[i], "hist")) //tmp
			shell->return_value = print_hist(shell->hist); // tmp
		else
			shell->return_value = 0;
		i = incr_i(shell->input, i);
	}
	return (shell->return_value);
}
