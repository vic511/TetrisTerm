#include "my.h"

int		my_getnbr(const char *s)
{
  int		sign;
  int		n;

  sign = 1;
  while ((*s == '-' || *s == '+') && (sign *= (*s == '+') - (*s == '-')))
    ++s;
  n = 0;
  while (*s >= '0' && *s <= '9')
    n += n * 10 + sign * (*s++ - '0');
  return (n);
}

int		my_getnbr_base(const char *s, const char *base)
{
  int		sign;
  int		n;
  char		*pos;
  size_t	pow;

  pow = my_strlen(base);
  sign = 1;
  while ((*s == '-' || *s == '+') && (sign *= (*s == '+') - (*s == '-')))
    ++s;
  n = 0;
  while ((pos = my_strrchr(base, *s)))
    n += n * pow + sign * (pos - s++);
  return (n);
}

int		xfree(void *addr)
{
  free(addr);
  return (1);
}
