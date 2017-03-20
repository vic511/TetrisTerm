#include <stddef.h>

void		*my_memset(void *s, int c, size_t n)
{
  size_t	i;
  char		*p;

  p = s;
  i = 0;
  while (i < n)
    p[i++] = c;
  return (s);
}

void		*my_memcpy(void *dest, const void *src, size_t n)
{
  size_t	i;

  i = 0;
  while (i++ < n)
    ((char *) dest)[i - 1] = ((char *) src)[i - 1];
  return (dest);
}
