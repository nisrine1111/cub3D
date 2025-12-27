NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

MLX = -lmlx -lX11 -lXext -lm

SRC =  srcs/main.c  	 \
	   srcs/map/map.c    	 \
	   srcs/map/map_utils.c	 \
	   srcs/map/player.c 	 \
	   srcs/mouvement/mouvement.c  \
	   srcs/mouvement/mouvement_utils.c \
	   srcs/raycasting/raycast_hor.c \
	   srcs/raycasting/raycast_ver.c \
	   srcs/raycasting/cast_single.c\
	   srcs/raycasting/cast_all.c	 \
	   srcs/rendering/render.c     \
	   srcs/rendering/texture_tool.c \
	   srcs/map/minimap.c     \
	   srcs/rendering/render_sprites.c

PARSING_SRC = srcs/parsing/colors.c \
			  srcs/parsing/door.c \
			  srcs/parsing/map.c \
			  srcs/parsing/map_validation.c \
			  srcs/parsing/texture.c \
			  srcs/parsing/helpers.c \
			  srcs/parsing/parse_file.c

GNL_SRC = helpers/get_next_line/get_next_line.c \
		  helpers/get_next_line/get_next_line_utils.c

GC_SRC = helpers/GarbageCollector/malloc.c \
		 helpers/GarbageCollector/malloc_utils.c \
		 helpers/GarbageCollector/gc_trim.c \
		 helpers/GarbageCollector/gc_split.c

LIBFT_SRC = helpers/libft/ft_atoi.c helpers/libft/ft_bzero.c helpers/libft/ft_calloc.c \
			helpers/libft/ft_isalnum.c helpers/libft/ft_isalpha.c helpers/libft/ft_isascii.c \
			helpers/libft/ft_isdigit.c helpers/libft/ft_isprint.c helpers/libft/ft_itoa.c \
			helpers/libft/ft_memchr.c helpers/libft/ft_memcmp.c helpers/libft/ft_memcpy.c \
			helpers/libft/ft_memmove.c helpers/libft/ft_memset.c helpers/libft/ft_putchar_fd.c \
			helpers/libft/ft_putendl_fd.c helpers/libft/ft_putnbr_fd.c helpers/libft/ft_putstr_fd.c \
			helpers/libft/ft_split.c helpers/libft/ft_strchr.c helpers/libft/ft_strdup.c \
			helpers/libft/ft_striteri.c helpers/libft/ft_strjoin.c helpers/libft/ft_strlcat.c \
			helpers/libft/ft_strlcpy.c helpers/libft/ft_strlen.c helpers/libft/ft_strmapi.c \
			helpers/libft/ft_strncmp.c helpers/libft/ft_strnstr.c helpers/libft/ft_strrchr.c \
			helpers/libft/ft_strtrim.c helpers/libft/ft_substr.c helpers/libft/ft_tolower.c \
			helpers/libft/ft_toupper.c

ALL_SRC = $(SRC) $(PARSING_SRC) $(GNL_SRC) $(GC_SRC) $(LIBFT_SRC)

OBJ = $(ALL_SRC:.c=.o)

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
