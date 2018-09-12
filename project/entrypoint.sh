#!/usr/bin/env bash
/tmp/MediaIPC/build/bin/ffmpeg_streaming_consumer UE4Capture vp8 127.0.0.1:5000 unused &
cd /tmp/StreamingDemo && ue4 run -game -windowed -ResX=640 -ResY=360
