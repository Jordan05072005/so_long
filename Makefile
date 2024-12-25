NAME = so_long
CC = gcc
FLAGS = -Wall -Wextra -Werror -g
RM = rm -f
FRAMEDIR = ./mlx
FRAMEWORK = -Lmlx -lmlx -Imlx -lXext -lX11 -lm -lz
SRC = src/main.c src/loader_assets.c src/utils.c src/utils_lst.c src/parseur.c src/builder_maps.c \
			src/get_next_line/get_next_line.c src/get_next_line/get_next_line_utils.c \
			src/player_gestion.c src/free.c\

OBJ = $(SRC:.c=.o)

.c.o: 
	$(CC)  -Imlx -c $< -o $(<:.c=.o)

$(NAME):	$(OBJ)
	make -C src/libft
	$(CC) $(OBJ) $(FRAMEWORK) -o display  -L src/libft -lft

all: $(NAME)

clean:
	make clean -C src/libft
	$(RM) $(OBJ)

fclean:	clean
	make fclean -C src/libft
	$(RM) $(NAME) display

re:	fclean all