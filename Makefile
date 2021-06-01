SRCS		=	srcs/main.c	\
				srcs/get_input.c	\
				srcs/str_to_tab.c	\
				srcs/utils/ft_isalpha.c	\
				srcs/utils/ft_isascii.c	\
				srcs/utils/ft_isdigit.c	\
				srcs/utils/ft_isalnum.c	\
				srcs/utils/ft_strlen.c	\
				srcs/utils/ft_strlen_spec.c	\
				srcs/utils/ft_strcmp.c	\
				srcs/utils/ft_strncmp.c	\
				srcs/utils/ft_calloc.c	\
				srcs/utils/words.c	\
				srcs/utils/go_to_function.c	\
				srcs/utils/get_env.c	\
				srcs/utils/free_items.c	\
				srcs/utils/get_arg_tab.c	\
				srcs/utils/historic.c	\
				srcs/utils/error.c	\
				srcs/utils/shell.c	\
				srcs/implementations/env.c	\
				srcs/implementations/echo.c	\
				srcs/implementations/export.c

OBJS_SRCS	=	$(SRCS:.c=.o)

.c.o:
				${CC} ${CFLAGS} -c ${INCLUDES} $< -o ${<:.c=.o}

INCLUDES	=	-I./includes/

NAME		=	minishell

CFLAGS      =   -g -fsanitize=address

CC			=	gcc

RM			=	rm -f

${NAME}:		${OBJS_SRCS}
				${CC} -o ${NAME} ${SRCS} ${CFLAGS} ${INCLUDES}

all:			${NAME}

clean:
				find . -type f \( -name "*~" -o -name "#*#" -o -name "*.o" -o -name "*.gch" \) -delete

fclean:			clean
				${RM} ${NAME}

re:				fclean all

mv_objs:		find . -type f -name "*.o" -exec mv -ft objs {} +

.PHONY:			all clean fclean re
