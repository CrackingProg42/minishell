SRC	= ft_cut_comma.c \
ft_fork.c\
ft_patchabsolut.c\
ft_strtrim.c\
ft_annexe.c\
ft_cut_egal.c\
ft_free.c\
ft_print.c\
ft_unset.c\
ft_annexe_2.c\
ft_cut_pipe.c\
ft_get_cmd.c\
ft_redirection.c\
ft_variable.c\
ft_annexe_3.c\
ft_echo.c\
ft_get_cmd_2.c\
ft_remove_quote.c\
main.c\
ft_cd.c\
ft_env.c\
ft_get_cmd_3.c\
ft_rm_for_quote.c\
ft_check_pipe_redirection_comma.c\
ft_error_message.c\
ft_get_str.c\
ft_save_rest.c\
ft_child.c\
ft_export.c\
ft_itoa.c\
ft_signal.c\
ft_concordance.c\
ft_export_2.c\
ft_jump_to_cara.c\
ft_splitspecial.c\

SRCS	= $(addprefix ./srcs/,$(SRC))

CFLAGS	= -Wextra -Werror -Wall $(INC)

INC		= -I include

OBJ		= $(SRCS:.c=.o)

CC		= @gcc

NAME	=	minishell


all		: 	$(OBJ)
			@gcc $(FLAG) $(OBJ) $(INC) -o $(NAME)

BONUS	:	all

clean 		:
				@rm -f ${OBJ}

fclean 		:	clean
				@rm -f ${NAME}

re 			:   fclean all

.PHONY		:	all clean fclean re	
