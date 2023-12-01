/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:09:15 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/30 12:27:30 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	As env builtin does, it prints out the env variables, but in ASCII
	order, including the variables which are not initialized.
*/
int	print_exported(t_list *env)
{
	t_var	*var;
	t_list	*sorted;

	sorted = NULL;
	if (env)
	{
		sorted = sort_env(env);
		if (!sorted)
			return (1);
		else
		{
			// print sorted
		}
	}
	// change printing
	while (env)
	{
		var = (t_var *)env->content;
		if (var->to_export)
		{
			if (var->name) // change to if (is_exported) ??
			{
				ft_putstr_fd("declare -x ", 1);
				ft_putstr_fd(var->name, 1);
			}
			if (var->value)
			{
				ft_putchar_fd('=', 1);
				ft_putchar_fd('"', 1);
				ft_putstr_fd(var->value, 1);
				ft_putchar_fd('"', 1);
			}
			ft_putchar_fd('\n', 1);
		}
		env = env->next;
	}
	return (0);
}

static int	env_var_exist(char *name, t_list *env)
{
	t_var	*var;

	while (env)
	{
		var = (t_var *)env->content;
		if (ft_strcmp(var->name, name) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

static void	update_var_content(char *name, char *new_value, t_list *env)
{
	t_var	*var;

	while (env)
	{
		var = (t_var *)env->content;
		if (ft_strcmp(var->name, name) == 0)
		{
			free(var->value);
			var->value = ft_strdup(new_value);
			return ;
		}
		env = env->next;
	}
}

/*
	Exports the specified variable to the subshells and child processes.
	• IF the var doesn't exist yet, a new one is created and appended
	• IF the var exist, if arg is initialized (at least = sign at the end),
		the variable need to be updated.
*/
static void	check_export(char *arg, t_list **env)
{
	t_var	*tmp_var;
	t_list	*new_node;

	new_node = NULL;
	tmp_var = NULL;
	tmp_var = create_var_content(arg);
	if (!env_var_exist(tmp_var->name, *env))
	{
		new_node = ft_lstnew(tmp_var);
		ft_lstadd_back(env, new_node);
	}
	else
	{
		if (tmp_var->value)
		{
			update_var_content(tmp_var->name, tmp_var->value, *env);
			del_var_content(tmp_var);
		}
	}
}

int	is_invalid_identifier(char *builtin, char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '=' || ft_isdigit(arg[0]))
		return (error(builtin, arg, CE_INVALIDIDENTIFIER), 1);
	while (ft_isalnum(arg[i]) || arg[i] == '_')
		i++;
	if (arg[i] != '=')
		return (error(builtin, arg, CE_INVALIDIDENTIFIER), 1);
	return (0);
}

int	export(t_cmd *cmd, t_data *data)
{
	int	i;

	if (!cmd->args[1])
		print_exported(data->env);
	else
	{
		i = 1;
		while (cmd->args[i])
		{
			if (is_invalid_identifier(cmd->args[0], cmd->args[i]))
				return (1);
			check_export(cmd->args[i], &data->env);
			i++;
		}
	}
	return (0);
}