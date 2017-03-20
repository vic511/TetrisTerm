#ifndef MY_H_
# define MY_H_

# include "my_printf.h"
# include "my_file.h"

# define MY_STRLEN(S)	(sizeof(S) - 1)
# define MY_PUTSTR(S)	(write(1, (S), MY_STRLEN(S)))
# define MAX(N1, N2)	((N1) > (N2) ? (N1) : (N2))

size_t			my_strlen(const char *);
int			my_strcmp(const char *, const char *);
int			my_strncmp(const char *, const char *, size_t);
char			*my_strlshift(char *, size_t);
char			*my_strrtrim(char *, char);
char			*my_strcpy(char *, const char *);
char			*my_strncpy(char *, const char *, size_t);
char			*my_strchr(const char *, int);
char			*my_strrchr(const char *, int);
char			*my_strcat(char *, const char *);
char			*my_strncat(char *, const char *, size_t);
int			my_putchar(char);
int			my_putstr(const char *);
int			my_showstr_octal(const char *);
int			my_putnbr_u(unsigned int);
int			my_putnbr_bitwise(unsigned long, int, const char *);
int			my_str_repeat(char, int);
int			my_errmsg(int, const char *);
int			my_getnbr(const char *);
long int		my_strtol(const char *, char **, int);
unsigned long int	my_strtoul(const char *, char **, int);
void			*my_memset(void *, int, size_t);
void			*my_memcpy(void *, const void *, size_t);
int			xfree(void *);

#endif /* !MY_H_ */
