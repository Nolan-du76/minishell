/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuette <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:19:57 by mjuette           #+#    #+#             */
/*   Updated: 2023/11/28 14:19:58 by mjuette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_received_signal;

static char	*create_list(t_env *env)
{
	char	*a;

	a = ft_calloc(1, sizeof(char));
	while (env)
	{
		super_concat(&a, env->name);
		super_concat(&a, "=");
		super_concat(&a, env->value);
		super_concat(&a, "\n");
		if (!env->next)
			break ;
		env = env->next;
	}
	while (env->previous)
		env = env->previous;
	return (a);
}

static int	err_env(t_cmd *cmd, char *vars)
{
	if (!ft_strchr(cmd->tokens->str, '='))
	{
		handle_output_create(cmd);
		error_print(ERROR, "No such file or directory",
			cmd->tokens->str);
		free(vars);
		g_received_signal = SIGNAL_ABORT;
		return (0);
	}
	return (1);
}

void	ft_env(t_cmd *cmd, t_main *main)
{
	char	*vars;

	if (!cmd->tokens->next->str)
	{
		vars = create_list(main->env);
		print_io(cmd, vars, &main);
		free(vars);
	}
	else
	{
		vars = create_list(main->env);
		cmd->tokens = cmd->tokens->next;
		while (cmd->tokens->str)
		{
			if (!err_env(cmd, vars))
				return ;
			super_concat(&vars, cmd->tokens->str);
			super_concat(&vars, "\n");
			cmd->tokens = cmd->tokens->next;
		}
		print_io(cmd, vars, &main);
		free(vars);
	}
}
