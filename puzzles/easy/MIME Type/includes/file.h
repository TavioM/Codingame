#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

typedef struct	s_type
{
	char *EXT;
	char *MT;
}				t_type;

typedef struct s_list
{
	struct s_list	*next;
	struct s_list	*prev;
	void			*data;	
}				t_list;

//	ft_lst.c
t_list	*ft_lstnew(void *data);
t_list	*ft_lstfirst(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnth(t_list *lst, int n);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstadd_front(t_list *lst, t_list *new);
t_list	*ft_lstadd_back(t_list *lst, t_list *new);
t_list	*ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list *lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
