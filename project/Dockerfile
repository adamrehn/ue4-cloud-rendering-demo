FROM adamrehn/ue4-full:4.20.3

# Install FFmpeg so we can use the MediaIPC FFmpeg RTP streaming consumer
USER root
RUN apt-get update && apt-get install -y --no-install-recommends ffmpeg
USER ue4

# Build the MediaIPC example consumers
RUN git clone --progress --depth=1 https://github.com/adamrehn/MediaIPC.git /tmp/MediaIPC
WORKDIR /tmp/MediaIPC/
RUN \
	conan install . --profile ue4 && \
	conan install . --profile ue4 -g=virtualenv && \
	cat activate.sh >> build.sh && \
	echo 'mkdir /tmp/MediaIPC/build && cd /tmp/MediaIPC/build && cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build .' >> build.sh && \
	chmod +x build.sh && \
	./build.sh

# Build the demo project and pre-fill the DDC
COPY --chown=ue4:ue4 StreamingDemo /tmp/StreamingDemo
WORKDIR /tmp/StreamingDemo
RUN ue4 build
RUN ue4 run -run=DerivedDataCache -fill -projectonly

# Setup our entrypoint
COPY --chown=ue4:ue4 entrypoint.sh /tmp/entrypoint.sh
ENTRYPOINT [ "/bin/bash", "/tmp/entrypoint.sh" ]
