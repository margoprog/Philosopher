# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/03 00:22:02 by maheraul          #+#    #+#              #
#    Updated: 2023/05/19 22:41:17 by maheraul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo

SRCS_NAMES			=	main.c \
					parsing.c \
					philo.c \
					action.c \
					utils.c \
					ft_calloc.c

DIR_SRCS		=	srcs

DIR_OBJS		=	objs

HEAD			=	-Iincludes

DEPS			=	${SRCS:.c=.d}

SRCS			=	$(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))

OBJS			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))

OBJS_NAMES		=	${SRCS_NAMES:.c=.o}

CC				=	cc

CDFLAGS 		=	-MMD -MP

CFLAGS			=	-g3 -Wall -Werror -Wextra -pthread

all				:	${NAME}

$(OBJS) : $(DIR_OBJS)/%.o : $(DIR_SRCS)/%.c
	$(CC) $(CFLAGS) $(CDFLAGS) $(HEAD) -c $< -o $@

$(DIR_OBJS):
	mkdir -p objs

$(NAME): $(DIR_OBJS) $(OBJS)
	$(CC) $(CFLAGS) ${HEAD} $(OBJS) -o $(NAME)



clean			:
					rm -rf ${OBJS}

fclean			:	clean
					rm -rf ${NAME}

re				:	fclean all

-include $(DEPS)

.PHONY			:	all clean fclean re bonus
