/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_quote_status_to_tokens.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:12:23 by fahmadia          #+#    #+#             */
/*   Updated: 2023/11/02 13:58:54 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_quote_status_to_tkn(t_list *tkns_head)
{
	t_list		*current_node;
	char		tkn_first_char;
	t_quote		position;
	t_tkn_data	*tkn_data;

	position = NOT_QUOTED;
	current_node = tkns_head;
	while (current_node)
	{
		tkn_data = ((t_tkn_data *)(current_node->content));
		tkn_first_char = *(tkn_data->str);
		detect_quote(tkn_data, tkn_first_char, &position);
		tkn_data->quote = position;
		if (tkn_data->quote == IN_S_QUOTE && tkn_first_char == S_QUOTE)
			tkn_data->quote = NOT_QUOTED;
		if (tkn_data->quote == IN_D_QUOTE && tkn_first_char == D_QUOTE)
			tkn_data->quote = NOT_QUOTED;
		current_node = current_node->next;
	}
}