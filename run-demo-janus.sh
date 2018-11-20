#!/usr/bin/env bash
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
export HOST_UID=`id -u`
cd "$SCRIPT_DIR/servers/janus" && docker-compose up
