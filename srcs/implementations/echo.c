/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:48:47 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/09 11:58:48 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "minishell.h"

int	ft_echo(char **args)
{
	int			i;
	__int8_t	op;

	op = 0;
	i = -1;
	if (args && *args && !ft_strcmp(args[0], "-n"))
	{
		i = 0;
		op = 1;
	}
	while (args && *args && args[++i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
	}
	if (!op)
		write(1, "\n", 1);
	return (0);
}
