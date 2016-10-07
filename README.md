# Livetube IO Server

[![Current Song](https://livetubeio-16323.appspot.com/channels/TGl2ZXR1YmVpby9zZXJ2ZXI=)](https://livetube.io/Livetubeio/server) [![Build Status](https://travis-ci.org/Livetubeio/server.svg?branch=master)](https://travis-ci.org/Livetubeio/server)

Remote control & sync
YouTube videos

Supercharge your GitHub repository.
Synchronize Videos with your friends
Remote control your channel.

## Dependencies:
```bash
apt-get install -y cmake build-essential curl libgoogle-glog-dev libjansson-dev libjsoncpp-dev libjsoncpp1 libcurl4-gnutls-dev libgflags-dev openssl libssl-dev

ln -sf /usr/include/jsoncpp/json /usr/include/json
```
## Compilation:
```bash
cmake . && make -j 4
```