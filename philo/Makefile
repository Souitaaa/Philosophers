NAME			= philo

SRCS			= time.c notmain.c philo.c ft_atoi.c ft_putstr.c ft_strlen.c init.c ft_memset.c \

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror
OBJS			= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)


clean:
	$(RM) $(OBJS) 

fclean:clean 
	$(RM) $(NAME) 

re: fclean all 
.SECONDARY : 