SRCS		=	srcs/main.c	\
				srcs/utils/get_input.c	\
				srcs/utils/free_tab.c	\
				srcs/utils/ft_isalnum.c	\
				srcs/utils/ft_isalpha.c	\
				srcs/utils/ft_putstr.c	\
				srcs/utils/ft_strlen.c	\
				srcs/utils/ft_strlen_spec.c	\
				srcs/utils/ft_strcmp.c	\
				srcs/utils/ft_strncmp.c	\
				srcs/utils/ft_calloc.c	\
				srcs/utils/ft_strdup.c	\
				srcs/utils/ft_atoi.c	\
				srcs/utils/ft_putnbr.c	\
				srcs/utils/ft_strdupncpy.c	\
				srcs/utils/words.c	\
				srcs/utils/check_symbol.c	\
				srcs/utils/go_to_function.c	\
				srcs/utils/get_env.c	\
				srcs/utils/free_items.c	\
				srcs/utils/normal_word.c	\
				srcs/utils/get_arg_tab.c	\
				srcs/utils/error.c	\
				srcs/utils/shell.c	\
				srcs/utils/is_charset.c	\
				srcs/utils/quote_checks.c	\
				srcs/utils/get_env_var.c	\
				srcs/utils/open_files.c	\
				srcs/utils/check_functions.c	\
				srcs/utils/pipes.c	\
				srcs/utils/char_env.c	\
				srcs/utils/dup_close_set.c	\
				srcs/utils/ft_setenv.c	\
				srcs/utils/here_doc.c	\
				srcs/utils/get_word.c	\
				srcs/utils/sighandle.c	\
				srcs/utils/check_dollar.c	\
				srcs/utils/ft_itoa.c	\
				srcs/utils/wait_pids.c	\
				srcs/implementations/env.c	\
				srcs/implementations/echo.c	\
				srcs/implementations/ft_exit.c	\
				srcs/implementations/cd.c	\
				srcs/implementations/unset.c	\
				srcs/implementations/pwd.c	\
				srcs/implementations/export.c 

OBJS_SRCS	=	$(SRCS:.c=.o)

.c.o:
				${CC} ${CFLAGS} -c ${INCLUDES} $< -o ${<:.c=.o}

INCLUDES	=	-I./includes/

NAME		=	minishell

CFLAGS      =   -Wall -Werror -Wextra

CC			=	gcc

RM			=	rm -f

${NAME}:		${OBJS_SRCS}
				${CC} -o ${NAME} ${SRCS} ${CFLAGS} ${INCLUDES} -lreadline

all:			${NAME}

clean:
				find . -type f \( -name "*~" -o -name "#*#" -o -name "*.o" -o -name "*.gch" \) -delete

fclean:			clean
				${RM} ${NAME}

re:				fclean all

mv_objs:		find . -type f -name "*.o" -exec mv -ft objs {} +

.PHONY:			all clean fclean re
