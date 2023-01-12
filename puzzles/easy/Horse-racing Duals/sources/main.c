#include "file.h"

int	find_closest(t_list *lst)
{
	int		min;
	int		diff;
	t_list	*tmp;

	min = 2147483647;
	while (lst)
	{
		tmp = lst->next;
//		fprintf(stderr, "%d", *((int *)(lst->data)));
//		if (lst->next)
//			fprintf(stderr, ", ");
//		else
//			fprintf(stderr, " ");
		while (tmp)
		{
			diff = abs(*((int *)(tmp->data)) - *((int *)(lst->data)));
			if (diff < min)
				min = diff;
			tmp = tmp->next;
		}
		lst = lst->next;
	}
	fprintf(stderr, "\n");
	return (min);
}

int	main()
{
	int		n;
	int		*p;
	t_list	*lst;
	t_list	*tmp;

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		p = malloc(sizeof(int));
		scanf("%d", p);
		tmp = ft_lstnew(p);
		lst = ft_lstadd_back(lst, tmp);
	}
	n = find_closest(lst);
	printf("%d\n", n);
	return (0);
}
