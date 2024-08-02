if [ ! -d $DEPENDENCIES_DIRECTORY_PATH ]; then
    sudo mkdir -p $DEPENDENCIES_DIRECTORY_PATH
fi
sudo curl --location --remote-name https://github.com/TinyCC/tinycc/archive/refs/heads/mob.zip \
    && unzip -d $DEPENDENCIES_DIRECTORY_PATH ./mob.zip \
    && rm ./mob.zip \
    && cd $DEPENDENCIES_DIRECTORY_PATH/tinycc-mob \
    && sudo ./configure \
    && sudo make \
    && sudo make install
sudo curl --location --remote-name https://github.com/pnggroup/libpng/archive/refs/heads/libpng16.zip \
    && unzip -d $DEPENDENCIES_DIRECTORY_PATH ./libpng16.zip \
    && rm ./libpng16.zip \
    && cd $DEPENDENCIES_DIRECTORY_PATH/libpng-libpng16 \
    && sudo ./configure \
    && sudo make \
    && sudo make install
sudo curl --location --remote-name https://github.com/madler/zlib/archive/refs/heads/master.zip \
    && unzip -d $DEPENDENCIES_DIRECTORY_PATH ./master.zip \
    && rm ./master.zip \
    && cd $DEPENDENCIES_DIRECTORY_PATH/zlib-master \
    && sudo ./configure \
    && sudo make \
    && sudo make install