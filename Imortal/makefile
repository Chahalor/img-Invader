# big Header

NAME = imortal

SRC =	hide_imortal.c
#thread_imortal.c #\
		debug.c

DIROBJ = .obj

OBJ = $(addprefix $(DIROBJ)/, $(SRC:.c=.o))

CC = gcc
CFLAGS = -g3 -I./
LDFLAGS = -lX11 #-lSDL2

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

$(DIROBJ)/%.o: %.c
	@mkdir -p $(DIROBJ)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(DIROBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

debug:
	$(eval CFLAGS=$(CFLAGS) -g3 -fsanitize=address -D DEBUG=1)

.PHONY: all clean fclean re debug