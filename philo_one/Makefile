# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/20 22:01:49 by mcaptain          #+#    #+#              #
#    Updated: 2021/01/23 16:20:41 by mcaptain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS			= ft_atoi.c get_time.c init.c live.c monitor.c print.c main.c
OBJS			= $(SRCS:.c=.o)

CC				= gcc 
RM				= rm -f
CFLAGS			= -I.
LIBS			= -lpthread

NAME			= philo_one

all:			$(NAME)

$(NAME):		$(OBJS)
				gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}

clean:
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
