NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX = -lmlx -lX11 -lXext -lm

SRC =  srcs/main.c  	 \
	   srcs/map.c    	 \
	   srcs/player.c 	 \
	   srcs/mouvement.c  \
	   srcs/raycasting.c \
	   srcs/cast_single.c\
	   srcs/cast_all.c	 \
	   srcs/render.c     \
	   srcs/texture_tool.c \
	   srcs/minimap.c     \

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJ)
