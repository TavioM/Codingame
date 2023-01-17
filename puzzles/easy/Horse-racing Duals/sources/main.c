#include "file.h"

void	print_list(t_list *lst)
{
	int tmp;
	lst = ft_lstfirst(lst);
	while (lst)
	{
		tmp = *((int *)(lst->data));
		fprintf(stderr, "%d->", tmp);
		lst = lst->next;
	}
	fprintf(stderr, "\n");
}

int		compare(t_list *lst, int n)
{
	int tmp;
	int	prev;
	int	next;

//	print_list(lst);
	tmp = *((int *)(lst->data));
	if (lst && lst->prev)
	{
		prev = *((int *)(lst->prev->data));
		if (tmp - prev < n)
			n = tmp - prev;
	}
	if (lst && lst->next)
	{
		next = *((int *)(lst->next->data));
		if (next - tmp < n)
			n = next - tmp;
	}
	return n;
}

t_list	*add_sort(t_list *lst, t_list *new)
{
	int		nb;
	int		tmp;
	t_list	*cpy;

	if (lst == 0)
		return (new);
	nb = *((int *)(new->data));
	tmp = *((int *)(lst->data));
	cpy = lst;
	while (nb > tmp)
	{
		if (lst->next == 0)
		{
			lst->next = new;
			new->prev = lst;
			return (cpy);
		}
		lst = lst->next;
		tmp = *((int *)(lst->data));
	}
	if (lst != cpy)
	{
		new->next = lst;
		new->prev = lst->prev;
		lst->prev = new;
		new->prev->next = new;
		return (cpy);
	}
	else
	{
		new->next = lst;
		new->prev = 0;
		lst->prev = new;
		return (new);
	}
}

int	main()
{
	int		*p;
	int		n;
	int		min;
	t_list	*lst;
	t_list	*tmp;

	min = 2147483647;
	lst = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		p = malloc(sizeof(int));
		scanf("%d", p);
		tmp = ft_lstnew(p);
		lst = add_sort(lst, tmp);
		min = compare(tmp, min);
		if (min == 1)
			break;
	}
	printf("%d\n", min);
	return (0);
}
