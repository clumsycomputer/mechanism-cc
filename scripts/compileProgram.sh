__CLANG_OPTIONS_ARGUMENTS=$1

if [ ! -d $OUTPUT_DIRECTORY_PATH ]; then
    mkdir -p $OUTPUT_DIRECTORY_PATH
fi
infer run -- \
    clang $__CLANG_OPTIONS_ARGUMENTS \
    -o $OUTPUT_EXECUTABLE_PATH \
    -lpng16 \
    $MAIN_SOURCE_FILE_PATH \
    /usr/local/lib/libtcc.a
