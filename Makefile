# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/03 14:46:08 by shinfray          #+#    #+#              #
#    Updated: 2023/08/12 12:31:08 by shinfray         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


################################################################################
#                                 CONFIG                                       #
################################################################################

.DELETE_ON_ERROR:
.SILENT:

NAME:=	minishell

SRCS_DIR:= src
BUILD_DIR:= build
INC_DIRS= include

LDLIBS:= -lreadline
LIB_DIRS=

CC:=	clang

CFLAGS=	-Wall -Wextra -Werror

CFLAGS+=	-std=c17 \
			-O3 \
			-Wconversion \
			-Wdouble-promotion \
			-Wfloat-equal \
			-Wformat=2 \
			-Winit-self \
			-fno-common \
			-Wshadow \
			-Wundef \
			-Wunused-macros \
			-Wwrite-strings \
			-Wmissing-prototypes \
			-Wmissing-declarations
#			-Wpedantic \
#			-pedantic-errors \
#			-Wcast-qual \
#			-Wstrict-prototypes \
#			-Wpadded \
#
#			gcc flags only
#			-Wformat-overflow \
#			-Wformat-truncation \
#			-Wlogical-op \
#			-Wformat-signedness \
#			-Wduplicated-cond \
#			-Wduplicated-branches \
#			-Walloc-zero

ADDITIONAL_CPPFLAGS=
ADDITIONAL_LDFLAGS=

ifeq (${shell uname}, Darwin)
        LIB_DIRS+= $$HOMEBREW_PREFIX/opt/readline/lib
        INC_DIRS+= $$HOMEBREW_PREFIX/opt/readline/include
endif

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

EXT:=	.c

MAIN:=	main

SRCS_FILES:=	getenv

################################################################################
#                                 SRC's FORMATING                              #
################################################################################

SRCS:=	${addprefix ${SRCS_DIR}/,${addsuffix ${EXT},${MAIN} ${SRCS_FILES}}}


OBJS_DIR:= ${BUILD_DIR}/objs
OBJS:=	${SRCS:${SRCS_DIR}/%.c=${OBJS_DIR}/%.o}

DEPS_DIR:= ${BUILD_DIR}/deps
DEPS:=	${OBJS:${OBJS_DIR}/%.o=${DEPS_DIR}/%.d}

CPPFLAGS= ${addprefix -I,${INC_DIRS}} -MMD -MP -MF ${@:${OBJS_DIR}/%.o=${DEPS_DIR}/%.d}
CPPFLAGS+= ${ADDITIONAL_CPPFLAGS}

LDFLAGS= ${addprefix -L,${LIB_DIRS}}
LDFLAGS+= ${ADDITIONAL_LDFLAGS}

RM:=	rm -rf

COLOR_GREEN := \033[32m
COLOR_RESET := \033[0m

################################################################################
#                                 Makefile rules                               #
################################################################################

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${LDFLAGS} ${OBJS} ${LDLIBS} -o $@
	echo "${COLOR_GREEN}Compilation completed.${COLOR_RESET}"

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
	mkdir -p ${dir $@}
	mkdir -p ${dir ${@:${OBJS_DIR}/%.o=${DEPS_DIR}/%.d}}
	${CC} ${CPPFLAGS} ${CFLAGS} -c $< -o $@

clean:
	${RM} ${BUILD_DIR}
	echo "${COLOR_GREEN}Objects cleaned.${COLOR_RESET}"

fclean: clean
	${RM} ${NAME}
	echo "${COLOR_GREEN}Executables cleaned.${COLOR_RESET}"

re: fclean all

.PHONY:	all clean fclean re

-include ${DEPS}
