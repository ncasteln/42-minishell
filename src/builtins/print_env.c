/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:16:10 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/14 10:57:45 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Outputs the environment variables which are at least an empty string. The
	uninitalized env var are not output like in the standar env builtin.
*/
void	print_env(t_list *env)
{
	t_var	*var;

	ft_printf("\033[0;36m============= ENVIRONMENT =============\033[0;37m\n");
	while (env)
	{
		var = (t_var *)env->content;
		if (var)
		{
			if (var->name && var->value)
			{
				ft_putstr_fd(var->name, 1);
				ft_putchar_fd('=', 1);
				ft_putendl_fd(var->value, 1);
			}
		}

		env = env->next;
	}
	ft_printf("\033[0;36m=======================================\033[0;37m\n");
}