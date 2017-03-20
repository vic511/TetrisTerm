long int		my_strtol(const char *nptr, char **endptr, int base)
{
  long int		n;
  int			sign;
  const char		*p;

  p = nptr;
  sign = 1;
  while ((*p == '-' || *p == '+') && (sign *= (*p == '+') - (*p == '-')))
    ++p;
  n = 0;
  while (*p >= '0' && *p <= '9')
    n = n * base + sign * (*p++ - '0');
  if (endptr)
    *endptr = (char *) p;
  return (n);
}

unsigned long int	my_strtoul(const char *nptr, char **endptr, int base)
{
  unsigned long int	n;
  const char		*p;

  p = nptr;
  n = 0;
  while (*p >= '0' && *p <= '9')
    n = n * base + (*p++ - '0');
  if (endptr)
    *endptr = (char *) p;
  return (n);
}
