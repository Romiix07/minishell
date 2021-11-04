/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 10:13:28 by cmarien           #+#    #+#             */
/*   Updated: 2021/11/03 23:51:45 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "minishell.h"

// int	echo_simple(char **arg, int *index, int arg_sz, char **buff)
// {
// 	*index += 1;
// 	if (arg[arg_sz][*index] == '\'')
// 	{
// 		*buff = concatenate_str(*buff, '\n');
// 		*index += 1;
// 		return (1);
// 	}
// //	write(1, "c", 1);
// 	if (quote_check(arg[arg_sz], *index - 1) == 0)
// 	{
// 		*buff = concatenate_str(*buff, '\'');
// 		return (1);
// 	}
// //	write(1, "a", 1);
// 	while (arg[arg_sz][*index] != '\0' && arg[arg_sz][*index] != '\'')
// 	{
// 		*buff = concatenate_str(*buff, arg[arg_sz][*index]);
// 		(*index) += 1;
// //		printf("-------------------------\n");
// //		printf("%d\n", ft_strlen(*buff));
// //		printf("%s\n", *buff);
// //		printf("-------------------------\n");
// 	}
// 	*index += 1;
// //	printf("-------------------------\n");
// //	printf("%d\n", ft_strlen(*buff));
// //	printf("%s\n", *buff);
// //	printf("-------------------------\n");
// 	return (1);
// }

// int	echo_double(char **arg, t_echo *echo)
// {
// 	echo->index += 1;
// 	if (arg[echo->arg_sz][echo->index] == '"')
// 	{
// 		echo->buff = concatenate_str(echo->buff, '\n');
// 		echo->index += 1;
// 		return (1);
// 	}
// 	if (quote_check(arg[echo->arg_sz], echo->index - 1) == 0)
// 	{
// 		echo->buff = concatenate_str(echo->buff, '"');
// 		return (1);
// 	}
// 	while (arg[echo->arg_sz][echo->index] != '\0' && arg[echo->arg_sz][echo->index] != '"')
// 	{
// 		echo->buff = concatenate_str(echo->buff, arg[echo->arg_sz][echo->index]);
// 		echo->index += 1;
// 	}
// 	echo->index += 1;
// 	return (1);
// }

// int	ft_echo(char **arg)
// {
// 	t_echo	echo;

// 	for (int i = 0; arg[i]; ++i)
// 	{
// 		write(1, arg[i], ft_strlen(arg[i]));
// 		write(1, "\n", 1);
// 	}
// 	return (0);
// 	echo.arg_sz = -1;
// 	echo.buff = NULL;
// //	printf("%s\n", arg[0]);
// /*	while (shell->env->next)
// 	{
// 		printf("%s\n", shell->env->name);
// 		printf("%s\n", shell->env->var);
// 		shell->env = shell->env->next;
// 	}
// */	
// //	if (!(arg))
// //	{
// //		echo.buff = concatenate_str(echo.buff, "\n");
// 	//	printf("%d\n", ft_strlen(echo.buff));
// 	//	printf("%s\n", echo.buff);
// //		return ;
// //	}
// 	if (arg && (arg[0][0] == '-' && arg[0][1] == 'n' && ft_strlen(arg[0]) == 2))
// 	{
// 		echo.arg_sz = 0;
// 	}
// 	while (arg && arg[++echo.arg_sz] != NULL)
// 	{
// 		echo.index = 0;
// //		printf("b'");
// 		while (arg[echo.arg_sz][echo.index])
// 		{
// 			if (arg[echo.arg_sz][echo.index] == '\'')
// 			{
// 				if (echo_simple(arg, &echo.index, echo.arg_sz, &echo.buff) == 0)
// 					return 0;
// 			}
// 		 	else if (arg[echo.arg_sz][echo.index] == '"')
// 			{
// 				echo_double(arg, &echo);
// 			}
// 		//		printf("---------\n");
// 		//		printf("%d\n", ft_strlen(arg[echo.arg_sz]));
// 		//		printf("%d\n", echo.index);
// 		//		printf("---------\n");
// 			else
// 			{
// 			//	printf("%s\n", echo.buff);
// 				echo.buff = concatenate_str(echo.buff, arg[echo.arg_sz][echo.index]);
// 				echo.index++;
// 			}
// 		}
// 		//printf("%s\n", "AB");
// 		if (echo.index > 0 && arg[echo.arg_sz + 1] && echo.buff)
// 			echo.buff = concatenate_str(echo.buff, ' ');
// 	}
// 	if (!arg || (!(arg[0][0] == '-' && arg[0][1] == 'n' && ft_strlen(arg[0]) == 2)))
// 	{
// 		if (echo.buff)
// 		{
// 			if (echo.buff[ft_strlen(echo.buff) - 1] != '\n')
// 				echo.buff = concatenate_str(echo.buff, '\n');
// 		}
// 		else
// 		{
// 			echo.buff = concatenate_str(echo.buff, '\n');
// 		}
// 	}
// 	printf("buff_size:\n%d\n-------------\n", ft_strlen(echo.buff));
// 	if (echo.buff)
// 		ft_putstr(echo.buff);
// 	printf("-------------\narg_sz:\n%d\n", echo.arg_sz);
// 	return (1);
// }

int	ft_echo(char **args)
{
	int			i;
	__int8_t	op;

	op = 0;
	i = -1;
	if (args && !ft_strcmp(args[0], "-n"))
	{
		i = 0;
		op = 1;
	}
	while (args && args[++i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
	}
	if (!op)
		write(1, "\n", 1);
	return (0);
}
