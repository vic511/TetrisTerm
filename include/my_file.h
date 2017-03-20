#ifndef MY_FILE_H_
# define MY_FILE_H_

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define READ_SIZE	0x2000

typedef struct	s_file
{
  char		*save;
  int		savelen;
  int		fd;
}		t_file;

t_file	*my_fopen(const char *);
t_file	*my_fdopen(const int);
char	*my_getline(t_file *);
int	my_fclose(t_file *);

#endif /* !MY_FILE_H_ */
