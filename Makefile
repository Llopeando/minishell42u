# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 13:14:43 by ullorent          #+#    #+#              #
#    Updated: 2022/06/13 11:45:14 by ullorent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CSRC =	src/minishell.c		\
		src/ms_pass.c		\
		src/ms_input.c		\
		src/ms_expand.c		\
		src/ms_free.c		\
		src/ms_allocate.c	\
		src/ms_input_cases.c\
		src/ms_utils.c		\
		src/ms_utils2.c		\
		src/ms_builtins.c	\
		src/ms_pipes.c		\
		src/ms_process.c	\
		src/ms_error.c		\
		src/ms_checker.c	\
		src/ms_checker2.c	\
		src/ms_export.c		\
		src/ms_unset.c		\
		src/ms_infile.c		\
		src/ms_command.c	\
		src/ms_dollar.c		\
		src/ms_cd.c			\
		src/ms_bridge.c

OSRC = $(CSRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra #-g3 -fsanitize=address
LDFLAGS = -lreadline -L/Users/$(USER)/.brew/opt/readline/lib/
CPPFLAGS= -I/Users/$(USER)/.brew/opt/readline/include
GCCCMD = gcc

LIBFT = libft/libft.all

all: $(NAME)

%.o: %.c
	@$(GCCCMD) $(CFLAGS) $(CPPFLAGS) -c $^ -o $@

$(NAME): $(OSRC)
	@echo "\033[33mCompiling libft...\033[0m"
	@make -C libft
	@make -C libft/ bonus
	@mv libft/libft.a .
	@echo "\033[33mCompiling minishell project...\033[0m"
	@$(GCCCMD) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) libft.a $^ -o $(NAME)
	@echo "\033[92mminishell has been successfully compiled!\033[0m"

clean:
	@rm -f $(OSRC)
	@rm -f libft.a
	@make -C libft/ clean

fclean: clean
	@rm -f $(NAME)
	@make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re