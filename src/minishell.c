/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:38:38 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/12 18:02:13 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_data(t_data *data, char **env)
{
	data->env = init_env(env);
	if (!data->env)
	{
		error("init_data", NULL, CE_INITENV);
		exit(CE_INITENV);
	}
	data->input = NULL;
	data->tokens = NULL;
	data->tree = NULL;
	data->e_code = 0;
	data->n_ps = 0;
	data->pid = NULL;
	data->prompt = "minishell $ ";
}

static void	shell_loop(t_data *data)
{
	int N = 0; // leaks

	while (1)
	{
		set_sig_action(1);
		if (!N)
		{
			data->input = ft_strdup("unset PWD HOSTNAME HOME TERM SHLVL PATH OLDPWD _");		// for leaks
			N = 1;
		}
		else if (N)
		{
			// data->input = ft_strdup("env");		// for leaks
		}
		// data->input = readline(data->prompt);
		set_sig_action(0);
		switch_g_var(data);
		if (!data->input)
			break ;		// for leaks
		if (ft_strlen(data->input) != 0)
		{
			lexer(data->input, &data->tokens);
			parser(data);
			expansion(data);
			quote_removal(data);
			here_doc(data->tree, data);
			executor(data);
			// add_history(data->input);
			free_data(data);
			exit_custom(NULL, data);		// for leaks
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	terminal_config();
	if (argc > 1 || argv[1])
		return (error("argc/argv", NULL, CE_INVARG), CE_INVARG);
	init_data(&data, env);
	shell_loop(&data);
	free_data(&data);
	ft_lstclear(&data.env, del_var_content);
	rl_clear_history();
	ft_putendl_fd("exit", 1);
	return (0);
}
