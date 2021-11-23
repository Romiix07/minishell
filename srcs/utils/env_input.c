/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:09:16 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/23 11:54:23 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_input(char *name, char str[256])
{
	char	*s;

	if (!name || name[0] != '$' || (name[0] == '$'
			&& name[1] != '_' && !ft_isalpha(name[1])))
		return (0);
	s = NULL;
	if (get_env_var(get_var_name(name, str)))
		s = select_env_var(name, str);
	if (s != NULL)
		return (s);
	if (name[0] == '$' && (ft_isalpha(name[1]) || name[1] == '_'))
	{
		str[0] = 0;
		return ((char *)str);
	}
	return (0);
}
