/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_close_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 19:38:37 by rmouduri          #+#    #+#             */
/*   Updated: 2021/10/28 18:31:37 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	dup_close_set(int fd1, int fd2, int val)
{
	if (dup2(fd1, fd2) == -1)
		return (0);
	close(fd1);
	fd1 = val;
	return (1);
}
