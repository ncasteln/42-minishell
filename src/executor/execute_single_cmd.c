/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:06:56 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/01 11:56:21 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_child_and_exit(t_node *node, char **env)
{
	// close pipes !!!!!!!!????
	free_cmd_node(node);
	free_dptr(env);
	exit(1);
}

/*
	@param exit(0) - this is the case in which there is no cmd->args (example
	when typing line '<<EOF' without anything else).
*/
static void	child_single_cmd(t_data *data)
{
	char	**env;
	t_cmd	*cmd;

	cmd = (t_cmd *)data->tree->content;
	env = convert_to_dptr(data->env);
	if (!env)
		exit(1);
	if (redirect_to_explicit(data->tree))
		free_child_and_exit(data->tree, env);
	if (cmd->args)
	{
		resolve_args(&cmd->args[0], env);
		if (execve(cmd->args[0], cmd->args, env))
		{
			error(cmd->args[0], NULL, CE_CMDNOTFOUND);
			exit(CE_CMDNOTFOUND);
		}
	}
	else
		exit(0);
}

static int	fork_one_ps(t_data *data)
{
	data->pid = ft_calloc(1, sizeof(int));
	if (!data->pid)
	{
		data->e_code = 1;
		return (error("executor", NULL, errno), 1);
	}
	data->pid[0] = fork();
	if (data->pid[0] == -1)
		return (error("fork", NULL, errno), 1);
	if (data->pid[0] == 0)
		child_single_cmd(data);
	return (0);
}

/*
	In case there is no pipe, the builtins has to be executed directly in the
	parent process, otherwise some of them would not take effect. Basic example
	would be "cd" command, which would change the directory inside the child ps
	and not in the parent.
*/
int	execute_single_cmd(t_data *data) // void or int ?
{
	if (is_builtin(data->tree->content))
		return (run_builtin_same_ps(data));
	else
	{
		if (fork_one_ps(data))
		{
			data->e_code = 1;
			return (1);
		}
	}
	return (0);
}
