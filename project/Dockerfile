FROM adamrehn/ue4-full:4.20.3

# Install FFmpeg so we can use the MediaIPC FFmpeg RTP streaming consumer
USER root
RUN apt-get update && apt-get install -y --no-install-recommends ffmpeg
USER ue4

# Build the MediaIPC example consumers
ENV CC=clang-5.0
ENV CXX=clang++-5.0
RUN git clone --progress --depth=1 https://github.com/adamrehn/MediaIPC.git /tmp/MediaIPC
WORKDIR /tmp/MediaIPC/
RUN conan install .
RUN mkdir /tmp/MediaIPC/build
WORKDIR /tmp/MediaIPC/build
RUN cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build .

# Build the demo project
COPY --chown=ue4:ue4 StreamingDemo /tmp/StreamingDemo
WORKDIR /tmp/StreamingDemo
RUN ue4 build

# Setup our entrypoint
COPY --chown=ue4:ue4 entrypoint.sh /tmp/entrypoint.sh
ENTRYPOINT [ "/bin/bash", "/tmp/entrypoint.sh" ]
