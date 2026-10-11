SRCS = philo.c ft_atoi.c init.c should_do.c utilise.c
OBJS = $(SRCS:.c=.o)
CC = cc  
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread
NAME = philo

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean : 
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re 