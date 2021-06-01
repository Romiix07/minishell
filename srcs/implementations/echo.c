/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 10:13:28 by cmarien           #+#    #+#             */
/*   Updated: 2021/05/27 11:35:10 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

void	echo_simple(char **arg, int *index, int arg_sz, char *buff)
{
	int		r;
	char	c;

	r = 1;
	while (arg[arg_sz][*index] != '\0' && arg[arg_sz][*index] != '\'')
	{
		concatenate_str(buff, arg[arg_sz][*index]);
		(*index) += 1;
	}
	if (arg[arg_sz][*index] == '\0')
	{
		r = read(0, &c, 1);
		while (r > 0)
		{
			if (c == '\n' || !c)
				break ;
			buff = concatenate_str(buff, c);
			if (!buff)
				return ;
			r = read(0, &c, 1);
		}
	}
}

int	ft_echo(char **arg, char *filename)
{
	int	arg_sz;
	int	index;
	char *buff;

	arg_sz = -1;
	buff = 0;
	while (arg[++arg_sz] != NULL)
	{
		index = 0;
		while (arg[arg_sz][index])
		{
			if (arg[arg_sz][index] == '\'')
				echo_simple(arg, &index, arg_sz, buff);
		 	// else if (arg[arg_sz][index] == '"')
				// echo_double(arg, &index, arg_sz, buff);
			// else if (arg[arg_sz][index] == '$')
				// echo_dollar(arg, &index, arg_sz, buff);
			else
			{
				buff = concatenate_str(buff, arg[arg_sz][index]);
				index++;
			}
		}
	}
	return (0);
}
