/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 09:47:06 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/23 11:03:13 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;

	while (*lst)
	{
		current = *lst;
		*lst = (*lst)-> next;
		ft_lstdelone(current, del);
	}
}
