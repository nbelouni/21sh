
NAME = libft.a

SRC = ft_memset.c	\
	  ft_bzero.c	\
	  ft_memcpy.c	\
	  ft_memccpy.c	\
	  ft_memmove.c	\
	  ft_memchr.c	\
	  ft_memcmp.c	\
	  ft_strlen.c	\
	  ft_strdup.c	\
	  ft_strcpy.c	\
	  ft_strncpy.c	\
	  ft_strcat.c	\
	  ft_strncat.c	\
	  ft_strlcat.c	\
	  ft_strchr.c	\
	  ft_strrchr.c	\
	  ft_strchr_post.c\
	  ft_strchr_prev.c\
	  ft_strstr.c	\
	  ft_strnstr.c	\
	  ft_strcmp.c	\
	  ft_strncmp.c	\
	  ft_atoi.c		\
	  ft_atoi_base16.c	\
	  ft_isalpha.c	\
	  ft_isdigit.c	\
	  ft_isalnum.c	\
	  ft_isascii.c	\
	  ft_isprint.c	\
	  ft_toupper.c	\
	  ft_tolower.c	\
	  ft_memalloc.c	\
	  ft_memdel.c	\
	  ft_strnew.c	\
	  ft_strdel.c	\
	  ft_strclr.c	\
	  ft_striter.c	\
	  ft_striteri.c	\
	  ft_strmap.c	\
	  ft_strmapi.c	\
	  ft_strequ.c	\
	  ft_strnequ.c	\
	  ft_strsub.c	\
	  ft_strjoin.c	\
	  ft_strtrim.c	\
	  ft_strtrimc.c	\
	  ft_strsplit.c	\
	  ft_itoa.c		\
	  is_num.c		\
	  ft_putchar.c	\
	  ft_putstr.c	\
	  ft_putendl.c	\
	  ft_putendsp.c	\
	  ft_putnbr.c	\
	  ft_putchar_fd.c	\
	  ft_putstr_fd.c	\
	  ft_putendl_fd.c	\
	  ft_putnbr_fd.c	\
	  ft_lstnew.c		\
	  ft_lstdelone.c	\
	  ft_lstdel.c		\
	  ft_lstadd.c		\
	  ft_lstiter.c		\
	  ft_lstmap.c		\
	  ft_lstclear.c		\
	  ft_lstpushback.c	\
	  get_next_line.c	\
	  ft_print_error.c	\
	  ft_free_and_join.c\
	  ft_strlchr.c		\
	  ft_multi_concat.c	\
	  ft_multi_free.c	\
	  ft_is_valid_dir.c	\
	  ft_tablen.c		\
	ft_epurstr.c	\
	ft_free_and_dup.c	\
	ft_get_index_of.c	\
	ft_getopt.c	\
	ft_intlen.c	\
	ft_multi_join.c	\
	ft_putnchar.c	\
	ft_puttab.c	\
	ft_strcut.c	\
	ft_strisdigit.c	\
	ft_strreplace.c	\
	ft_tabconcat.c	\
	ft_tabdel.c

FILEO = $(SRC:.c=.o)

HEADER = libft.h

WWW = -Wall -Werror -Wextra

$(NAME):
	gcc $(WWW) -c $(SRC) -I ./inc
	ar rc $(NAME) $(FILEO)
	ranlib $(NAME)

all: $(NAME)

clean:
	/bin/rm -f $(FILEO)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all 
