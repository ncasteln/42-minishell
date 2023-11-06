/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:31:07 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/06 11:11:50 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
#include "lexer.h"
/*
	SYNTAX TREE
	The tree is composed by t_node items. Each t_node can be either of type
	IS_PIPE or IS_CMD, and consequently its content is either t_pipe or t_cmd.
*/
enum e_node
{
	IS_PIPE,
	IS_CMD
};

typedef struct s_node
{
	int			n;
	enum e_node	type;
	void		*content;
}	t_node;

/*
	t_pipe is the content of t_node, when its type is IS_PIPE.
	It holds just two address to 2 different t_node.
*/
typedef struct s_pipe
{
	struct s_node	*left;
	struct s_node	*right;
}	t_pipe;

/*
	t_cmd is the content of t_node in case its type is IS_CMD'
	It holds information about the tokens in a block delimited by start/end of
	the input, and by pipes.
	@param tkn_sublist - given an input of "ls -la | cat -eb >out1", the list is
	divided into [ls -la | ][cat -eb >out1]
*/
typedef struct s_cmd
{
	t_list			*tokens;
	char			**args;			// top cat -e ls
	t_list			*redir;			// in1(<) - out4(>) - temp1(<<) - temp2(<<) - temp3(<<) - (null or "")(>)
	int				fd_in;			// still necessary ???
	int				fd_out;
	int				err_code;
}	t_cmd;

enum e_redir
{
	REDIR_IN = '<',		// <
	REDIR_OUT = '>',	// >
	REDIR_HERE_DOC,		// <<
	REDIR_APPEND		// >>
};

typedef struct s_redir
{
	char			*file_name;
	enum e_redir	type;
}	t_redir;

// ---------------------------------------------------------------- SYNTAX TREE
t_node	*build_syntax_tree(t_list *token, int n);
void	free_tree(t_node *tree);

// -------------------------------------------------------------------- PARSING
void	parse(t_node *tree);

// ---------------------------------------------------------------- PARSE REDIR
void	update_cmd_tab_redir_type(t_cmd *cmd, t_tkn_data *tkn_curr, t_tkn_data *tkn_next);
void	update_cmd_tab_redir_filename(t_cmd *cmd, t_tkn_data *tkn_curr);
int		is_redir_syntax_err(t_tkn_data *curr, t_tkn_data *next);
int		is_redir(t_tkn_type tkn_type);

// ----------------------------------------------------------------- PARSE ARGS
void	update_cmd_tab_args(t_cmd *cmd, t_tkn_data *tkn_curr);

// ----------------------------------------------------------------- PARSE PIPE
int		is_pipe_syntax_err(t_tkn_data *curr, t_tkn_data *next);

// ---------------------------------------------------------------- PRINT UTILS
void	print_syntax_tree(t_node *root);

#endif
