if [ ! -d $DEPENDENCIES_DIRECTORY_PATH ]; then
    sudo mkdir -p $DEPENDENCIES_DIRECTORY_PATH
fi
sudo curl --remote-name --location https://download.savannah.gnu.org/releases/tinycc/tcc-0.9.27.tar.bz2 \
    && sudo tar --directory $DEPENDENCIES_DIRECTORY_PATH --extract --bzip2 --file ./tcc-0.9.27.tar.bz2 \
    && sudo rm -rf ./tcc-0.9.27.tar.bz2