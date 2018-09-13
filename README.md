UE4 Cloud Rendering Demo
========================

The code in this repository demonstrates performing cloud rendering using the NVIDIA Docker containers built by the [ue4-docker](https://github.com/adamrehn/ue4-docker) project and then streaming the results to a web browser via WebRTC. **Note that this code is provided as an example only and is NOT suitable for production use.**

## Contents

- [Prerequisites](#prerequisites)
- [Running the demo](#running-the-demo)
- [Enabling audio output (experimental)](#enabling-audio-output-experimental)
- [Frequently Asked Questions](#frequently-asked-questions)
- [Legal](#legal)


## Prerequisites

- Linux distribution with NVIDIA binary drivers satisfying the [NVIDIA Docker installation requirements](https://github.com/NVIDIA/nvidia-docker/wiki/Installation-(version-2.0)#prerequisites)
- NVIDIA graphics card satisfying the [NVIDIA Docker installation requirements](https://github.com/NVIDIA/nvidia-docker/wiki/Installation-(version-2.0)#prerequisites)
- [Docker](https://www.docker.com/) and [Docker Compose](https://docs.docker.com/compose/) 1.19.0 or newer
- [NVIDIA Docker](https://github.com/NVIDIA/nvidia-docker) 2.x
- [ue4-docker](https://github.com/adamrehn/ue4-docker)


## Running the demo

- Ensure you have built the NVIDIA Docker image `adamrehn/ue4-capture:4.20.2` using the build script from [ue4-docker](https://github.com/adamrehn/ue4-docker). Assuming you have all of the other prerequisites installed correctly, you can build the image using the following command:
  
  ```
  python3 build.py 4.20.2 --nvidia
  ```

- Run the appropriate shell script for the WebRTC server you want to use:
  
  - `./run-demo-janus.sh` for the example using the [Janus WebRTC Server](https://janus.conf.meetecho.com/)
  - *(Kurento and GStreamer native WebRTC examples will be added soon.)*

- Docker will build and run the images for the demo. This may take some time. You will know everything is built and running when you see the following lines in the log output:
  
  ```
  Received Control Block:
  
  videoFormat = Packed BGRA 8:8:8:8
  width = 640
  height = 360
  bytesPerPixel = 4
  frameRate = 30
  audioFormat = No audio
  ```

- Open the URL <http://127.0.0.1:8000/> in a web browser with VP8 support such as Mozilla Firefox or Google Chrome. The exact details of the page that loads will depend on which WebRTC server is being used:
  
  - When using Janus, you will see a copy of the [Janus Streaming plugin demo page](https://janus.conf.meetecho.com/streamingtest.html). Press the "Start" button to bring up the list of available streams, and select **"VP8/Opus live stream from UE4 and FFmpeg"** from the dropdown list. Finally, press the "Watch or Listen" button to activate the WebRTC stream. Once it is active, you should see the live video output from the UE4 demo project displayed.
  
  - *(Kurento and GStreamer native WebRTC examples will be added soon.)*


## Enabling audio output (experimental)

In order to enable audio support, the NVIDIA Docker container running UE4 needs to be given access to the audio devices from the host system. However, when UE4 is accessing host audio devices from inside a container, it has a nasty habit of attempting to lock them for exclusive access. This means that if other applications are already accessing the sound card then UE4 will be unable to open it for output, and vice versa. This is not an issue when the containers are running on a separate server to the client web browser, but the demo is limited to localhost only, which means a workaround is neccesary.

To enable audio output, perform the following steps:

- Create an ALSA loopback device by executing the command `sudo modprobe snd_aloop`. This provides a virtual audio device that UE4 can be instructed to use instead of the host's real audio output device. (This is actually the same solution used to provide an audio device when running the containers in a cloud VM that has no real audio output devices.)

- Uncomment the audio-related lines from the `docker-compose.yml` file for the WebRTC server being used:
  
  - For Janus, uncomment the lines in the file [servers/janus/docker-compose.yml](./servers/janus/docker-compose.yml).
  
  - *(Kurento and GStreamer native WebRTC examples will be added soon.)*

- Run the demo as per the instructions in the section above. This time, the log output should look like this:
  
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

- When the WebRTC stream is played back in the browser, you should hear the Mozart serenade *[Eine kleine Nachtmusik](https://en.wikipedia.org/wiki/Eine_kleine_Nachtmusik)* playing. (The audio file is the Creative Commons licensed [recording from the Wikipedia article](https://en.wikipedia.org/wiki/File:Mozart_-_Eine_kleine_Nachtmusik_-_1._Allegro.ogg).)


## Frequently Asked Questions

- **Q: Can the WebRTC video stream be viewed from a different machine to the host that is running the demo?**
  
  **A:** The demo is only configured for HTTP, not for HTTPS, which means WebRTC will only function over localhost due to security restrictions.

- **Q: Can the demo be modified to run under Windows or macOS?**
  
  **A:** No, because [NVIDIA Docker only supports Linux](https://github.com/NVIDIA/nvidia-docker/wiki/Frequently-Asked-Questions#platform-support) and the purpose of the demo is to illustrate Unreal Engine 4 running in an NVIDIA Docker container.


## Legal

Copyright &copy; 2018, Adam Rehn. Licensed under the MIT License, see the file [LICENSE](./LICENSE) for details.

The demo project contains a recording of *Eine kleine Nachtmusik* by Wolfgang Amadeus Mozart as performed by the Advent Chamber Orchestra, which is licensed under a [Creative Commons Attribution-Share Alike 2.0 Generic](https://creativecommons.org/licenses/by-sa/2.0/deed.en) license. For more details, see the [file page on Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Mozart_-_Eine_kleine_Nachtmusik_-_1._Allegro.ogg).
