# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/03 18:59:35 by jeza              #+#    #+#              #
#    Updated: 2024/03/08 17:09:13 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'executable
NAME = pipex
NAMEB = pipex_bonus

# Compilateur
CC := gcc

# Options de compilation
CFLAGS := -Wall -Wextra -Werror -Iheaders/ -g

#Liste des fichiers source.
SRCS = pipex.c utils.c handle_path.c process.c \
		exec.c

BONUS = pipex_bonus.c handle_cmd_bonus.c utils_bonus.c \
		handle_path_bonus process_bonus.c 
GETNEXTLINE = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
LIBFT = Libft/libft.a
PRINTF = printf/libftprintf.a

OBJS = $(SRCS:.c=.o)
OBJSBONUS = $(BONUS:.c=.o)
GETNEXTLINE_OBJ := $(GETNEXTLINE:.c=.o)

# Regle par defaut pour l'executable
all: author project $(NAME)
bonus: author project $(NAMEB)

# Regles pour afficher l'auteur et le projet.
author:
	@echo "Author : jeguerin\n"
project:
	@echo "Project : Pipex\n"

$(LIBFT):
	make -C Libft

$(PRINTF):
	make -C printf

# Regle pour creer l'executable en liant les objets.
$(NAME): $(OBJS) $(LIBFT) $(PRINTF) $(GETNEXTLINE_OBJ)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) $(GETNEXTLINE_OBJ) -o $(NAME)

$(NAMEB): $(OBJSBONUS) $(LIBFT) $(PRINTF) $(GETNEXTLINE_OBJ)
	$(CC) $(CFLAGS) $(OBJSBONUS) $(LIBFT) $(PRINTF) $(GETNEXTLINE_OBJ) -o $(NAMEB)

# Regle pour nettoyer les fichiers objets.
clean:
	$(RM) $(OBJS) $(OBJSBONUS)
	$(RM) $(GETNEXTLINE_OBJ)
	make clean -C Libft
	make clean -C printf

# Regle pour nettoyer les fichiers objets et l'executable.
fclean: clean
	$(RM) $(NAME) $(NAMEB)
	make fclean -C Libft
	make fclean -C printf

# Regle pour reconstruire le projet (clean, puis all)
re: author fclean all

# Declarer les regles comme des cibles .phony pour eviter des conflits avec
# des fichiers du meme nom.
.PHONY: all clean fclean re bonus
