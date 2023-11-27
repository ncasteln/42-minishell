/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote_removal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 08:34:59 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/27 10:28:20 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	args_quote_removal(t_cmd *cmd, t_data *data)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			if (ft_strchr(cmd->args[i], TKN_D_QUOTE) || ft_strchr(cmd->args[i], TKN_S_QUOTE))
			{
				tmp = cmd->args[i];
				cmd->args[i] = remove_quote_pairs(cmd->args[i]); // check leaks and protect
				free(tmp);
				if (cmd->args[i] == NULL)
					return (error(cmd->args[i], NULL, CE_EXPANSION), 1);
			}
			i++;
		}
	}
	return (0);
}

static int	redir_quote_removal(t_cmd *cmd, t_data *data)
{
	t_list			*redir;
	t_redir_data	*redir_content;
	char			*tmp;

	redir = (t_list *)cmd->redir;
	redir_content = NULL;
	tmp = NULL;
	while (redir)
	{
		redir_content = (t_redir_data *)redir->content;
		if (redir_content->type != REDIR_HERE_DOC)
		{
			if (ft_strchr(redir_content->file_name, TKN_D_QUOTE) || ft_strchr(redir_content->file_name, TKN_S_QUOTE))
			{
				tmp = redir_content->file_name;
				redir_content->file_name = expand(redir_content->file_name, data);
				free(tmp);
				if (!redir_content->file_name)
					return (error(redir_content->file_name, NULL, CE_EXPANSION), 1);
			}
		}
		redir = redir->next;
	}
	return (0);
}

static int	check_quote_removal(t_cmd *cmd, t_data *data)
{
	if (args_quote_removal(cmd, data))
		return (1);
	if (redir_quote_removal(cmd, data))
		return (1);
	return (0);
}

void	quote_removal(t_data *data)
{
	t_node	*node;
	t_cmd	*cmd;
	t_pipe	*pipe;

	if (!data->tree || data->e_code)
		return ;
	node = data->tree;
	while (node->type == IS_PIPE)
	{
		pipe = (t_pipe *)node->content;
		cmd = pipe->left->content;
		if (check_quote_removal(cmd, data))
		{
			data->e_code = 1;
			return ;
		}
		node = pipe->right;
	}
	cmd = node->content;
	if (check_quote_removal(cmd, data))
		data->e_code = 1;
}