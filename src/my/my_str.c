#include <stdlib.h>
#include "my.h"

char		*my_strrchr(const char *s, int c)
{
  const char	*pos;

  pos = NULL;
  while (*s)
    if (*s == c)
      pos = s++;
    else
      ++s;
  return ((char *) pos);
}

char		*my_strcpy(char *dest, const char *src)
{
  char		*tmp;

  tmp = dest;
  while ((*tmp++ = *src++));
  return (dest);
}

char		*my_strncpy(char *dest, const char *src, size_t n)
{
  size_t	i;

  i = 0;
  while (i < n && src[i] && (dest[i] = src[i]) && ++i);
  dest[i] = 0;
  return (dest);
}

int		my_strcmp(const char *s1, const char *s2)
{
  while (*s1 && *s1 == *s2 && ++s1 && ++s2);
  return (*s1 - *s2);
}

char		*my_strncat(char *dest, const char *src, size_t n)
{
  char		*tmp;
  size_t	i;

  tmp = dest;
  while (*tmp && ++tmp);
  i = 0;
  while (i < n && (tmp[i] = src[i]) && ++i);
  return (dest);
}
