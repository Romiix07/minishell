/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:24:54 by rmouduri          #+#    #+#             */
/*   Updated: 2021/06/01 11:28:13 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

static int	error_export(char *s)
{
	write(2, "minishell: export: << ", 22);
	write(2, s, ft_strlen(s));
	write(2, " >> : indentifiant non valable\n", 31);
	return (0);
}

static int	check_arg_export(char **input)
{
	int		i;

	i = 0;
	if (!input[1][i])
		return (0);
	while (input[1][i] && input[1][i] != '=')
	{
		if (!ft_isalnum(input[1][i]) && input[1][i] != '_')
			return (0);
		++i;
	}
	if (input[1][i] == '=')
		return (1);
	return (0);
}

t_env	*get_env_var(char *s, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, s))
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_export(char **input, t_env *env)
{
	t_env	*arg;
	char	*name;

	// if (input && input[0] && !input[1])
		// export_no_arg(input);
	if (!check_arg_export(input))
		return (1 + error_export(input[1]));
	name = init_env_name(input[1]);
	if (!name)
		return (1);
	arg = get_env_var(name, env);
	if (arg)
	{
		if (arg->var)
			free(arg->var);
		arg->var = init_env_var(input[1]);
	}
	else
	{
		env->next = ft_envnew(input[1]);
		if (!env->next)
			return (1);
	}
	return (0);
}
