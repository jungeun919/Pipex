# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jungchoi <jungchoi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/01 16:13:26 by jungchoi          #+#    #+#              #
#    Updated: 2022/11/10 17:34:51 by jungchoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

INCLUDES_DIR = includes
LIBS_DIR = libs
SRCS_DIR = srcs
OBJS_DIR = objs

LIBFT_DIR = libs/libft
LIBFT = libft.a

SRCS = $(addprefix $(SRCS_DIR)/, \
	pipex.c \
	execute.c)

OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))


SRCS_BONUS = $(addprefix $(SRCS_DIR)/, \
	pipex_bonus.c \
	execute_bonus.c \
	get_next_line.c)

OBJS_BONUS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS_BONUS:.c=.o)))

ifdef WITH_BONUS
	OBJ_FILES = $(OBJS_BONUS)
else
	OBJ_FILES = $(OBJS)
endif

all : $(NAME)

bonus :
	make WITH_BONUS=1 all

$(NAME) : $(OBJ_FILES)
	make -C $(LIBFT_DIR) all
	$(CC) $(CFLAGS) $(OBJ_FILES) -I $(INCLUDES_DIR) -L $(LIBFT_DIR) -lft -o $@

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c
	@mkdir $(OBJS_DIR) 2> /dev/null || true
	$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -I $(LIBFT_DIR) -c $< -o $@

clean :
	rm -rf $(OBJS_DIR)
	make -C $(LIBFT_DIR) clean

fclean : clean
	rm -rf $(NAME)
	make -C $(LIBFT_DIR) fclean

re :
	make fclean
	make all

.PHONY = all bonus clean fclean re
