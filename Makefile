include Makefiles/default_var.mk

NAME := doom-nukem

BLACK_LIST_SRCS += libui SDL_rudp

CFLAGS += -D_REENTRANT

INC_DIR += libui/inc SDL_rudp/inc

SHELL := zsh #make sure that the builtin 'command' is available

Darwin_LDFLAGS += -lm -liconv -Wl,-framework,CoreAudio -Wl,-framework,AudioToolbox -Wl,-framework,ForceFeedback -lobjc -Wl,-framework,CoreVideo -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,IOKit -Wl,-weak_framework,QuartzCore -Wl,-weak_framework,Metal
#note: on linux, if sdl2-config is not present, expect pulseaudio + alsa + x11 + wayland
#to get sdl2-config, install the package libsdl2-dev
ifneq ($(shell command -v sdl2-config), )
Linux_LDFLAGS += `$(shell command -v sdl2-config) --static-libs | sed -e "s/-lSDL2 //g"`
else
Linux_LDFLAGS += -Wl,--no-undefined -lm -ldl -lasound -lm -ldl -lpthread -lpulse-simple -lpulse -lsndio -lX11 -lXext -lXcursor -lXinerama -lXi -lXrandr -lXss -lXxf86vm -lwayland-egl -lwayland-client -lwayland-cursor -lxkbcommon -lpthread -lrt
endif

LDLIBS += $(PACKAGE_MANAGER_LIB)/libSDL2.dylib $(PACKAGE_MANAGER_LIB)/libSDL2_ttf.dylib $(PACKAGE_MANAGER_LIB)/libSDL2_mixer.dylib $(PACKAGE_MANAGER_LIB)/libSDL2_image.dylib $(PACKAGE_MANAGER_LIB)/libSDL2_net.dylib
CLIB += libui/libui.a SDL_rudp/libsdl_rudp.a

include Makefiles/bin.mk

ifeq ($(UNAME), Darwin)

$(PACKAGE_MANAGER_LIB)/libSDL2_net.dylib: $(PACKAGE_MANAGER)
	$(PACKAGE_MANAGER) install SDL2_net
	touch $(PACKAGE_MANAGER_LIB)/libSDL2_net.dylib
$(PACKAGE_MANAGER_LIB)/libSDL2.dylib: $(PACKAGE_MANAGER)
	$(PACKAGE_MANAGER) install SDL2
	touch $(PACKAGE_MANAGER_LIB)/libSDL2.dylib
$(PACKAGE_MANAGER_LIB)/libSDL2_ttf.dylib: $(PACKAGE_MANAGER)
	$(PACKAGE_MANAGER) install SDL2_ttf
	touch $(PACKAGE_MANAGER_LIB)/libSDL2_ttf.dylib
$(PACKAGE_MANAGER_LIB)/libSDL2_mixer.dylib: $(PACKAGE_MANAGER)
	$(PACKAGE_MANAGER) install SDL2_mixer
	touch $(PACKAGE_MANAGER_LIB)/libSDL2_mixer.dylib
$(PACKAGE_MANAGER_LIB)/libSDL2_image.dylib: $(PACKAGE_MANAGER)
	$(PACKAGE_MANAGER) install SDL2_image
	touch $(PACKAGE_MANAGER_LIB)/libSDL2_image.dylib

else

SDL2-2.0.9/build/libSDL2.dylib:
	echo "non OSX is not supported for now"

endif
