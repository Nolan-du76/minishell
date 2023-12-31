/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_depth.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:39:44 by nmascrie          #+#    #+#             */
/*   Updated: 2023/12/12 09:39:45 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	array_depth(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i - 1);
}
