/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elfetoua <elfetoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 23:41:48 by elfetoua          #+#    #+#             */
/*   Updated: 2020/01/10 15:35:27 by elfetoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"


t_list	*add_poly(t_list	*head_p1, t_list	*head_p2)
{
	t_list	*p_sum;
	
	p_sum = NULL;
	while (head_p1)
	{
		poly_add(&p_sum, head_p1->coeff, head_p1->exp);
		head_p1 = head_p1->next;
	}
	while (head_p2)
	{
		poly_add(&p_sum, head_p2->coeff, head_p2->exp);
		head_p2 = head_p2->next;
	}
	return (p_sum);
}

t_list	*sub_poly(t_list *head_p1, t_list *head_p2)
{
	t_list	*p_sub;
	t_list	*hd;

    p_sub = NULL;
	p_sub = (t_list*)malloc(sizeof(t_list));
	hd =  new_node(-1, 0);
	head_p2 = mul_poly(head_p2, hd);
	p_sub = add_poly(head_p2, head_p1);
	return (p_sub);
}

t_list	*mul_poly(t_list *head_p1, t_list *head_p2)
{
	t_list	*h1;
	t_list	*h2;
	t_list	*p_mul;
	int		coefficient;
	int		exponent;

	h1 = head_p1;
	p_mul = NULL;
	while (h1)
	{
		h2 = head_p2;
		while (h2)
		{
			coefficient = h1->coeff * h2->coeff;
			exponent = h1->exp + h2->exp;
			h2 = h2->next;
			poly_add(&p_mul, coefficient, exponent);
		}
		h1 = h1->next;
	}
	return (p_mul);
}

void		poly_add(t_list** mul, int coeff, int expo)
{
	t_list *node_add;
	t_list *temp;

	temp = *mul;
	node_add = NULL;
	if (*mul == NULL || (*mul)->exp < expo)
	{
		node_add = new_node(coeff, expo);
		*mul = node_add;
		(*mul)->next = temp;
	}
	else
	{
		while (temp)
		{
			if (temp->exp == expo)
			{
				temp->coeff = temp->coeff + coeff;
				return ;
			}
			if (temp->exp > expo && (temp->next == NULL || temp->next->exp < expo))
			{
				node_add = new_node(coeff, expo);
				node_add->next = temp->next;
				temp->next = node_add;
				return ;
			}
			temp = temp->next;
		}
		node_add->next = NULL;
		temp->next = node_add;
	}
}

void	oppos_poly(t_list	*poly)
{
	t_list	*p;
	p = new_node(-1, 0);
	p = mul_poly(p, poly);
	printf("\nl'opposee du polynome est :\n");
	afficher_poly(&p);
	free_list(&p);
}

t_list	*puiss_n(t_list* poly, int n)
{
	t_list	*np;

	np = new_node(1,0);
	if (n == 1)
		return (poly);
	if (n == 0)
		np = new_node(1,0);
	if (n > 0)
			np = mul_poly(poly, puiss_n(poly, n - 1));
	return (np);
}

t_list*	division(t_list *p, t_list *d, int a)
{
	t_list	*quotion, *Q;
	t_list	*rest;
	t_list	*in, *lben;

	if ((d->coeff == 0 && d->exp == 0) || (int)p->coeff % (int)d->coeff != 0)
		return NULL;
	quotion = NULL;
	Q = NULL;
	while (p->exp - d->exp >= 0)
	{
		insert_node(&quotion, (int)(p->coeff / d->coeff), p->exp - d->exp);
		afficher_poly(&quotion);
		in = mul_poly(quotion, d);
		rest = sub_poly(p, in);
		free_list(&p);
		lben = rest;
		while (rest->coeff == 0 && rest->next != NULL)
		{
			lben = rest;
			rest = rest->next;
			free (lben);
		}
		p = rest;
		afficher_poly(&p);
		insert_node(&Q, (int)quotion->coeff, quotion->exp);
		quotion = quotion->next;
	}
	if(a == 1)
	{
		printf("\nle quotion est :\n");
		afficher_poly(&Q);
		printf("\nle rest est :\n");
		afficher_poly(&rest);
	}
	return (rest);
}

void	derivative(t_list	*poly)
{
	t_list	*head;
	
	head = poly;
	while (head)
	{
		head->coeff = head->coeff * head->exp;
		head->exp--;
		head = head->next;
	}
	afficher_poly(&poly);
}

void	primitive(t_list	*poly)
{
	t_list	*head;
	t_node	*new, *prim;
	
	head = poly;
	prim = NULL;
	while (head)
	{
		new = (t_node*)malloc(sizeof(t_node));
		if (!new)
			return ;
		if (head->coeff % (head->exp + 1) == 0)
			{
				new->coeff[0] = head->coeff / (head->exp + 1);
				new->coeff[1] = 1;
				new->exp = head->exp + 1;
			}
		else
		{
			new->coeff[0] = head->coeff;
			new->coeff[1] = head->exp + 1;
			new->exp = head->exp + 1;
		}
		insert_node2(&prim, new->coeff, new->exp);
		if (head->next == NULL)
			new->next = NULL;
		else
			new->next = (t_node*)malloc(sizeof(t_node));
		head = head->next;
	}
	print_poly(&prim);
}

void	pgcd_poly(t_list* a, t_list* b)
{
	t_list*	r;
	r = (t_list*)malloc(sizeof(t_list));
	r = division(a, b, 0);
	if (r->coeff == 0)
	{
		printf("le pgcd est:\n");
		afficher_poly(&b);
	}
	else
		pgcd_poly(b, r);
}

void	calcule(t_list	*poly)
{
	int		val;
	int		x;

	printf("entrer la valeur a calculer\n");
	scanf("%d", &val);
	x = 0;
	while (poly)
	{
		x += (poly->coeff) * ft_power(val, poly->exp);
		poly = poly->next;
	}
	printf("P(%d) = %d\n", val, x);
	if (x == 0)
		printf("%d est un zéro d’un polynôme\n", val);
}