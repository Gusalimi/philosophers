NAME	= philo
SRCS	=	main.c \
			ft_atoi.c \
			ft_putstr_fd.c \
			init.c \
			utils.c
OBJS	= $(SRCS:.c=.o)
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g3
RM		= rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -pthread -o $(NAME)

debug: fclean $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -pthread -fsanitize=address -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re debug