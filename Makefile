NAME	=	tetristerm

RM	=	rm -f

CC	=	gcc

CFLAGS	=	-Wall -Wextra -std=gnu99 -Iinclude

LDFLAGS	=	-lncurses

SRC	=	src/ttr.c				\
		src/ttr_debug.c				\
		src/ttr_game.c				\
		src/ttr_opts.c				\
		src/ttr_optsset.c			\
		src/ttr_minos.c				\
		src/ttr_minosget.c			\
		src/ttr_mecha.c				\
		src/ttr_mechadelay.c			\
		src/ttr_mechakey.c			\
		src/ttr_mechascore.c			\
		src/ttr_parser.c			\
		src/ttr_parsercheck.c			\
		src/ttr_ui.c				\
		src/ttr_uidisplay.c			\
		src/ttr_uicolors.c			\
		src/ttr_uimsg.c				\
		src/ttr_uisound.c			\
		src/my/my_io.c				\
		src/my/my_io2.c				\
		src/my/my_str.c				\
		src/my/my_str2.c			\
		src/my/my_str3.c			\
		src/my/my_strto.c			\
		src/my/my_utils.c			\
		src/my/my_mem.c				\
		src/my_file/my_file.c			\
		src/my_file/my_getline.c		\
		src/my_printf/my_printf.c		\
		src/my_printf/my_printf_internals.c	\
		src/my_printf/my_printf_internals2.c	\
		src/my_printf/my_printf_internals3.c	\
		src/my_printf/my_printf_lengths.c	\
		src/my_printf/my_printf_parser.c

OBJ	=	$(SRC:.c=.o)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

all:		$(NAME)

clean:
	$(RM) $(OBJ)

fclean:		clean
	$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
