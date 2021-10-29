NAME = libkaf.a

S = src
O = obj

ifeq ($(OS),Windows_NT)
	TARGET_SYSTEM := Windows
else
	TARGET_SYSTEM := $(shell uname -s)
	TARGET_SYSTEM := $(patsubst CYGWIN%,Cygwin,$(TARGET_SYSTEM))
	TARGET_SYSTEM := $(patsubst MSYS%,MSYS,$(TARGET_SYSTEM))
	TARGET_SYSTEM := $(patsubst MINGW%,MSYS,$(TARGET_SYSTEM))
endif

ifeq ($(TARGET_SYSTEM),Windows)
	RM = del /s/q
	SLASH = \\
	MKDIR = mkdir
else
	RM = /bin/rm -rf
	SLASH = /
	MKDIR = mkdir -p
endif

SRC_LIST = \
	$(SLASH)kaf_arithmetic.cpp \
	$(SLASH)kaf_nblen.cpp \
	$(SLASH)kaf_putendl.cpp \
	$(SLASH)kaf_putstr.cpp \
	$(SLASH)kaf_strncmp.cpp \
	$(SLASH)kaf_swap.cpp \
	$(SLASH)kaf_vectors.cpp \
	$(SLASH)kaf_object_constructor.cpp \
	$(SLASH)kaf_object_methods.cpp \
	$(SLASH)kaf_object_helper_methods.cpp \
	$(SLASH)kaf_memcpy.cpp \
	$(SLASH)kaf_memcmp.cpp \

HEADERS = ./libkaf.h

CC = g++
CFLAGS = -Wall -Wextra -Werror -g -std=c++14
SRC = $(addprefix $S, $(SRC_LIST))
OBJ = $(SRC:$S%=$O%.o)

.PHONY: all tests clean fclean re cleanobj cleanobjdir

all: $(NAME)

tests: all
	cd mains && \
	/bin/bash tests.sh

$O:
	$(MKDIR) $@

$(OBJ): | $O

$(OBJ): $O%.o: $S% $(HEADERS)
	$(CC) -c -o $@ $(CFLAGS) -I. $<

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
	@echo Successfully created $(NAME)

cleanobj:
ifneq ($(wildcard $(OBJ)),)
	$(RM) $(wildcard $(OBJ))
endif

cleanobjdir: cleanobj
ifeq ($(TARGET_SYSTEM), Linux)
	$(RM) $O
else
	IF EXIST $O ( rd /s /q "$O" )
endif

clean: cleanobjdir
	@echo Removed object files.

fclean: clean
ifeq ($(TARGET_SYSTEM), Linux)
	$(RM) $(NAME)
else
	IF EXIST $(NAME) ( $(RM) "$(NAME)" )
endif

re: fclean all
