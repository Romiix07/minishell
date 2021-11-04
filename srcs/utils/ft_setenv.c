/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:24:15 by rmouduri          #+#    #+#             */
/*   Updated: 2021/10/28 15:02:05 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

void	add_to_env(t_env *node)
{
	t_env	*tmp;

	tmp = g_shell->env;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp && tmp->next)
		tmp->next->next = node;
	else if (tmp)
		tmp->next = node;
	else
		g_shell->env = node;
}

static t_env	*ft_setenv_existing(char *name, char *var)
{
	t_env	*node;

	node = get_env_node(name);
	if (!node)
		return (0);
	if (node->var)
		free(node->var);
	node->var = ft_strdup(var);
	if (!node->var && var)
	{
		return_error("minishell", "Malloc error on initializing\
		new env value", "name", 0);
		return (0);
	}
	return (node);
}

t_env	*ft_setenv(char *name, char *var)
{
	t_env	*node;

	if (!name)
		return (0);
	if (get_env_var(name))
		return (ft_setenv_existing(name, var));
	node = malloc(sizeof(t_env));
	if (!node)
		return (0);
	node->var = 0;
	node->next = 0;
	node->name = ft_strdup(name);
	if (!node->name)
	{
		free(node);
		return (0);
	}
	node->var = ft_strdup(var);
	if (!node->var && var)
	{
		free_node(node);
		return (0);
	}
	add_to_env(node);
	return (node);
}
