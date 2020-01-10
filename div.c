/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elfetoua <elfetoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 23:18:37 by elfetoua          #+#    #+#             */
/*   Updated: 2019/12/15 23:32:22 by elfetoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "interface.h"

t_list	*division1(t_list *p, t_list *d)
{
	t_list	*quotion, *Q;
	t_list	*rest;
	t_list	*in, *temp;
	int		a;

	if (d->coeff == 0 && d->exp == 0)
		return NULL;
    if (p->exp < d->exp)
        return (p);
  
		insert_node(&quotion, (p->coeff / d->coeff), p->exp - d->exp);
		afficher_poly(&quotion);
		in = NULL;
		in = mul_poly(quotion, d);
		afficher_poly(&in);
		rest = sub_poly(p, in);
        p = rest;
        scanf("%d", &a);
        division1(p, d);
        insert_node(&quotion, (p->coeff / d->coeff), p->exp - d->exp);
		afficher_poly(&quotion);
        free(in);

	printf("**4**\n");
	afficher_poly(&Q);
	afficher_poly(&rest);
    return (NULL);
}