FROM mcr.microsoft.com/devcontainers/base:ubuntu
USER vscode
ENV PROJECT_DIRECTORY_PATH=/workspaces/mechanism_cc
ENV OUTPUT_DIRECTORY_PATH=${PROJECT_DIRECTORY_PATH}/out
ENV OUTPUT_EXECUTABLE_PATH=${OUTPUT_DIRECTORY_PATH}/mechanism_cc
ENV DEPENDENCIES_DIRECTORY_PATH=${PROJECT_DIRECTORY_PATH}/dependencies
ENV MAIN_SOURCE_FILE_PATH=${PROJECT_DIRECTORY_PATH}/source/main.c
COPY ./scripts/installBuildTools.sh /tmp
RUN bash ./tmp/installBuildTools.sh
RUN sudo rm /tmp/installBuildTools.sh
