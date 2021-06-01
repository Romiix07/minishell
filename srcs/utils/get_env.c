/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 15:30:23 by rmouduri          #+#    #+#             */
/*   Updated: 2021/05/27 14:24:45 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

char	*init_env_var(char *s)
{
	int		size;
	int		i;
	char	*var;

	size = 0;
	var = 0;
	size = ft_strlen_c(s, '=') + 1;
	size = ft_strlen(&s[size]);
	if (!ft_calloc((void **)&var, sizeof(char) * (size + 1)))
		return (0);
	var[size] = 0;
	size = ft_strlen_c(s, '=');
	i = -1;
	while (s[++size])
		var[++i] = s[size];
	return (var);
}

char	*init_env_name(char *s)
{
	int		size;
	int		i;
	char	*name;

	size = 0;
	name = 0;
	size = ft_strlen_c(s, '=');
	if (!ft_calloc((void **)&name, sizeof(char) * (size + 1)))
		return (0);
	name[size] = 0;
	size = -1;
	i = -1;
	while (s[++size] && s[size] != '=')
		name[++i] = s[size];
	return (name);
}

t_env	*ft_envnew(char *s)
{
	t_env	*node;

	node = 0;
	node = malloc(sizeof(t_env) * 1);
	if (!node)
		return (0);
	node->name = 0;
	node->var = 0;
	node->next = 0;
	node->name = init_env_name(s);
	if (!node->name)
		free(node);
	node->var = init_env_var(s);
	if (!node->var)
	{
		free(node->name);
		free(node);
	}
	return (node);
}

int	free_env(t_env *env)
{	
	t_env	*tmp;
	int		i;

	i = -1;
	while (env)
	{
		if (env->name)
			free(env->name);
		if (env->var)
			free(env->var);
		tmp = env;
		env = env->next;
		free(tmp);
	}
	return (0);
}

t_env	*init_env(char **env)
{
	int		i;
	t_env	*lstenv;
	t_env	*tmp;

	i = 0;
	if (!env)
		return (0);
	lstenv = ft_envnew(env[i]);
	if (!lstenv)
		return (0);
	tmp = lstenv;
	while (env[++i])
	{
		tmp->next = ft_envnew(env[i]);
		if (!tmp)
		{
			free_env(lstenv);
			return (0);
		}
		tmp = tmp->next;
	}
	return (lstenv);
}
