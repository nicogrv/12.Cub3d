SHELL = /bin/bash

SRCS_MACOS += main.c
SRCS_MACOS += get_next_line_utils.c
SRCS_MACOS += get_next_line.c
SRCS_MACOS += ft_strlen.c
SRCS_MACOS += ft_strdup.c
SRCS_MACOS += ft_substr.c
SRCS_MACOS += ft_isdigit.c
SRCS_MACOS += ft_atoiplus.c
SRCS_MACOS += ft_ray_0_360.c
SRCS_MACOS += ft_init_id_verif_color.c
SRCS_MACOS += ft_init_id.c
SRCS_MACOS += ft_init_id2.c
SRCS_MACOS += ft_map.c
SRCS_MACOS += ft_ray.c
SRCS_MACOS += ft_key.c
SRCS_MACOS += ft_free_macos.c
SRCS_MACOS += ft_draw.c
SRCS_MACOS += ft_verif_map.c
SRCS_MACOS += ft_init.c
SRCS_MACOS += ft_utils.c
SRCS_MACOS += ft_input_macos.c
SRCS_MACOS += ft_color.c

SRCS_LINUX += main.c
SRCS_LINUX += get_next_line_utils.c
SRCS_LINUX += get_next_line.c
SRCS_LINUX += ft_strlen.c
SRCS_LINUX += ft_strdup.c
SRCS_LINUX += ft_substr.c
SRCS_LINUX += ft_isdigit.c
SRCS_LINUX += ft_atoiplus.c
SRCS_LINUX += ft_ray_0_360.c
SRCS_LINUX += ft_init_id_verif_color.c
SRCS_LINUX += ft_init_id.c
SRCS_LINUX += ft_init_id2.c
SRCS_LINUX += ft_map.c
SRCS_LINUX += ft_ray.c
SRCS_LINUX += ft_key.c
SRCS_LINUX += ft_free_linux.c
SRCS_LINUX += ft_draw.c
SRCS_LINUX += ft_verif_map.c
SRCS_LINUX += ft_init.c
SRCS_LINUX += ft_utils.c
SRCS_LINUX += ft_input_linux.c
SRCS_LINUX += ft_color.c

SRC_PATH += ./src/
SRC_PATH += ./src/Get_next_line/
SRC_PATH += ./src/Libft/
SRC_PATH += ./src/Init/
SRC_PATH += ./src/Input/
SRC_PATH += ./src/Map/
SRC_PATH += ./src/Other/
SRC_PATH += ./src/Raycasting/
SRC_PATH += ./src/Draw/

OBJS_PATH_LINUX = ./src/_Objet_L
OBJS_PATH_MACOS = ./src/_Objet_M

HEAD_PATH += -I ./src/_Include






OBJS_LINUX = ${patsubst %.c, ${OBJS_PATH_LINUX}/%.o, ${SRCS_LINUX}}
OBJS_MACOS = ${patsubst %.c, ${OBJS_PATH_MACOS}/%.o, ${SRCS_MACOS}}


NAME = cub3d
CC = cc

CFLAGS = -Wall -Werror -Wextra -g
CFLAGS_LINUX = -Wall -Werror -Wextra -lmlx -lm -lXext -MMD -lX11 -I ./lib/minilibx-linux -L ./lib/minilibx-linux
FLAGSMACOS = -g3 -fsanitize=address -lmlx -framework OpenGL -framework AppKit -MMD -I ./lib/minilibx_macos -L ./lib/minilibx_macos



vpath %.c ${SRC_PATH}
vpath %.h ${HEAD_PATH}

all:
	@	echo make linux / make macos

linux:  ${OBJS_LINUX}
	@	$(MAKE) --no-print-directory -s -C ./lib/minilibx-linux/
	@	${CC}  -o ${NAME} ${OBJS_LINUX} ${HEAD_PATH} ${CFLAGS_LINUX} -D OS=0
	@	echo -ne "\r\033[2K" $(LIGHTGREEN) "\t$(NAME) OK" "\033[0m" "\n"

macos: ${OBJS_MACOS}
	@	$(MAKE) --no-print-directory -s -C ./lib/minilibx_macos/
	@	${CC} -o ${NAME} ${OBJS_MACOS}  ${HEAD_PATH} ${FLAGSMACOS} 
	@	echo -ne "\r\033[2K" $(LIGHTGREEN) "\t$(NAME) OK" "\033[0m" "\n"

run: all
# @	clear
	@	./${NAME}

valgrind: all
	valgrind ./${NAME}


${OBJS_MACOS}: ${OBJS_PATH_MACOS}/%.o: %.c Makefile ./src/_Include/cub3d.h
	@	mkdir -p ${OBJS_PATH_MACOS}
	@	$(COLORCOMPIL)
	@	${CC} -D OS=0 ${CFLAGS} -c $< -o $@ ${HEAD_PATH}


${OBJS_LINUX}: ${OBJS_PATH_LINUX}/%.o: %.c Makefile ./src/_Include/cub3d.h
	@	mkdir -p ${OBJS_PATH_LINUX}
	@	$(COLORCOMPIL)
	@	${CC} -D OS=1 ${CFLAGS} -c $< -o $@ ${HEAD_PATH}


clean:
	@	echo -ne "\r\033[2K" $(YELLOW) "Cleaning\n\n"$(NC)
	@	rm -rf ${OBJS_PATH_LINUX}
	@	rm -rf ${OBJS_PATH_MACOS}


fclean: clean
	@	rm -f ${NAME}
	@	echo -ne "\r\033[2K" $(GREEN) "\t$(NAME) Remove\n"$(NC)"\n"




re: fclean
	@	echo -ne "\r\033[2K" $(YELLOW) "Rebuilding..."$(NC)"\n""\n"
	@	$(MAKE) -s


.PHONY: re clean fclean 

NOCOLOR='\033[0m'
RED='\033[0;31m'
GREEN='\033[0;32m'
ORANGE='\033[0;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
LIGHTGRAY='\033[0;37m'

DARKGRAY='\033[1;30m'
LIGHTRED='\033[1;31m'
LIGHTGREEN='\033[1;32m'
LIGHTBLUE='\033[1;34m'
LIGHTPURPLE='\033[1;35m'
LIGHTCYAN='\033[1;36m'
YELLOW='\033[1;33m'
WHITE='\033[1;37m'


ifndef COLORCOMPIL
COLORCOMPIL = \
	if [ "$(shell test $P -lt 33; echo $$?)" = "0" ]; then \
    	echo -ne "\r\033[2K" $(LIGHTRED) "[$(P)%] "$(DARKGRAY) "Compiling MiniShell" $(WHITE) "$<"; \
	else \
		if [ "$(shell test $P -lt 66; echo $$?)" = "0" ]; then \
    		echo -ne "\r\033[2K" $(YELLOW) "[$(P)%]" $(DARKGRAY) "Compiling MiniShell" $(WHITE) "$<"; \
		else \
       		echo -ne "\r\033[2K" $(LIGHTGREEN) "[$(P)%]" $(DARKGRAY) "Compiling MiniShell" $(WHITE) "$<"; \
		fi \
	fi
T := $(words $(SRCS_MACOS))
N := x
C = $(words $N)$(eval N := x $N)
P = `expr $C '*' 100 / $T / 5`
endif
