/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:20:48 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/27 08:21:18 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	cd changes the current working directory of the current shell env. Only a
	relative or an absolute path are accepted.
*/
int	cd(char *path, char **env)
{
	char	*old_dir;
	char	*new_dir;

	if (chdir(path) == -1)
		return (ENOENT);
	new_dir = ft_strdup(get_wd());
	update_env_var("PWD=", new_dir, env);
	return (0);
}
