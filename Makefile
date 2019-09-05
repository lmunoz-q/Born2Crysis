include Makefiles/default_var.mk

NAME := doom-nukem
TEST_ARG += test.b2cm

BLACK_LIST_SRCS += libui mflib

CFLAGS += -D_REENTRANT -flto -O3

INC_DIR += libui/inc mflib mflib/include

Darwin_LDFLAGS += -lm -liconv -Wl,-framework,CoreAudio -Wl,-framework,AudioToolbox -Wl,-framework,ForceFeedback -lobjc -Wl,-framework,CoreVideo -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,IOKit -Wl,-weak_framework,QuartzCore -Wl,-weak_framework,Metal
#note: on linux, if sdl2-config is not present, expect pulseaudio + alsa + x11 + wayland
#to get sdl2-config, install the package libsdl2-dev
#ifneq ($(shell command -v sdl2-config), )
#Linux_LDFLAGS += `$(shell command -v sdl2-config) --static-libs | sed -e "s/-lSDL2 //g"`
#else
Linux_LDFLAGS += -Wl,--no-undefined -lm -ldl -lasound -lm -ldl -lpthread -lpulse-simple -lpulse -lsndio -lX11 -lXext -lXcursor -lXinerama -lXi -lXrandr -lXss -lXxf86vm -lwayland-egl -lwayland-client -lwayland-cursor -lxkbcommon -lpthread -lrt
#endif

Darwin_LDLIBS += $(PACKAGE_MANAGER_LIB)/libSDL2.dylib $(PACKAGE_MANAGER_LIB)/libSDL2_ttf.dylib $(PACKAGE_MANAGER_LIB)/libSDL2_mixer.dylib $(PACKAGE_MANAGER_LIB)/libSDL2_image.dylib $(PACKAGE_MANAGER_LIB)/libSDL2_net.dylib
Linux_LDLIBS += $(PACKAGE_MANAGER_LIB)/libSDL2.so $(PACKAGE_MANAGER_LIB)/libSDL2_ttf.so $(PACKAGE_MANAGER_LIB)/libSDL2_mixer.so $(PACKAGE_MANAGER_LIB)/libSDL2_image.so $(PACKAGE_MANAGER_LIB)/libSDL2_net.so
LDLIBS += mflib/mflib.a
CLIB += libui/libui.a

include Makefiles/bin.mk

mflib/mflib.a:
	$(MAKE) -C mflib

ifeq ($(UNAME), Darwin)

$(PACKAGE_MANAGER_LIB)/libSDL2_net.dylib:
	$(PACKAGE_MANAGER) install SDL2_net
	touch $(PACKAGE_MANAGER_LIB)/libSDL2_net.dylib
$(PACKAGE_MANAGER_LIB)/libSDL2.dylib:
	$(PACKAGE_MANAGER) install SDL2
	touch $(PACKAGE_MANAGER_LIB)/libSDL2.dylib
$(PACKAGE_MANAGER_LIB)/libSDL2_ttf.dylib:
	$(PACKAGE_MANAGER) install SDL2_ttf
	touch $(PACKAGE_MANAGER_LIB)/libSDL2_ttf.dylib
$(PACKAGE_MANAGER_LIB)/libSDL2_mixer.dylib:
	$(PACKAGE_MANAGER) install SDL2_mixer
	touch $(PACKAGE_MANAGER_LIB)/libSDL2_mixer.dylib
$(PACKAGE_MANAGER_LIB)/libSDL2_image.dylib:
	$(PACKAGE_MANAGER) install SDL2_image
	touch $(PACKAGE_MANAGER_LIB)/libSDL2_image.dylib

else ifeq ($(UNAME), Linux)

$(PACKAGE_MANAGER_LIB)/libSDL2.so:
		$(PACKAGE_MANAGER) $(PACKAGE_MANAGER_INSTALL_ARGUMENT) $(SDL2_NAME)

$(PACKAGE_MANAGER_LIB)/libSDL2_ttf.so:
		$(PACKAGE_MANAGER) $(PACKAGE_MANAGER_INSTALL_ARGUMENT) $(SDL2_TTF_NAME)

$(PACKAGE_MANAGER_LIB)/libSDL2_mixer.so:
		$(PACKAGE_MANAGER) $(PACKAGE_MANAGER_INSTALL_ARGUMENT) $(SDL2_MIXER_NAME)

$(PACKAGE_MANAGER_LIB)/libSDL2_image.so:
		$(PACKAGE_MANAGER) $(PACKAGE_MANAGER_INSTALL_ARGUMENT) $(SDL2_IMAGE_NAME)

$(PACKAGE_MANAGER_LIB)/libSDL2_net.so:
		$(PACKAGE_MANAGER) $(PACKAGE_MANAGER_INSTALL_ARGUMENT) $(SDL2_NET_NAME)

else

SDL2-2.0.9/build/libSDL2.dylib:
	echo "non OSX is not supported for now"

endif
