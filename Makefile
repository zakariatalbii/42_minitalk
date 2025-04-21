HDR = minitalk.h

SSRC = server.c tools.c
CSRC = client.c tools.c

SOBJ =	$(SSRC:.c=.o)
COBJ =	$(CSRC:.c=.o)

NAME =	server
CNAME =	client

HDR_B = minitalk_bonus.h

SSRC_B = server_bonus.c tools_bonus.c
CSRC_B = client_bonus.c tools_bonus.c

SOBJ_B = $(SSRC_B:.c=.o)
COBJ_B = $(CSRC_B:.c=.o)

NAME_B =	server_bonus
CNAME_B =	client_bonus

CC =	cc -Wall -Wextra -Werror
RM =	rm -f

%.o: %.c $(HDR)
	$(CC) -c $< -o $@

%_bonus.o: %_bonus.c $(HDR_B)
	$(CC) -c $< -o $@

all: $(NAME) $(CNAME)

bonus: $(NAME_B) $(CNAME_B)

$(NAME): $(SOBJ)
	$(CC) $(SOBJ) -o $(NAME)

$(CNAME): $(COBJ)
	$(CC) $(COBJ) -o $(CNAME)

$(NAME_B): $(SOBJ_B)
	$(CC) $(SOBJ_B) -o $(NAME_B)

$(CNAME_B): $(COBJ_B)
	$(CC) $(COBJ_B) -o $(CNAME_B)

clean:
	$(RM) $(SOBJ) $(COBJ) $(SOBJ_B) $(COBJ_B)

fclean: clean
	$(RM) $(NAME) $(CNAME) $(NAME_B) $(CNAME_B)

re: fclean all
