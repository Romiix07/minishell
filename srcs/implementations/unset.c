/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:26:31 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/10 11:14:45 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_var(char *s)
{
	int	i;

	i = 0;
	if (!ft_isalpha(s[i]) && s[i] != '_')
		return (0);
	while (s[++i])
		if (!ft_isalnum(s[i]))
			return (0);
	return (1);
}

int	ft_unset(void)
{
	if (g_shell->fct[1] && !check_var(g_shell->fct[1]))
		return (return_error("minishell: unset", g_shell->fct[1],
				"not a valid identifier", 1));
	if (g_shell->fct[1])
		del_env_node(g_shell->env, g_shell->fct[1]);
	return (0);
}
