/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_symbol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:08:09 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/10 16:39:53 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

static int	symbol_error(char symbol)
{
	write(STDERR_FILENO, "minishell: Redirection operator \" ", 34);
	if (symbol)
		write(STDERR_FILENO, &symbol, 1);
	else
		write(STDERR_FILENO, "newline", 7);
	write(STDERR_FILENO, " \" requires a valid argument\n", 29);
	return (0);
}

static int	check_symbol_2(char **input, int i, int symb)
{
	if (!input[i + 1])
		return (symbol_error(0));
	if (g_shell->ops[symb + 1] > 0)
		return (1);
	if (is_charset(input[i + 1][0], "<>|;&"))
		return (symbol_error(input[i + 1][0]));
	return (1);
}

static int	check_symbol_1(char **input, int i, int symb)
{
	int		j;
	int		len;

	if (g_shell->ops[symb] > 0)
		return (1);
	len = 0;
	j = -1;
	while (input[i][++j])
	{
		if (!is_charset(input[i][j], "<>"))
			break ;
		++len;
	}
	if (input[i][j] && !is_charset(input[i][j], "<>"))
		return (1);
	if (len == 2 && input[i][0] != input[i][1])
		return (symbol_error(input[i][1]));
	if (len > 2 && input[i][j - 1] == input[i][j - 2])
		return (symbol_error(input[i][j - 3]));
	else if (len > 2)
		return (symbol_error(input[i][j - 1]));
	return (check_symbol_2(input, i, symb));
}

int	check_symbol(char **input, int i)
{
	int	j;

	j = -1;
	while (input[++j])
	{
		if (g_shell->ops[i + j] == 0)
		{
			if (!ft_strcmp("|", input[j]) && (!input[j + 1]
					|| !ft_strcmp("|", input[j + 1])))
				return (symbol_error('|'));
			else if (is_charset(input[j][0], "<>")
				&& !check_symbol_1(input, j, i + j))
				return (0);
		}
	}
	return (1);
}
