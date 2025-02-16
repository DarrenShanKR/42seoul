#include "push_swap.h"

int	roll_back(Stack *a, Stack *b, int cnt_ra, int cnt_rb)
{
	int		i;
	int		num;
	int		count;

	count = 1;
	num = cnt_ra;
	if (cnt_ra < cnt_rb)
		rrb(b, 0);
	else if (cnt_ra > cnt_rb)
	{
		num = cnt_rb;
		rra(a, 0);
	}
	else
		count--;
	i = 0;
	while (i < num)
	{
		rrr(a, b);
		i++;
	}
	count += num;
	return (count);
}

int	main(int	argc, char		*argv[])
{
	Stack		*a;
	Stack		*b;
	t_Pushswap	*p;
	int			count;
	int			sorted;

	sorted = TRUE;
	if (argc <= 1)
	{
		write(1, "Error", sizeof("Error"));
		return (0);
	}
	a = init();
	b = init();
	count = parcing_input(argc, argv, a);
	if (check_sorted(a, size(*a)) == TRUE)
		exit(0);
	p = push_swap_init();
	a_to_b(a, b, size(*a), p);
	print_stack(a ,b);
	exit(0);
}

/*
    print_stack(a, b);
    printf("count %d\n ", p->count);
    if (check_sorted(a, size(*a)) == TRUE)
      printf("Properly sorted\n");
    */
