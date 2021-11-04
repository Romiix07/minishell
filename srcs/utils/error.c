/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 12:15:33 by rmouduri          #+#    #+#             */
/*   Updated: 2021/09/15 15:22:05 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

int	return_error(char *s1, char *s2, char *s3, int ret)
{
	if (s1)
		write(2, s1, ft_strlen(s1));
	if (s2)
	{
		write(2, ": ", 2);
		write(2, s2, ft_strlen(s2));
	}
	if (s3)
	{
		write(2, ": ", 2);
		write(2, s3, ft_strlen(s3));
	}
	write(2, "\n", 1);
	return (ret);
}
