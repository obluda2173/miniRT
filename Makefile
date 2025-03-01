# **************************************************************************** #
# CONFIG                                                                       #
# **************************************************************************** #
NAME		=	minirt

# Compiler and flags
CC			=	@cc
RM			=	@rm -fr
CCFLAGS		=	-Wall -Werror -Wextra -Iinclude/mlx
MLXFLAGS	=	-L/usr/X11/lib -lX11 -lXext -Llibs/mlx_linux -lm

# Directories and source files
SRCS_DIR    =   src
PRSR_DIR	=	src/parser
OBJ_DIR		=	obj
SRCS        =   $(wildcard $(SRCS_DIR)/*.c)
OBJS        =   $(patsubst $(SRCS_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

INC			=	-Ilibft -Iget_next_line -Iinc

# Libraries
LIBS		=	libft/libft.a \
				get_next_line/gnl.a \
				minilibx-linux/libmlx.a

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
			@make --no-print-directory -sC minilibx-linux
			$(CC) $(CCFLAGS) $(OBJS) $(INC) $(LIBS) -o $(NAME) $(MLXFLAGS)
			$(SUCCESS)

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CCFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
			$(RM) $(OBJS)
			@make --no-print-directory -sC libft clean
			@make --no-print-directory -sC get_next_line clean
			@make --no-print-directory -sC minilibx-linux clean
			@$(RM) obj
			$(S_OBJS)

fclean:		clean
			$(RM) $(NAME)
			@make --no-print-directory -sC libft fclean
			@make --no-print-directory -sC get_next_line fclean
			@$(RM) minilibx-linux/libmlx.a
			@$(RM) obj
			$(S_NAME)

re:			fclean all

# **************************************************************************** #
# PHONY                                                                        #
# **************************************************************************** #
.PHONY:		all clean fclean re
