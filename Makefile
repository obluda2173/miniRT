# **************************************************************************** #
# CONFIG                                                                       #
# **************************************************************************** #
NAME		=	minirt

# Compiler and flags
CC			=	@cc
RM			=	@rm -fr
CCFLAGS		=	-Wall -Werror -Wextra
MLXFLAGS	=	-L/usr/X11/lib -lX11 -lXext -lmlx -lm

# Directories and source files
SRCS_DIR    =   src
PRSR_DIR	=	src/parser
OBJ_DIR		=	obj
SRCS        =   src/_main.c src/graphics.c src/light_and_color_1.c src/light_and_color_2.c \
				src/math_operations_1.c src/math_operations_2.c src/math_operations_3.c \
				src/parsing.c src/parsing_extracting_objects.c src/parsing_robust_check_1.c \
				src/parsing_robust_check_2.c src/parsing_robust_check_3.c \
				src/parsing_structures_1.c src/parsing_structures_2.c \
				src/ray_cone_intersection.c src/ray_cylinder_intersect_1.c \
				src/ray_cylinder_intersect.c src/ray_object_intersect.c src/ray_object_intersect_1.c \
				src/raytracing.c src/textures.c src/utils.c
OBJS        =   $(patsubst $(SRCS_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

INC			=	-Ilibft -Iget_next_line -Iinc -Iminilibx-linux

# Libraries
LIBS		=	libft/libft.a \
				get_next_line/gnl.a

# **************************************************************************** #
# COLOURS                                                                      #
# **************************************************************************** #
BLUE		=	\033[0;94m
RED			=	\033[0;91m
GREEN		=	\033[0;92m
YELLOW		=	\033[0;33m
CYAN		=	\033[0;96m
COLOR		=	\033[0m

# Messages
SUCCESS		=	@echo "$(GREEN)miniRT compiled successfully$(COLOR)"
S_OBJS		=	@echo "$(BLUE)cleaning of objects completed$(COLOR)"
S_NAME		=	@echo "$(CYAN)full clean completed$(COLOR)"

# **************************************************************************** #
# RULES                                                                        #
# **************************************************************************** #
all:		$(NAME)

$(NAME):	$(OBJS)
			@make bonus -sC libft
			@make -sC get_next_line
			$(CC) $(CCFLAGS) $(OBJS) $(INC) $(LIBS) -o $(NAME) $(MLXFLAGS)
			$(SUCCESS)

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CCFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
			$(RM) $(OBJS)
			@make --no-print-directory -sC libft clean
			@make --no-print-directory -sC get_next_line clean
			@$(RM) obj
			$(S_OBJS)

fclean:		clean
			$(RM) $(NAME)
			@make --no-print-directory -sC libft fclean
			@make --no-print-directory -sC get_next_line fclean
			@$(RM) obj
			@rm -rf build
			$(S_NAME)

re:			fclean all

# **************************************************************************** #
# PHONY                                                                        #
# **************************************************************************** #
.PHONY:		all clean fclean re
