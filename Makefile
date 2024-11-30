#  |  |  ___ \    \  |         |
#  |  |     ) |  |\/ |   _  |  |  /   _ 
# ___ __|  __/   |   |  (   |    <    __/ 
#    _|  _____| _|  _| \__,_| _|\_\ \___|
#                              by jcluzet
################################################################################
#                                     CONFIG                                   #
################################################################################

NAME        := cube3d
CC        := gcc
FLAGS    := -Wall -Wextra -Werror 
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS        :=      main.c \
                          join_the_fullpath.c \
                          tests_to_knows_if_is_playable.c \
                          init_game.c \
                          libft/ft_isascii.c \
                          libft/ft_strjoin.c \
                          libft/ft_isalpha.c \
                          libft/ft_strtrim.c \
                          libft/ft_strnstr.c \
                          libft/ft_putstr_fd.c \
                          libft/ft_lstlast_bonus.c \
                          libft/ft_putendl_fd.c \
                          libft/ft_strlen.c \
                          libft/ft_isalnum.c \
                          libft/ft_calloc.c \
                          libft/ft_strlcpy.c \
                          libft/ft_memcpy.c \
                          libft/ft_lstadd_back_bonus.c \
                          libft/ft_strdup.c \
                          libft/ft_memset.c \
                          libft/ft_memcmp.c \
                          libft/ft_lstnew_bonus.c \
                          libft/ft_strchr.c \
                          libft/ft_lstiter_bonus.c \
                          libft/ft_substr.c \
                          libft/ft_memmove.c \
                          libft/ft_lstadd_front_bonus.c \
                          libft/ft_striteri.c \
                          libft/ft_lstclear_bonus.c \
                          libft/ft_lstmap_bonus.c \
                          libft/ft_tolower.c \
                          libft/ft_itoa.c \
                          libft/ft_isdigit.c \
                          libft/ft_strncmp.c \
                          libft/ft_putnbr_fd.c \
                          libft/ft_putchar_fd.c \
                          libft/ft_strrchr.c \
                          libft/ft_strlcat.c \
                          libft/ft_strmapi.c \
                          libft/ft_bzero.c \
                          libft/ft_atoi.c \
                          libft/ft_lstsize_bonus.c \
                          libft/ft_toupper.c \
                          libft/ft_memchr.c \
                          libft/ft_lstdelone_bonus.c \
                          libft/ft_isprint.c \
                          libft/ft_split.c \
                          read_the_map.c \
                          MLX42/build/CMakeFiles/3.22.1/CompilerIdC/CMakeCCompilerId.c \
                          MLX42/build/CMakeFiles/3.22.1/CompilerIdCXX/CMakeCXXCompilerId.cpp \
                          MLX42/build/mlx_frag_shader.c \
                          MLX42/build/mlx_vert_shader.c \
                          MLX42/lib/glad/glad.c \
                          MLX42/lib/png/lodepng.c \
                          MLX42/src/textures/mlx_png.c \
                          MLX42/src/textures/mlx_texture.c \
                          MLX42/src/textures/mlx_xpm42.c \
                          MLX42/src/mlx_exit.c \
                          MLX42/src/mlx_mouse.c \
                          MLX42/src/mlx_cursor.c \
                          MLX42/src/mlx_put_pixel.c \
                          MLX42/src/mlx_window.c \
                          MLX42/src/mlx_init.c \
                          MLX42/src/mlx_monitor.c \
                          MLX42/src/utils/mlx_list.c \
                          MLX42/src/utils/mlx_utils.c \
                          MLX42/src/utils/mlx_error.c \
                          MLX42/src/utils/mlx_compare.c \
                          MLX42/src/mlx_keys.c \
                          MLX42/src/font/mlx_font.c \
                          MLX42/src/mlx_loop.c \
                          MLX42/src/mlx_images.c \
                          MLX42/tests/tests.cpp \
                          ray.c \
                          print_3d.c \
                          moves.c \
                          test_to_knows_if_is_playable3.c \
                          init_game2.c \
                          distance.c \
                          moves2.c \
                          ft_printf/utils.c \
                          ft_printf/libftprintf.c \
                          ft_printf/utils1.c \
                          test_to_knows_if_is_playable2.c \
                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

################################################################################
#                                  Makefile  objs                              #
################################################################################


CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

UNAME		:=	$(shell uname)

ifeq ($(UNAME), Darwin)
$(NAME): ${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			@ $(MAKE) -C mlx all >/dev/null 2>&1
			@ cp ./mlx/libmlx.a .
			$(CC) $(CFLAGS) -g3 -Ofast -o $(NAME) -Imlx $(OBJS) -Lmlx -lmlx -lm -framework OpenGL -framework AppKit
			@echo "$(GREEN)$(NAME) created[0m ✔️"
endif

ifeq ($(UNAME), Linux)
$(NAME): ${OBJS}
			@echo "$(GREEN)Linux compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			@chmod 777 mlx_linux/configure
			@ $(MAKE) -C mlx_linux all
			$(CC) $(CFLAGS) -g3 -o $(NAME) $(OBJS) -Imlx_linux -Lmlx_linux -lmlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm
			@echo "$(GREEN)$(NAME) created[0m ✔️"
endif

all:		${NAME}

ifeq ($(UNAME), Darwin)
clean:
			@ ${RM} *.o */*.o */*/*.o
			@ rm -rf $(NAME).dSYM >/dev/null 2>&1
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"
endif

ifeq ($(UNAME), Linux)
clean:
			@ ${RM} *.o */*.o */*/*.o
			@ rm -rf $(NAME).dSYM >/dev/null 2>&1
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"
endif


ifeq ($(UNAME), Linux)
fclean:		clean
			@ ${RM} ${NAME}
			@ $(MAKE) -C mlx_linux clean 
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"
endif

ifeq ($(UNAME), Darwin)
fclean:		clean
			@ ${RM} ${NAME}
			@ rm libmlx.a
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"
endif

re:			fclean all

.PHONY:		all clean fclean re


