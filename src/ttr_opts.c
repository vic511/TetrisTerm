#include <ncurses.h>
#include <term.h>
#include "my.h"
#include "ttr_opts.h"

int			opts_init(t_opts *options)
{
  char			*key;

  if (setupterm(NULL, 1, NULL) == ERR)
    return (0);
  my_memset(options, 0, sizeof(*options));
  options->level = 1;
  if (!(key = tigetstr(OPTS_TERMUP)) || key == (char *) -1)
    return (my_errmsg(0, "Cannot get term's up key"));
  options->keys[TTR_KEYTURN] = key;
  if (!(key = tigetstr(OPTS_TERMLEFT)) || key == (char *) -1)
    return (my_errmsg(0, "Cannot get term's left key"));
  options->keys[TTR_KEYLEFT] = key;
  if (!(key = tigetstr(OPTS_TERMDOWN)) || key == (char *) -1)
    return (my_errmsg(0, "Cannot get term's down key"));
  options->keys[TTR_KEYDROP] = key;
  if (!(key = tigetstr(OPTS_TERMRIGHT)) || key == (char *) -1)
    return (my_errmsg(0, "Cannot get term's right key"));
  options->keys[TTR_KEYRIGHT] = key;
  options->keys[TTR_KEYQUIT] = "q";
  options->keys[TTR_KEYPAUSE] = " ";
  options->mapsize.x = 10;
  options->mapsize.y = 20;
  return (1);
}

int			opts_parse(int argc, char * const *argv,
				   const t_optparam *params)
{
  int			i;
  size_t		iparams;
  const t_optparam	*curr;
  bool			shortmatch;
  bool			ok;

  i = -1;
  while (++i < argc && !(iparams = 0) && !(ok = false))
    {
      while (!ok && (curr = &params[iparams++])->apply && !(shortmatch = 0))
	{
	  if ((ok = (curr->shortname && !my_strcmp(curr->shortname, argv[i]))))
	    shortmatch = true;
	  ok |= (curr->longname && !my_strncmp(curr->longname, argv[i],
					       my_strlen(curr->longname)));
	  if (shortmatch && curr->reqarg && i + 1 >= argc)
	    return (my_errmsg(0, "No arguments given to short option"));
	  else if (ok && !curr->apply(&argv[i], curr))
	    return (0);
	  i += (shortmatch && curr->reqarg);
	}
      if (!ok)
	return (my_errmsg(0, "Unrecognized option"));
    }
  return (1);
}

int			opts_checkconflicts(const t_opts *options)
{
  size_t		index;
  size_t		loop;
  size_t		length;

  index = 0;
  while (index < TTR_KEYSNB)
    {
      length = my_strlen(options->keys[index]);
      loop = 0;
      while (loop < TTR_KEYSNB)
	{
	  if (loop != index &&
	      !my_strncmp(options->keys[index], options->keys[loop], length))
	    return (my_errmsg(0, "Options are conflicting"));
	  ++loop;
	}
      ++index;
    }
  return (1);
}
