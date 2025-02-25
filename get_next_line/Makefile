SRCS		= 	get_next_line.c get_next_line_utils.c
OBJS		= 	$(SRCS:.c=.o)

CC			= 	cc
RM			= 	@rm -rf
CCFLAGS		= 	-Wall -Werror -Wextra -I.

NAME		= 	gnl.a

%.o:			%.c
				@$(CC) $(CCFLAGS) -c $< -o $@

all:			$(NAME)
				
$(NAME):		$(OBJS)
				@ar rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re