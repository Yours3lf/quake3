#!/bin/bash
# this script builds q3 with SDL
# invoke with ./build.sh
# or ./build.sh clean to clean before build

# directory containing the ARM shared libraries (rootfs, lib/ of SD card)
# specifically libEGL.so and libGLESv2.so
#GL_DRIVER_LIBS="/opt/vc/lib"
GL_DRIVER_LIBS="/home/pi/prefix/lib"
SDL_LIB=lib

#LIBEGL=brcmEGL
LIBEGL=EGL
#LIBGLES=brcmGLESv2
LIBGLES=GLESv2

# directory containing baseq3/ containing .pk3 files - baseq3 on CD
BASEQ3_DIR="/home/${USER}/"

# directory to find khronos linux make files (with include/ containing
# headers! Make needs them.)
#INCLUDES="-I/opt/bcm-rootfs/opt/vc/include -I/opt/bcm-rootfs/opt/vc/include/interface/vcos/pthreads"

## rpi version
INCLUDES="-I/home/pi/prefix/include"


# prefix of arm cross compiler installed
## commented out for rpi
#CROSS_COMPILE=bcm2708-

# clean
if [ $# -ge 1 ] && [ $1 = clean ]; then
   echo "clean build"
   rm -rf build/*
fi

# sdl not disabled
make -j4 -f Makefile COPYDIR="$BASEQ3_DIR" ARCH=arm \
	CC=""$CROSS_COMPILE"gcc" USE_SVN=0 USE_CURL=0 USE_OPENAL=0 \
	CFLAGS="-DVCMODS_MISC -DVCMODS_OPENGLES -DVCMODS_DEPTH -DVCMODS_REPLACETRIG $INCLUDES" \
	LDFLAGS="-L"$GL_DRIVER_LIBS" -L$SDL_LIB -lSDL -lkhrn_static -lopenmaxil -l"$LIBEGL" -l"$LIBGLES" -lrt -lX11 -lxcb -lxcb-dri2 -lxcb-dri3 -lxcb-sync -lxcb-present -lxcb-xfixes -lxshmfence -lXau -lX11-xcb -lXdmcp -lexpat"

# copy the required pak3 files over
# cp "$BASEQ3_DIR"/baseq3/*.pk3 "build/release-linux-arm/baseq3/"
# cp -a lib build/release-linux-arm/baseq3/
exit 0

