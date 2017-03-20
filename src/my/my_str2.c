#include "my.h"

size_t		my_strlen(const char *s)
{
  size_t	len;

  len = 0;
  while (s[len] && ++len);
  return (len);
}

int		my_strncmp(const char *s1, const char *s2, size_t n)
{
  while (n-- > 0 && *s1 && *s1 == *s2)
    {
      if (!n)
	return (*s1 - *s2);
      ++s1;
      ++s2;
    }
  return (*s1 - *s2);
}

char		*my_strlshift(char *s, size_t shift)
{
  char		*p;
  size_t	len;

  len = 0;
  while (s[len] && ++len);
  if (len < shift)
    {
      *s = 0;
      return (s);
    }
  p = s;
  while (p[shift] && (*p = p[shift]) && ++p);
  *p = 0;
  return (s);
}

char		*my_strchr(const char *s, int c)
{
  const char	*pos;

  pos = s;
  while (*pos)
    if (*pos == c)
      return ((char *) pos);
    else
      ++pos;
  return (NULL);
}

char		*my_strrtrim(char *s, char c)
{
  size_t	len;

  len = 0;
  while (s[len] && ++len);
  while (len > 0 && s[len - 1] == c)
    s[--len] = 0;
  return (s);
}
