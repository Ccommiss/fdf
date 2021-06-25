# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/20 14:10:49 by ccommiss          #+#    #+#              #
#    Updated: 2019/03/16 15:42:35 by ccommiss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_fdf

SRCS = ./sources/main.c \
		./sources/parser.c \
		./sources/handlekey.c \
		./sources/views.c \
		./sources/draw.c \
		./sources/pratic.c \
		./sources/pixelcolor.c \

INCLUDES_MAC = ./includes/
INCLUDES_LINUX = ./includes_linux/

OBJS := ${SRCS:c=o}
CC = clang -g $(FLAGS)
LIBS = ./libft
UNAME := $(shell uname)
APPLE = Darwin

ifeq ($(UNAME),$(APPLE))
	FLAGS = -I. -I$(INCLUDES_MAC) -Wall -Werror -Wextra
endif
ifeq ($(UNAME),Linux)
	FLAGS = -I. -I$(INCLUDES_LINUX) -Wall -Werror -Wextra
endif

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDES)
	make -C $(LIBS)

ifeq ($(UNAME),$(APPLE))
	make -C mlx
	$(CC)  $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -L$(LIBS) -lft  -o $(NAME)
endif
ifeq ($(UNAME),Linux)
	make -C mlx_linux
	$(CC) $(OBJS) -L$(LIBS) -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
endif

clean:
	rm $(OBJS)
	make clean -C ./libft

fclean: clean
	rm $(NAME)

re : fclean all
