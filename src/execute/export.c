/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:43:28 by nmascrie          #+#    #+#             */
/*   Updated: 2023/11/21 09:43:30 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_received_signal;

static int	is_valid_input(char *input)
{
	int	i;

	i = 0;
	if (input[0] == '=')
		return (0);
	if (ft_isdigit(input[i]) == 1)
		return (0);
	i++;
	while (input[i] && input[i] != '=')
	{
		if (ft_isalnum(input[i]) == 0)
			return (-1);
		i++;
	}
	return (1);
}

static void	add_env(t_cmd *cmd, t_main **main)
{
	char	*name;
	char	*value;

	while (cmd->tokens->str)
	{
		generate_env(cmd->tokens->str, &name, &value);
		if (name && is_system_env(name))
			error_env();
		if (value && value[0])
			add_to_env(&(*(main))->env, name, value);
		if (ft_equals(name, "PWD"))
			chdir(value);
		free(name);
		if (value)
			free(value);
		cmd->tokens = cmd->tokens->next;
	}
}

int	is_valid_tokens(t_cmd *cmd)
{
	while (cmd->tokens->str)
	{
		if (!is_valid_input(cmd->tokens->str))
		{
			error_print(ERROR, "not a valid identifier", cmd->tokens->str);
			g_received_signal = SIGNAL_ABORT;
			return (0);
		}
		cmd->tokens = cmd->tokens->next;
	}
	while (cmd->tokens->previous)
		cmd->tokens = cmd->tokens->previous;
	return (1);
}

void	ft_export(t_cmd *cmd, t_main **main)
{
	char	*vars;

	if (!cmd->tokens->next->str)
	{
		vars = print_sorted_env((*main)->env);
		g_received_signal = IGNORE_NEW_LINE;
		print_io(cmd, vars, main);
		free(vars);
	}
	if (!is_valid_tokens(cmd))
		return ;
	add_env(cmd, main);
}
