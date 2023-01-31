#include "file.h"

t_list	*ft_lstnew(void *data)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (0);
	list->data = data;
	list->prev = 0;
	list->next = 0;
	return (list);
}

t_list	*ft_lstfirst(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->prev)
		lst = lst->prev;
	return (lst);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_list	*ft_lstnth(t_list *lst, int n)
{
	if (n < 0)
		return (0);
	lst = ft_lstfirst(lst);
	for (int i = 0; i < n; i++)
	{
		if (!(lst->next))
			return (0);
		else
			lst = lst->next;
	}
	return (lst);
}

t_list	*ft_lstadd_front(t_list *lst, t_list *new)
{
	lst = ft_lstfirst(lst);
	if (!lst)
		return (new);
	new->prev = 0;
	new->next = lst;
	if (lst)
		lst->prev = new;
	return (new);
}

t_list	*ft_lstadd_back(t_list *lst, t_list *new)
{
	t_list	*begin;

	begin = ft_lstfirst(lst);
	lst = ft_lstlast(lst);
	if (!new)
		return (begin);
	new->next = 0;
	new->prev = lst;
	if (lst)
		lst->next = new;
	if (begin)
		return (begin);
	else
		return (new);
}

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	lst = ft_lstfirst(lst);
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_list	*ft_lstdelone(t_list *lst, void (*del)(void*))
{
	t_list	*tmp;

	tmp = lst;
	lst = ft_lstfirst(lst);
	if (lst == tmp)
		lst = lst->next;
	if (tmp && tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp && tmp->next)
		tmp->next->prev = tmp->prev;
	del(tmp->data);
	free(tmp);
	return (lst);
}

void	ft_lstclear(t_list *lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!lst || !del)
		return ;
	lst = ft_lstfirst(lst);
	while (lst)
	{
		del(lst->data);
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	lst = ft_lstfirst(lst);
	while (lst)
	{
		f(lst->data);
		lst = lst->next;
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	fprintf(stderr, "ft_lstmap is unusable\n");
	printf("ft_lstmap is unusable\n");
	return (0);
	t_list	*start;
	t_list	*tmp;

	if (!lst || !f)
		return (0);
	start = ft_lstnew(f(lst->data));
	if (!start)
		return (0);
	lst = lst->next;
	while (lst)
	{
		tmp = ft_lstnew(f(lst->data));
		if (!tmp)
		{
			ft_lstclear(start, del);
			return (0);
		}
		start = ft_lstadd_back(start, tmp);
		lst = lst->next;
	}
	return (start);
}
