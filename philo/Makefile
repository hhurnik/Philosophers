CC      = cc
CFLAGS  = -Wall -Wextra -Werror -pthread -g

NAME    = philo

SRC     = monitor_death.c monitor_simulation.c init_mutexes.c main.c parsing.c philo_thread_init.c philo_thread_utils.c routine.c sim_init_clean.c time.c
OBJ     = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re