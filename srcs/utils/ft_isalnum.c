/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:22:14 by romain            #+#    #+#             */
/*   Updated: 2021/05/20 15:51:49 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if (((unsigned char)c >= '0' && (unsigned char)c <= '9')
		|| (((unsigned char)c >= 'a' && (unsigned char)c <= 'z')
			|| ((unsigned char)c >= 'A' && (unsigned char)c <= 'Z')))
		return (1);
	return (0);
}
