UE4 Cloud Rendering Demo
========================

The code in this repository demonstrates performing cloud rendering using the NVIDIA Docker containers built by the [ue4-docker](https://github.com/adamrehn/ue4-docker) project and then streaming the results to a web browser via WebRTC. **Note that this code is provided as an example only and is NOT suitable for production use.**

## Contents

- [Prerequisites](#prerequisites)
- [Running the demo](#running-the-demo)
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
  
  - When using Janus, you will see a copy of the [Janus Streaming plugin demo page](https://janus.conf.meetecho.com/streamingtest.html). Press the "Start" button to bring up the list of available streams, and select **"VP8 live stream from UE4 and FFmpeg"** from the dropdown list. Finally, press the "Watch or Listen" button to activate the WebRTC stream. Once it is active, you should see the live video output from the UE4 demo project displayed.
  
  - *(Kurento and GStreamer native WebRTC examples will be added soon.)*


## Frequently Asked Questions

- **Q: Can the WebRTC video stream be viewed from a different machine to the host that is running the demo?**
  
  **A:** The demo is only configured for HTTP, not for HTTPS, which means WebRTC will only function over localhost due to security restrictions.

- **Q: Can the demo be modified to run under Windows or macOS?**
  
  **A:** No, because [NVIDIA Docker only supports Linux](https://github.com/NVIDIA/nvidia-docker/wiki/Frequently-Asked-Questions#platform-support) and the purpose of the demo is to illustrate Unreal Engine 4 running in an NVIDIA Docker container.


## Legal

Copyright &copy; 2018, Adam Rehn. Licensed under the MIT License, see the file [LICENSE](./LICENSE) for details.
