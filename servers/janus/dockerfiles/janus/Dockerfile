FROM ubuntu:18.04

# Disable interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install our build prerequisites
RUN apt-get update && apt-get install -y --no-install-recommends \
	automake \
	build-essential \
	ca-certificates \
	gengetopt \
	git \
	libcurl4-openssl-dev \
	libglib2.0-dev \
	libjansson-dev \
	liblua5.3-dev \
	libmicrohttpd-dev \
	libnice-dev \
	libogg-dev \
	libopus-dev \
	libsofia-sip-ua-dev \
	libsrtp2-dev \
	libssl-dev \
	libtool \
	pkg-config

# Clone the Janus source code
RUN git clone --progress --depth=1 -b v0.4.3 "https://github.com/meetecho/janus-gateway.git" /tmp/janus-gateway

# Build Janus
WORKDIR /tmp/janus-gateway
RUN sh autogen.sh && \
	./configure --prefix=/opt/janus && \
	make && \
	make install && \
	make configs

# Clean up the source directory
WORKDIR /opt/janus
RUN rm -R /tmp/janus-gateway

# Copy our custom configuration files into the image
COPY config /tmp/config

# Expose our TCP and UDP ports
EXPOSE 5000/udp
EXPOSE 5001/udp
EXPOSE 8088
EXPOSE 8089
EXPOSE 8889
EXPOSE 7088
EXPOSE 7089

# Set the Janus executable as the entrypoint and point it to our custom config files
ENTRYPOINT [ "/opt/janus/bin/janus", "--configs-folder=/tmp/config" ]
