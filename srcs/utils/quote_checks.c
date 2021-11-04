/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:27:32 by rmouduri          #+#    #+#             */
/*   Updated: 2021/10/22 11:17:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_check(char *arg, int index)
{
	char	c;

	c = arg[index];
	while (arg[++index])
	{
		if (arg[index] == c)
		{
			return (1);
		}
	}
	return (0);
}
