NAME = graphics_nerd

SRCS = \
	main.cpp \
	camera.cpp \
	controls.cpp \
	dds_parser.cpp \
	shader.cpp \
	systems.cpp \
	utils.cpp \

HEADERS = \
	libkaf/libkaf.h \
	headers/nerd.h \

CC = g++

ABS_DIR = $(shell pwd)
INCLUDES = -Ilibkaf -Iglm -Iglew/include/GL -Iglfw/GLFW/include
LIBS = -Llibkaf/
SDL_SRCS = $(ABS_DIR)/SDL2-2.0.14/
SDL_LIBS = $(ABS_DIR)/SDL2/
SDL_INC = SDL2/include/SDL2/
SDL_MIXER_SRCS = $(ABS_DIR)/SDL2_mixer-2.0.4/
SDL_MIXER_LIBS = $(ABS_DIR)/SDL2_mixer/
SDL_MIXER_INC = SDL2_mixer/include/SDL2/
CORES = $(shell echo 2+$(shell cat /proc/cpuinfo | grep processor | wc -l) | bc)
GLM = $(shell dpkg -l | grep libglm-dev)
GLFW_SRCS = $(ABS_DIR)/glfw-3.3.4
GLFW_LIBS = $(ABS_DIR)/glfw
GLEW_SRCS = $(ABS_DIR)/glew-1.13.0
GLEW_LIBS = $(ABS_DIR)/glew
CFLAGS_GLFW = $(shell export PKG_CONFIG_PATH=/home/kafkalainen/Documents/cplusplus/glfw/lib/pkgconfig && pkg-config --cflags glfw3)
CFLAGS_GLEW = $(shell export PKG_CONFIG_PATH=/home/kafkalainen/Documents/cplusplus/glew/lib64/pkgconfig && pkg-config --cflags glew)
CFLAGS_SDL = $(shell $(ABS_DIR)/SDL2/bin/sdl2-config --cflags)
CFLAGS = -Wall -Wextra -Werror -g $(shell pkg-config --cflags gl) $(CFLAGS_SDL) $(CFLAGS_GLEW) $(CFLAGS_GLFW)
LIBS_GLFW = $(shell export PKG_CONFIG_PATH=/home/kafkalainen/Documents/cplusplus/glfw/lib/pkgconfig && pkg-config --static --libs glfw3)
LIBS_GLEW = $(shell export PKG_CONFIG_PATH=/home/kafkalainen/Documents/cplusplus/glew/lib64/pkgconfig && pkg-config --static --libs glew)
LIBS_SDL = $(shell $(ABS_DIR)/SDL2/bin/sdl2-config --libs)
LDFLAGS = -lkaf $(LIBS_GLEW) $(LIBS_GLFW) $(LIBS_SDL) "-Wl,-rpath,$(GLEW_LIBS)/lib64" "-Wl,-rpath,$(GLFW_LIBS)/lib"
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

.PHONY: all clean fclean re glm

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

$(GLEW_LIBS):
	@if [ ! -d $(GLEW_SRCS) ]; then \
		tar -xzf glew-1.13.0.tgz; \
	fi
	cd $(GLEW_SRCS) && \
	make GLEW_DEST=$(GLEW_LIBS) && \
	make install GLEW_DEST=$(GLEW_LIBS)

glm:
ifndef GLM
	sudo apt install libglm-dev
endif

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

$O:
	$(MKDIR) $@
	$(MKDIR) $@/utils

$(OBJ): | $O

$(OBJ): $O%.o: $S% $(HEADERS)
	$(CC) -c -o $@ $(CFLAGS) $(INCLUDES) $<

$(LIBKAF):
	make -C libkaf

$(NAME): $(LIBKAF) $(SDL_LIBS) $(SDL_MIXER_LIBS) $(OPENGL) $(GLFW_LIBS) $(GLEW_LIBS) glm $(OBJ)
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
