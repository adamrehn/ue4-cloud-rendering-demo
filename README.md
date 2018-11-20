UE4 Cloud Rendering Demo
========================

The code in this repository demonstrates performing cloud rendering using the NVIDIA Docker containers built by the [ue4-docker](https://github.com/adamrehn/ue4-docker) Python package and then streaming the results to a web browser via WebRTC. **Note that this code is provided as an example only and is NOT designed for production use.**

## Contents

- [Prerequisites](#prerequisites)
- [Running the demo](#running-the-demo)
- [Enabling audio output (experimental)](#enabling-audio-output-experimental)
- [Frequently Asked Questions](#frequently-asked-questions)
- [Legal](#legal)


## Prerequisites

General requirements:

- Linux distribution with NVIDIA binary drivers satisfying the [NVIDIA Docker installation requirements](https://github.com/NVIDIA/nvidia-docker/wiki/Installation-(version-2.0)#prerequisites)
- NVIDIA graphics card satisfying the [NVIDIA Docker installation requirements](https://github.com/NVIDIA/nvidia-docker/wiki/Installation-(version-2.0)#prerequisites)
- [Docker](https://www.docker.com/) and [Docker Compose](https://docs.docker.com/compose/) 1.19.0 or newer
- [NVIDIA Docker](https://github.com/NVIDIA/nvidia-docker) 2.x
- [ue4-docker](https://github.com/adamrehn/ue4-docker) 0.0.5 or newer

Audio output has a couple of extra requirements:

- A PulseAudio server needs to be running on the host. This will already be the case by default for most modern desktop distributions of Linux.
- You will need to ensure you have added a non-root user to the `docker` group as described by the [Post-installation steps for Linux](https://docs.docker.com/install/linux/linux-postinstall/) page of the Docker documentation., since the PulseAudio socket cannot be bind-mounted correctly if the commands for running the demo are invoked as the root user.


## Running the demo

- Ensure you have built the NVIDIA Docker image `adamrehn/ue4-full:4.20.3` using [ue4-docker](https://github.com/adamrehn/ue4-docker) version 0.0.5 or newer. Assuming you have the package installed and the host system is configured correctly, you can build the image using the following command:
  
  ```
  ue4-docker build 4.20.3 --no-engine
  ```

- Run the appropriate shell script for the WebRTC server you want to use:
  
  - `./run-demo-janus.sh` for the example using the [Janus WebRTC Server](https://janus.conf.meetecho.com/)

- Docker will build and run the images for the demo. This may take some time. You will know everything is built and running when you see the following lines in the log output:
  
  ```
  Received Control Block:
  
  videoFormat = Packed BGRA 8:8:8:8
  width = 640
  height = 360
  bytesPerPixel = 4
  frameRate = 30
  audioFormat = PCM 32-bit floating-point little-endian
  channels = 6
  sampleRate = 48000
  samplesPerBuffer = 1024
  bytesPerSample = 4
  ```

- Open the URL <http://127.0.0.1:8000/> in a web browser with VP8 support such as Mozilla Firefox or Google Chrome. The exact details of the page that loads will depend on which WebRTC server is being used:
  
  - When using Janus, you will see a copy of the [Janus Streaming plugin demo page](https://janus.conf.meetecho.com/streamingtest.html). Press the "Start" button to bring up the list of available streams, and select **"VP8/Opus live stream from UE4 and FFmpeg"** from the dropdown list. Finally, press the "Watch or Listen" button to activate the WebRTC stream. Once it is active, you should see the live video output from the UE4 demo project displayed and you should hear the Mozart serenade *[Eine kleine Nachtmusik](https://en.wikipedia.org/wiki/Eine_kleine_Nachtmusik)* playing. (The audio file is the Creative Commons licensed [recording from the Wikipedia article](https://en.wikipedia.org/wiki/File:Mozart_-_Eine_kleine_Nachtmusik_-_1._Allegro.ogg).)


## Frequently Asked Questions

- **Q: Can the WebRTC video stream be viewed from a different machine to the host that is running the demo?**
  
  **A:** The demo is only configured for HTTP, not for HTTPS, which means WebRTC will only function over localhost due to security restrictions. In production scenarios a TLS certificate would be used, which would allow access from other machines over HTTPS.

- **Q: Can the demo be modified to run under Windows or macOS?**
  
  **A:** No, because [NVIDIA Docker only supports Linux](https://github.com/NVIDIA/nvidia-docker/wiki/Frequently-Asked-Questions#platform-support) and the purpose of the demo is to illustrate Unreal Engine 4 running in an NVIDIA Docker container.


## Legal

Copyright &copy; 2018, Adam Rehn. Licensed under the MIT License, see the file [LICENSE](./LICENSE) for details.

The demo project contains a recording of *Eine kleine Nachtmusik* by Wolfgang Amadeus Mozart as performed by the Advent Chamber Orchestra, which is licensed under a [Creative Commons Attribution-Share Alike 2.0 Generic](https://creativecommons.org/licenses/by-sa/2.0/deed.en) license. For more details, see [the file's page on Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Mozart_-_Eine_kleine_Nachtmusik_-_1._Allegro.ogg).
