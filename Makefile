NAME = graphics_nerd

SRCS = \
	main.cpp \
	camera.cpp \
	controls.cpp \
	dds_parser.cpp \
	fps_timer.cpp \
	image_loader.cpp \
	shader.cpp \
	systems.cpp \
	update_world.cpp \
	utils.cpp \
	typewriter.cpp \
	glad.c \

HEADERS = \
	libkaf/libkaf.h \
	headers/camera.hpp \
	headers/controls.hpp \
	headers/nerd.hpp \
	headers/shader.hpp \
	headers/typewriter.hpp \

CC = g++

ABS_DIR = $(shell pwd)
INCLUDES = -Ilibkaf -Iglad/include/ -Iglfw/GLFW/include
LIBS = -Llibkaf/
SDL_SRCS = $(ABS_DIR)/SDL2-2.0.14/
SDL_LIBS = $(ABS_DIR)/SDL2/
SDL_INC = SDL2/include/SDL2/
SDL_MIXER_SRCS = $(ABS_DIR)/SDL2_mixer-2.0.4/
SDL_MIXER_LIBS = $(ABS_DIR)/SDL2_mixer/
SDL_MIXER_INC = SDL2_mixer/include/SDL2/
CORES = $(shell echo 2+$(shell cat /proc/cpuinfo | grep processor | wc -l) | bc)
GLFW_SRCS = $(ABS_DIR)/glfw-3.3.4
GLFW_LIBS = $(ABS_DIR)/glfw
GLAD = $(ABS_DIR)/glad
FREETYPE_SRCS = $(ABS_DIR)/freetype-2.11.0
FREETYPE_LIBS = $(ABS_DIR)/freetype
CFLAGS_GLFW = $(shell export PKG_CONFIG_PATH=/home/kafkalainen/Documents/cplusplus/glfw/lib/pkgconfig && pkg-config --cflags glfw3)
CFLAGS_SDL = $(shell $(ABS_DIR)/SDL2/bin/sdl2-config --cflags)
CFLAGS_FREETYPE = $(shell export PKG_CONFIG_PATH=$(FREETYPE_LIBS) && $(FREETYPE_LIBS)/freetype-config --cflags)
CFLAGS = -Wall -Wextra -Werror -g $(shell pkg-config --cflags gl) $(CFLAGS_SDL) $(CFLAGS_GLFW) $(CFLAGS_FREETYPE)
LIBS_GLFW = $(shell export PKG_CONFIG_PATH=/home/kafkalainen/Documents/cplusplus/glfw/lib/pkgconfig && pkg-config --static --libs glfw3)
LIBS_SDL = $(shell $(ABS_DIR)/SDL2/bin/sdl2-config --libs)
LIBS_STB = $(ABS_DIR)/stb
LIBS_FREETYPE = $(shell export PKG_CONFIG_PATH=$(FREETYPE_LIBS) && $(FREETYPE_LIBS)/freetype-config --static --libs)
LDFLAGS = -lkaf $(LIBS_GLFW) $(LIBS_SDL) "-Wl,-rpath,$(GLFW_LIBS)/lib" $(LIBS_FREETYPE)
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

S = srcs
O = objs
LIBKAF = libkaf$(SLASH)libkaf.a
SRC = $(addprefix $S$(SLASH), $(SRCS))
OBJ = $(SRC:$S%=$O%.o)

.PHONY: all clean fclean re

all: $(NAME)

$(GLFW_LIBS):
	@if [ ! -d $(GLFW_SRCS) ]; then \
		unzip glfw-3.3.4.zip; \
	fi
	@if [ ! -d $(GLFW_LIBS) ]; then \
		cmake -DCMAKE_INSTALL_PREFIX:PATH=$(GLFW_LIBS) -S $(GLFW_SRCS) -B $(GLFW_LIBS) && \
		cd $(GLFW_LIBS) && \
		make install; \
	fi

$(SDL_LIBS):
	@if [ ! $(shell command -v wget 2> /dev/null) ]; then \
	sudo apt-get install wget -y; \
	fi
	@if [ ! -f "SDL2-2.0.14.tar.gz" ]; then \
	wget https://www.libsdl.org/release/SDL2-2.0.14.tar.gz; \
	fi
	@if [ ! -d "$(SDL_SRCS)" ]; then \
	tar -xzf SDL2-2.0.14.tar.gz; \
	fi
	@if [ ! -d "$(SDL_LIBS)" ] ; then \
	mkdir -p $(SDL_LIBS); \
	cd $(SDL_LIBS) && \
	$(SDL_SRCS)./configure --prefix=$(SDL_LIBS) && \
	make -j$(CORES) && make install ; \
	else    \
	make -j$(CORES) -C $(SDL_LIBS) ; \
	fi

$(SDL_MIXER_LIBS):
	@if [ ! $(shell command -v wget 2> /dev/null) ]; then \
	sudo apt-get install wget -y; \
	fi
	@if [ ! -f "SDL2_mixer-2.0.4.tar.gz" ]; then \
	wget https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.4.tar.gz; \
	fi
	@if [ ! -d "$(SDL_MIXER_SRCS)" ]; then \
	tar -xzf SDL2_mixer-2.0.4.tar.gz; \
	fi
	@if [ ! -d "$(SDL_MIXER_LIBS)" ] ; then \
	mkdir -p $(SDL_MIXER_LIBS); \
	cd $(SDL_MIXER_LIBS) && \
	$(SDL_MIXER_SRCS)./configure --prefix $(SDL_MIXER_LIBS) && \
	make -j$(CORES) && make install; \
	else \
	make -j$(CORES) -C $(SDL_MIXER_LIBS) ; \
	fi

$(OPENGL):
	sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev

$(GLAD):
	@if [ ! -d $(GLAD) ]; then \
		mkdir -p glad && \
		unzip glad.zip -d glad && \
		mv glad/src/glad.c srcs/glad.c;
	fi

$(FREETYPE_LIBS):
	@if [ ! -d $(FREETYPE_SRCS) ]; then \
		tar -xzf freetype-2.11.0.tar.gz; \
	fi
	@if [ ! -d "$(FREETYPE_LIBS)" ] ; then \
		mkdir -p $(FREETYPE_LIBS); \
		cd $(FREETYPE_LIBS) && \
		$(FREETYPE_SRCS)/configure --prefix=$(FREETYPE_LIBS) && \
		make && make install; \
	fi

$(LIBS_STB):
	git clone git@github.com:nothings/stb.git
$O:
	$(MKDIR) $@
	$(MKDIR) $@/utils

$(OBJ): | $O

$(OBJ): $O%.o: $S% $(HEADERS)
	$(CC) -c -o $@ $(CFLAGS) $(INCLUDES) $<

$(LIBKAF):
	make -C libkaf

$(NAME): $(LIBKAF) $(SDL_LIBS) $(SDL_MIXER_LIBS) $(OPENGL) $(GLFW_LIBS) $(FREETYPE_LIBS) $(LIBS_STB) $(OBJ)
	$(CC) -o $@ $(INCLUDES) $(LIBS) $(CFLAGS) $(OBJ) $(LDFLAGS)
	@echo $(GREEN)Compiled executable $(NAME).

cleanobj:
ifneq ($(wildcard $(OBJ)),)
	@$(RM) $(wildcard $(OBJ))
endif

cleanobjdir: cleanobj
	@$(RM) $O

clean: cleanobjdir
	@if [ -d "$(SDL_LIBS)" ] ; then \
	make -C $(SDL_LIBS) clean ; \
	fi;
	@if [ -d "$(SDL_MIXER_LIBS)" ] ; then \
	make -C $(SDL_MIXER_LIBS) clean ; \
	fi;
	@make -C libft clean
	@echo $(GREEN)Cleaned projects from object files.$(RESET)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(SDL_LIBS)
	@$(RM) $(SDL_MIXER_LIBS)
	@$(RM) $(SDL_SRCS)
	@$(RM) $(SDL_MIXER_SRCS)
	@make -C libkaf fclean
	@echo $(GREEN)Removed binaries and libraries.$(RESET)

re: fclean all
