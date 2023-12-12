/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:03:48 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/12 15:12:26 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**env_convert_to_double_pointer(t_list *env)
{
	char	**env_dptr;
	int		i;
	char	*name_value;
	char	*temp;

	i = 0;
	env_dptr = ft_calloc(ft_lstsize(env) + 1, sizeof(char *));
	while (env)
	{
		if (((t_var *)(env->content))->value)
		{
			name_value = ft_strjoin(((t_var *)(env->content))->name, "=");
			temp = name_value;
			name_value = ft_strjoin(name_value,
					((t_var *)(env->content))->value);
			free(temp);
		}
		else
			name_value = ft_strdup(((t_var *)(env->content))->name);
		env_dptr[i] = name_value;
		env = env->next;
		i++;
	}
	return (env_dptr);
}

char	**sort_export(t_list *env)
{
	char	**env_dptr;
	int		i;
	int		j;
	char	*temp;

	i = 0;
	env_dptr = env_convert_to_double_pointer(env);
	while (env_dptr[i])
	{
		j = i + 1;
		while (env_dptr[j])
		{
			if (env_dptr[i][0] > env_dptr[j][0])
			{
				temp = env_dptr[j];
				env_dptr[j] = env_dptr[i];
				env_dptr[i] = temp;
			}
			j++;
		}
		i++;
	}
	return (env_dptr);
}

void	print_each_line(int *i, bool *is_equal, char **sorted_env)
{
	int	j;

	j = 0;
	ft_putstr_fd("declare -x ", 1);
	while (sorted_env[*i][j])
	{
		ft_putchar_fd(sorted_env[*i][j], 1);
		if (sorted_env[*i][j] == '=')
		{
			ft_putchar_fd('"', 1);
			*is_equal = true;
		}
		j++;
	}
	if (*is_equal)
	{
		ft_putchar_fd('"', 1);
		*is_equal = false;
	}
	(*i)++;
	ft_putchar_fd('\n', 1);
}

size_t	find_min_len(char *str1, char *str2)
{
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len1 < len2)
		return (len1);
	else
		return (len2);
}

static void	swap(char **str1, char **str2)
{
	char		*temp;
	temp = *str2;
	*str2 = *str1;
	*str1 = temp;
}

char	**check_next_chars(char **sorted_env)
{
	int			i;
	int			j;
	size_t		min_len;

	i = 0;
	while (sorted_env[i])
	{
		j = i + 1;
		while (sorted_env[j])
		{
			if (sorted_env[i][0] == sorted_env[j][0])
			{
				min_len = find_min_len(sorted_env[i], sorted_env[j]);
				if (ft_strncmp(sorted_env[i], sorted_env[j], min_len) > 0)
					swap(&sorted_env[i], &sorted_env[j]);
			}
			j++;
		}
		i++;
	}
	return (sorted_env);
}
