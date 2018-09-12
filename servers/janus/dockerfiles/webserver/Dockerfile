FROM ubuntu:18.04

# Disable interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install git and Python
RUN apt-get update && apt-get install -y --no-install-recommends \
	ca-certificates \
	git \
	python3

# Clone the Janus source code and make the streaming demo the index page
RUN git clone --progress --depth=1 -b v0.4.3 "https://github.com/meetecho/janus-gateway.git" /tmp/janus-gateway
RUN mv /tmp/janus-gateway/html/streamingtest.html /tmp/janus-gateway/html/index.html

# Use Python to serve the static web files over HTTP
EXPOSE 8000
WORKDIR /tmp/janus-gateway/html/
ENTRYPOINT [ "/usr/bin/python3", "-m", "http.server" ]
