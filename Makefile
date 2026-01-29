SRC_S = src/server.c src/tools.c
SRC_C = src/client.c src/tools.c

OBJ_S = $(SRC_S:.c=.o)
OBJ_C = $(SRC_C:.c=.o)

NAME = server
NAME_C = client

SRC_S_B = bonus/src/server_bonus.c bonus/src/tools_bonus.c
SRC_C_B = bonus/src/client_bonus.c bonus/src/tools_bonus.c

OBJ_S_B = $(SRC_S_B:.c=.o)
OBJ_C_B = $(SRC_C_B:.c=.o)

NAME_B = server_bonus
NAME_C_B = client_bonus

CC = cc -Wall -Wextra -Werror

RM = rm -f

%_bonus.o: %_bonus.c bonus/include/minitalk_bonus.h
	$(CC) -c $< -Ibonus/include -o $@

%.o: %.c include/minitalk.h
	$(CC) -c $< -Iinclude -o $@

all: $(NAME) $(NAME_C)

$(NAME): $(OBJ_S)
	$(CC) $(OBJ_S) -o $(NAME)

$(NAME_C): $(OBJ_C)
	$(CC) $(OBJ_C) -o $(NAME_C)

bonus: $(NAME_B) $(NAME_C_B)

$(NAME_B): $(OBJ_S_B)
	$(CC) $(OBJ_S_B) -o $(NAME_B)

$(NAME_C_B): $(OBJ_C_B)
	$(CC) $(OBJ_C_B) -o $(NAME_C_B)

clean:
	$(RM) $(OBJ_S) $(OBJ_C) $(OBJ_S_B) $(OBJ_C_B)

fclean: clean
	$(RM) $(NAME) $(NAME_C) $(NAME_B) $(NAME_C_B)

re: fclean all