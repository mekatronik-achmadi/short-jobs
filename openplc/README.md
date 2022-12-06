# OpenPLC

## Description

OpenPLC is an open-source Programmable Logic Controller that is based on easy to use software.

**NOTE:** This tutorial show some how to and example on OpenPLC running in ArchLinux.
By default, original project intended for APT and YUM based distro.
This tutorial should be reproducible on Arch based distro like Manjaro, EndeavorOS, etc.

For Windows or other distro, do your own work. Sorry

**Assumption**:
- You know how to using terminal emulator program in your distro OS
- You are familiar with Arch Build System and PKGBUILD in general
- You have sufficient disk and decent internet connection

## Contents
- [Runtime](#runtime)
    - [Docker](#docker)
        - [Setup Docker](#setup-docker)
        - [Install Image](#install-image)
        - [Running Image](#running-image)
    - [RaspberryPi]()
- [Editor]()
    - [Install]()
    - [Running]()

## Runtime

Runtime will be act as virtual PLC unit for the editor.
For convinience, this tutorial only show example using docker.
It may updated to include RaspberryPi in future.

### Docker

#### Setup Docker

First, if needed, update and upgrade your Arch package database using command:

```sh
sudo pacman -Syu --noconfirm
```

Then install git and docker package using command:

```sh
sudo pacman -S git docker
```

Next, add yourself into **docker** group using command:

```sh
sudo groupadd -f docker
sudo gpasswd -a $USER docker
```

you may need reboot or relogin after this.

Then for starting up docker, run command:

```sh
sudo systemctl enable docker
sudo systemctl start docker
```

#### Install Image

First, clone the runtime repository using command

```sh
git clone https://github.com/thiagoralves/OpenPLC_v3.git
```

To build docker image for OpenPLC runtime in a folder, use command:

```sh
docker build -t openplc:v3 OpenPLC_v3/
```

Wait for a while as docker image being downloaded and installed.
You can grab your favorite coffe and healthy salad as snacks.

Next, if you got message like:

```sh
Successfully built f18fa3f3d840
Successfully tagged openplc:v3
```

It means docker image build process is completed

#### Running Image

Next, you can run docker image using command

```sh
docker run -it --rm --privileged -p 8080:8080 -v /dev/ttyACM0:/dev/ttyACM0 openplc:v3
```
