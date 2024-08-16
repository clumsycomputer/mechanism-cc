__CLANG_OPTIONS_ARGUMENTS=$1

if [ ! -d $OUTPUT_DIRECTORY_PATH ]; then
    mkdir -p $OUTPUT_DIRECTORY_PATH
fi
infer run -- \
    clang $__CLANG_OPTIONS_ARGUMENTS \
    -Wall -Wextra -Wpedantic \
    -o $OUTPUT_EXECUTABLE_PATH \
    -lpng16 \
    /workspaces/mechanism-cc/source/main.c \
    /usr/local/lib/libtcc.a \
    /workspaces/mechanism-cc/source/ImagePixels.c
