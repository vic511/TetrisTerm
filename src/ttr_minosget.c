#include "ttr_minos.h"

void		minos_errorfilter(t_minos **minoslist)
{
  t_minos	*tmp;
  t_minos	*tmp2;

  while ((tmp = *minoslist) && !tmp->shape)
    {
      *minoslist = tmp->next;
      free(tmp);
    }
  while (tmp && tmp->next)
    if (!tmp->next->shape)
      {
	tmp2 = tmp->next;
	tmp->next = tmp2->next;
	free(tmp2);
      }
    else
      tmp = tmp->next;
}

void		minos_getmax(const t_minos *minoslist, t_coords *maxsize)
{
  const t_minos	*curr;

  if (!minoslist)
    return ;
  maxsize->x = minoslist->size.x;
  maxsize->y = minoslist->size.y;
  curr = minoslist->next;
  while (curr)
    {
      if (curr->size.x > maxsize->x)
	maxsize->x = curr->size.x;
      if (curr->size.y > maxsize->y)
	maxsize->y = curr->size.y;
      curr = curr->next;
    }
}

const t_minos	*minos_getrand(const t_minos *minoslist)
{
  size_t	len;
  size_t	index;
  const t_minos	*minos;

  if (!minoslist)
    return (NULL);
  minos = minoslist;
  len = 0;
  while (minos && ++len)
    minos = minos->next;
  index = rand() % len;
  minos = minoslist;
  len = 0;
  while (len++ < index)
    minos = minos->next;
  return (minos);
}
