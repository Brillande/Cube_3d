#  |  |  ___ \    \  |         |
#  |  |     ) |  |\/ |   _  |  |  /   _ 
# ___ __|  __/   |   |  (   |    <    __/ 
#    _|  _____| _|  _| \__,_| _|\_\ \___|
#                              by jcluzet
################################################################################
#                                     CONFIG                                   #
################################################################################

NAME        := cub3D
CC        := gcc
FLAGS    := -Wall -Wextra -Werror -g3
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS        :=      main.c \
                          map_is_playable.c \
                          init_game.c \
                         read_the_map.c \
                          print_3d.c \
                          moves.c \
                          exit_game.c \
                          distance.c \
                          moves2.c \
													get_visuals.c \
                          ray.c \
													boundary_test.c \
													file_helpers.c \
													maths.c \
							moves3.c	\
							maths2.c	\
							map_is_playable2.c

OBJS        := $(SRCS:.c=.o)

%.o: %.c
	${CC} ${FLAGS} $(HEADERS) -c $< -o ${<:.c=.o}

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
# Change this if we are using the original MLX
MLXDIR	= MLX42
MLXLIBS	= -L $(MLXDIR) -lmlx42 -ldl -lglfw -pthread -lm
LIBMLX	= $(MLXDIR)/libmlx42.a

FTDIR	= ./libft
FTLIB	= -L $(FTDIR) -lft
LIBFT = $(FTDIR)/libft.a

HEADERS	= -I $(MLXDIR) -I $(FTDIR)
LIBS	= $(FTLIB) $(MLXLIBS)

all:	$(NAME)

$(LIBFT):
	@echo "making libft"
	make -C $(FTDIR)

# NOTE Specify source and build location, else we overwrite our own Makefile!
$(LIBMLX):
	@echo "making MLX42"
	cmake -S $(MLXDIR) -B $(MLXDIR)
	make -C $(MLXDIR)

ifeq ($(UNAME), Linux)
$(NAME): ${OBJS} $(LIBFT) $(LIBMLX)
			@echo "$(GREEN)Linux compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			$(CC) $(OBJS) $(HEADERS) $(FTLIB) $(MLXLIBS) -o $(NAME)
			@echo "$(GREEN)$(NAME) created[0m ✔️"
endif

ifeq ($(UNAME), Linux)
clean:
			@ ${RM} *.o */*.o */*/*.o
			@ rm -rf $(NAME).dSYM >/dev/null 2>&1
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"
			@ ${RM} ${NAME}
			-@ $(MAKE) -C $(MLXDIR) clean
			-@ make -C $(FTDIR) fclean
endif

re:			fclean all

.PHONY:		all clean fclean re
