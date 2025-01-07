/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:24:40 by nbk               #+#    #+#             */
/*   Updated: 2024/09/04 15:38:34 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

typedef struct s_list
{
	char				*content;
	struct s_list		*next;
}	t_list;

t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstnew(char *content);
void		ft_lstadd_back(t_list **lst, t_list *new_lst);
void		ft_lstadd_front(t_list **lst, t_list *new_lst);
void		ft_lstdelone(t_list *lst);
int			ft_lstsize(t_list *lst);
void		ft_lstclear(t_list **lst);
t_list		*ft_lstcpy(t_list **list);

#endif
