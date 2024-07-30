__INFER_VERSION=1.1.0
__INFER_OUTPUT_DIRECTORY_PATH=/opt

sudo apt-get update
sudo apt-get install -y clang clang-tools clangd lldb lld
sudo curl --remote-name --location https://github.com/facebook/infer/releases/download/v${__INFER_VERSION}/infer-linux64-v${__INFER_VERSION}.tar.xz \
    && sudo tar --directory $__INFER_OUTPUT_DIRECTORY_PATH --extract --xz --file ./infer-linux64-v${__INFER_VERSION}.tar.xz \
    && sudo rm -rf ./infer-linux64-v${__INFER_VERSION}.tar.xz \
    && sudo ln -s /opt/infer-linux64-v${__INFER_VERSION}/bin/infer /usr/local/bin/infer \
    && export PATH=/infer/bin:${PATH}