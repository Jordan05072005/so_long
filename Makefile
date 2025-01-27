NAME = so_long
CC = gcc
FLAGS = -Wall -Wextra -Werror
RM = rm -f
FRAMEDIR = ./mlx
FRAMEWORK = -Lmlx -lmlx -Imlx -lXext -lX11 -lm -lz
SRC = src/main.c src/loader_assets.c src/utils.c src/utils_lst.c src/parseur.c src/builder_maps.c \
			src/get_next_line/get_next_line.c src/get_next_line/get_next_line_utils.c \
			src/character_gestion.c src/free.c src/event.c src/collision.c src/utils2.c\
			src/loader_utils.c src/mobs.c \

OBJ = $(SRC:.c=.o)

.c.o: 
	$(CC) $(FLAGS) -Imlx -c $< -o $(<:.c=.o)

$(NAME):	$(OBJ)
	make -C src/libft
	make -C mlx
	$(CC) $(OBJ) $(FRAMEWORK) -no-pie -o $(NAME)  -L src/libft -lft

all: $(NAME)

clean:
	make clean -C mlx
	make clean -C src/libft
	$(RM) $(OBJ)

fclean:	clean
	make fclean -C src/libft
	$(RM) $(NAME) display

re:	fclean all
