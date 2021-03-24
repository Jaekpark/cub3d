/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:19:26 by parkjaekw         #+#    #+#             */
/*   Updated: 2021/03/23 16:05:31 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef struct s_list
{
	char *content;
	struct s_list *next;
}	t_list;

typedef struct s_test
{
	char c;
	t_list *head;
}		t_test;

void init(t_test *test)
{
	test->c = 0;
	test->head = malloc(sizeof(t_list) * 1);
}

int something(t_test *test, char *line)
{
	t_list *new_node;
	t_list *temp;

	new_node = malloc(sizeof(t_list) * 1);
	new_node->content = line;
	temp = test->head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
	return (1);
}

int main_loop(void)
{
	t_test test;
	init(&test);
	something(&test, "1 0 1 0 4 5 6 7 3 4 1 0 0 0 0 3 4");
	something(&test, "123456");
	something(&test, "fff");
	while (test.head->next != NULL)
	{
		test.head = test.head->next;
		printf("%s\n", test.head->content);

	}
	//printf("test %s\n", test.head->next->next->content);
	return (0);
}

int main(void)
{
	main_loop();
	return (0);
}
