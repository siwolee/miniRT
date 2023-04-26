NAME = libft.a

SRCS = \
		srcs/ft_atoi.c srcs/ft_bzero.c srcs/ft_calloc.c srcs/ft_isalnum.c srcs/ft_isalpha.c \
		srcs/ft_isascii.c srcs/ft_isdigit.c srcs/ft_isprint.c srcs/ft_itoa.c srcs/ft_lstadd_back.c \
		srcs/ft_lstadd_front.c srcs/ft_lstclear.c srcs/ft_lstdelone.c srcs/ft_lstiter.c srcs/ft_lstlast.c \
		srcs/ft_lstmap.c srcs/ft_lstnew.c srcs/ft_lstsize.c srcs/ft_memchr.c srcs/ft_memcmp.c srcs/ft_memcpy.c \
		srcs/ft_memset.c srcs/ft_putchar_fd.c srcs/ft_putendl_fd.c srcs/ft_putnbr_fd.c \
		srcs/ft_putstr_fd.c srcs/ft_split.c srcs/ft_strchr.c srcs/ft_strdup.c srcs/ft_striteri.c \
		srcs/ft_strjoin.c srcs/ft_strlcat.c srcs/ft_strlcpy.c srcs/ft_strlen.c srcs/ft_strmapi.c \
		srcs/ft_strncmp.c srcs/ft_strnstr.c srcs/ft_strrchr.c srcs/ft_strtrim.c srcs/ft_substr.c \
		srcs/ft_tolower.c srcs/ft_toupper.c srcs/get_next_line_utils.c srcs/get_next_line.c \
		srcs/ft_split_replace.c

OBJS = $(SRCS:.c=.o)

INC = ./include

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3

AR = ar
ARFLAGS = crs

.PHONY : all clean fclean re bonus

all : $(NAME)

$(NAME) : $(OBJS)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	@printf "libft library compiled\n"
	@rm -f $(B_OBJS) $(OBJS)

%.o : %.c
	@$(CC) $(CFLAGS) -I$(INC) -c $^ -o $@

clean :
	@rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all