NAME = graphics_nerd

SRCS = \
	main.cpp \
	utils/utils.cpp \

HEADERS = \
	libkaf/libkaf.h \
	headers/nerd.h

CC = g++

ABS_DIR = $(shell pwd)
INCLUDES = -Ilibkaf
LIBS = -Llibkaf/
CFLAGS = -Wall -Wextra -Werror -g $(shell pkg-config --cflags gl) $(shell $(ABS_DIR)/SDL2/bin/sdl2-config --cflags)
LDFLAGS = -lkaf $(shell pkg-config --libs gl) $(shell $(ABS_DIR)/SDL2/bin/sdl2-config --libs) -lGLU -lglut
SLASH = /
MKDIR := mkdir -p
RM = /bin/rm -rf
RESET = "\033[0m"
RED = "\033[0;31m"
GREEN = "\033[0;32m"
YELLOW = "\033[0;33m"
BLUE = "\033[0;34m"
MAGENTA = "\033[0;35m"
CYAN = "\033[0;36m"
WHITE = "\033[0;37m"
OPENGL = $(shell pkg-config --libs gl)
SDL_ORIG = $(ABS_DIR)/SDL2-2.0.14/
SDL_NEW = $(ABS_DIR)/SDL2/
SDL_INC = SDL2/include/SDL2/
SDL_MIXER_ORIG = $(ABS_DIR)/SDL2_mixer-2.0.4/
SDL_MIXER_NEW = $(ABS_DIR)/SDL2_mixer/
SDL_MIXER_INC = SDL2_mixer/include/SDL2/
CORES = $(shell echo 2+$(shell cat /proc/cpuinfo | grep processor | wc -l) | bc)

S = srcs
O = objs
LIBKAF = libkaf$(SLASH)libkaf.a
SRC = $(addprefix $S$(SLASH), $(SRCS))
OBJ = $(SRC:$S%=$O%.o)

.PHONY: all clean fclean re

all: $(NAME)

$(SDL_NEW):
	@if [ ! $(shell command -v wget 2> /dev/null) ]; then \
	sudo apt-get install wget -y; \
	fi
	@if [ ! -f "SDL2-2.0.14.tar.gz" ]; then \
	wget https://www.libsdl.org/release/SDL2-2.0.14.tar.gz; \
	fi
	@if [ ! -d "$(SDL_ORIG)" ]; then \
	tar -xzf SDL2-2.0.14.tar.gz; \
	fi
	@if [ ! -d "$(SDL_NEW)" ] ; then \
	mkdir -p $(SDL_NEW); \
	cd $(SDL_NEW) && \
	$(SDL_ORIG)./configure --prefix=$(SDL_NEW) && \
	make -j$(CORES) && make install ; \
	else    \
	make -j$(CORES) -C $(SDL_NEW) ; \
	fi

$(SDL_MIXER_NEW):
	@if [ ! $(shell command -v wget 2> /dev/null) ]; then \
	sudo apt-get install wget -y; \
	fi
	@if [ ! -f "SDL2_mixer-2.0.4.tar.gz" ]; then \
	wget https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.4.tar.gz; \
	fi
	@if [ ! -d "$(SDL_MIXER_ORIG)" ]; then \
	tar -xzf SDL2_mixer-2.0.4.tar.gz; \
	fi
	@if [ ! -d "$(SDL_MIXER_NEW)" ] ; then \
	mkdir -p $(SDL_MIXER_NEW); \
	cd $(SDL_MIXER_NEW) && \
	$(SDL_MIXER_ORIG)./configure --prefix $(SDL_MIXER_NEW) && \
	make -j$(CORES) && make install; \
	else \
	make -j$(CORES) -C $(SDL_MIXER_NEW) ; \
	fi

$(OPENGL):
	sudo apt-get install freeglut3-dev

$O:
	$(MKDIR) $@
	$(MKDIR) $@/utils

$(OBJ): | $O

$(OBJ): $O%.o: $S% $(HEADERS)
	$(CC) -c -o $@ $(CFLAGS) $(INCLUDES) $<

$(LIBKAF):
	make -C libkaf

$(NAME): $(LIBKAF) $(SDL_NEW) $(SDL_MIXER_NEW) $(OPENGL) $(OBJ)
	$(CC) -o $@ $(INCLUDES) $(LIBS) $(CFLAGS) $(OBJ) $(LDFLAGS)
	@echo $(GREEN)Compiled executable $(NAME).

cleanobj:
ifneq ($(wildcard $(OBJ)),)
	@$(RM) $(wildcard $(OBJ))
endif

cleanobjdir: cleanobj
	@$(RM) $O

clean: cleanobjdir
	@if [ -d "$(SDL_NEW)" ] ; then \
	make -C $(SDL_NEW) clean ; \
	fi;
	@if [ -d "$(SDL_MIXER_NEW)" ] ; then \
	make -C $(SDL_MIXER_NEW) clean ; \
	fi;
	@make -C libft clean
	@echo $(GREEN)Cleaned projects from object files.$(RESET)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(SDL_NEW)
	@$(RM) $(SDL_MIXER_NEW)
	@$(RM) $(SDL_ORIG)
	@$(RM) $(SDL_MIXER_ORIG)
	@make -C libkaf fclean
	@echo $(GREEN)Removed binaries and libraries.$(RESET)

re: fclean all
