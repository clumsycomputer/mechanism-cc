if [ ! -d $DEPENDENCIES_DIRECTORY_PATH ]; then
    sudo mkdir -p $DEPENDENCIES_DIRECTORY_PATH
fi
sudo curl -L -o tinycc-mob.zip https://github.com/TinyCC/tinycc/archive/refs/heads/mob.zip \
    && unzip -d $DEPENDENCIES_DIRECTORY_PATH ./tinycc-mob.zip \
    && rm ./tinycc-mob.zip \
    && cd $DEPENDENCIES_DIRECTORY_PATH/tinycc-mob \
    && sudo ./configure \
    && sudo make \
    && sudo make install