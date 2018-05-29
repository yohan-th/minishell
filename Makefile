# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/05/04 20:51:29 by ythollet     #+#   ##    ##    #+#        #
#    Updated: 2018/05/04 20:53:05 by ythollet    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #


.PHONY: all clean fclean re

CFLAGS = -c -g -Wall -Wextra -Werror

NAME = minishell

DIR_LIB = Libft
DIR_INC = Include
DIR_SRC = Sources
DIR_OBJ = Objects

SRCS =  main.c \
        get_path.c \
        tools.c \
        builtin_cd.c \
        builtin_allenv.c \
        builtin_echo.c \
        strsplit_mnshl.c \
        builtin.c

INCLUDES_FILE = minishell.h

OBJS = $(addprefix $(DIR_OBJ)/,$(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(DIR_LIB)
	@gcc -o $(NAME) $(OBJS) -L $(DIR_LIB) -lft

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c  $(DIR_INC)/$(INCLUDES_FILE)
	@mkdir -p $(DIR_OBJ)
	gcc -o $@ -c $< -I $(DIR_INC) $(CFLAGS)

clean:
	@rm -rf $(DIR_OBJ)
	@make clean -C $(DIR_LIB)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(DIR_LIB)

re: fclean all
