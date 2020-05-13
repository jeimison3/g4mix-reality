#!/bin/bash
IFS= read -rsp 'Digite sua senha: ' password



# sudo -S apt-get install build-essential mercurial make cmake autoconf automake \
# libtool libasound2-dev libpulse-dev libaudio-dev libx11-dev libxext-dev \
# libxrandr-dev libxcursor-dev libxi-dev libxinerama-dev libxxf86vm-dev \
# libxss-dev libgl1-mesa-dev libesd0-dev libdbus-1-dev libudev-dev \
# libgles2-mesa-dev libgles2-mesa-dev libegl1-mesa-dev libibus-1.0-dev \
# fcitx-libs-dev libsamplerate0-dev libsndio-dev xorg-dev guile-2.0-dev


echo "====================================="
echo ">>>>>>>>>>>>>>>> PACOTES BUILD:"
sudo -S apt-get install \
build-essential linux-headers-$(uname -r) \
-y <<<"$password"


echo "====================================="
echo ">>>>>>>>>>>>>>>> PACOTES PRINCIPAIS:"
sudo -S apt-get install \
libsdl2-dev libsdl2-2.0-0 \
-y <<<"$password"


echo "====================================="
echo ">>>>>>>>>>>>>>>> SDL IMAGE:"
sudo -S apt-get install \
libjpeg9-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0 \
-y <<<"$password"

echo "====================================="
echo ">>>>>>>>>>>>>>>> SDL MIXER:"
sudo -S apt-get install \
libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0 \
-y <<<"$password"

echo "====================================="
echo ">>>>>>>>>>>>>>>> TRUE TYPE FONTS:"
sudo -S apt-get install \
libfreetype6-dev libsdl2-ttf-dev libsdl2-ttf-2.0-0 \
-y <<<"$password"


sudo -S apt-get autoremove -y <<<"$password"
