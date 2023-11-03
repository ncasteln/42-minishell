/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:22:05 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/03 14:07:14 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir_syntax_err(t_tkn_data *curr, t_tkn_data *next)
{
	ft_printf("   • Check if [%s] & [%s] are valid\n", curr->str, next->str);
	return (0);
}

int	is_redir(int tkn_type)
{
	if (tkn_type == TKN_REDIRECT_OUT_CONCAT ||
		tkn_type == TKN_HERE_DOC ||
		tkn_type == TKN_REDIRECT_IN ||
		tkn_type == TKN_REDIRECT_OUT )
		return (tkn_type);
	return (0);
}

/*
	Add the current redirection token to the list of redirections of the command
	table, and changes the next token type to "TKN_FILE_NAME", so that it can
	be catched in the next iteration.
*/
void	update_cmd_tab_redir_type(t_cmd *cmd, t_tkn_data *tkn_curr, t_tkn_data *tkn_next)
{
	t_redir	*redir_content;
	t_list	*new_redir;

	redir_content = ft_calloc(1, sizeof(t_redir)); // prtct
	redir_content->file_name = tkn_next->str;
	redir_content->type = tkn_curr->type; // correct names
	new_redir = ft_lstnew(redir_content);
	tkn_next->type = TKN_FILE_NAME;
	ft_lstadd_back(&cmd->redir, new_redir);
	ft_printf("   • Added type [%c] to redir\n", redir_content->type);
}

void	update_cmd_tab_redir_filename(t_cmd *cmd, t_tkn_data *tkn_curr)
{
	t_redir	*last;

	last = ft_lstlast(cmd->redir)->content;
	last->file_name = tkn_curr->str;
	ft_printf("   • Added filename [%s] to redir\n", last->file_name);
}
