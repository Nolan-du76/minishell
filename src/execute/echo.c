/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuette <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:19:45 by mjuette           #+#    #+#             */
/*   Updated: 2023/11/28 14:19:48 by mjuette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_received_signal;

void	ft_echo(t_cmd *cmd, t_main *main)
{
	char	*str;

	str = ft_calloc(1, sizeof(char));
	cmd->tokens = cmd->tokens->next;
	if (ft_equals(cmd->tokens->str, "-n"))
	{
		g_received_signal = 0;
		cmd->tokens = cmd->tokens->next;
	}
	while (cmd->tokens->str)
	{
		super_concat(&str, cmd->tokens->str);
		if (cmd->tokens->next->str && cmd->tokens->has_space)
			super_concat(&str, " ");
		cmd->tokens = cmd->tokens->next;
	}
	if (g_received_signal == IGNORE_NEW_LINE)
		super_concat(&str, "\n");
	print_io(cmd, str, &main);
	free(str);
}
