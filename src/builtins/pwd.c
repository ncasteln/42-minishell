/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 10:52:18 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/20 15:03:11 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_blank_str(char *s)
{
	while (*s)
	{
		if (*s != ' ' && *s != '\n' && *s != '\t')
			return (0);
		s++;
	}
	return (1);
}

/*
	pwd command returns the current working path. As the subject states, it has
	not to handle any option (-P and -L) like the original Shell buil-in. In
	those case an error is returned.
	ATTENTION: the dir returned is not allocated on the heap!
*/
const char	*get_wd(char *opt)
{
	char	*dir;
	char	*buff;
	size_t	size;

	// if (opt && !is_blank_str(opt))
	// 	return (E2BIG); // set argument error ???
	size = 1;
	buff = ft_calloc(size + 1, sizeof(char)); // protect --- create err function!
	dir = getcwd(buff, size);
	while (!dir)
	{
		free(buff);
		size += 1;
		buff = ft_calloc(size + 1, sizeof(char)); // protect --- create err function
		dir = getcwd(buff, size);
	}
	free (buff);
	return (dir);
}