/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 16:02:50 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/18 10:37:24 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

t_env	*get_env_node(char *s)
{
	t_env	*tmp;

	tmp = g_shell->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, s) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

void	del_env_node(t_env *env, char *name)
{
	t_env	*tmp;
	t_env	*to_next;

	tmp = env;
	while (tmp && tmp->next && ft_strcmp(tmp->next->name, name))
		tmp = tmp->next;
	if (!tmp || !tmp->next)
		return ;
	to_next = tmp->next->next;
	free(tmp->next->name);
	free(tmp->next->var);
	free(tmp->next);
	tmp->next = to_next;
}

t_env	*create_env_node(char *name, char *var)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (0);
	node->name = ft_strdup(name);
	if (!node->name)
	{
		free(node);
		return (0);
	}
	if (var)
		node->var = ft_strdup(var);
	else
		node->var = 0;
	if (!node->var && var)
	{
		free(node->name);
		free(node);
		return (0);
	}
	return (node);
}

int	print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		write(1, tmp->name, ft_strlen(tmp->name));
		write(1, "=", 1);
		write(1, tmp->var, ft_strlen(tmp->var));
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	return (1);
}
