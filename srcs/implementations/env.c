/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 16:02:50 by rmouduri          #+#    #+#             */
/*   Updated: 2021/05/25 16:28:09 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

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
