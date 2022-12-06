# OpenPLC

## Description

OpenPLC is an open-source Programmable Logic Controller that is based on easy to use software.

**NOTE:** This tutorial show some how to and example on OpenPLC running in ArchLinux.
By default, original project intended for APT and YUM based distro.
This tutorial should be reproducible on Arch based distro like Manjaro, EndeavorOS, etc.

For Windows or other distro, do your own work. Sorry

**Assumptions**:
- You know how to using terminal emulator program in your distro OS
- You are familiar with Arch Build System and PKGBUILD in general
- You have sufficient disk and decent internet connection

## Contents
- [Runtime](#runtime)
    - [Docker](#docker)
        - [Setup Docker](#setup-docker)
        - [Install Image](#install-image)
        - [Running Image](#running-image)
    - [RaspberryPi](#raspberrypi)
- [Editor](#editor)
    - [Install Editor](#install-editor)
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

### RaspberryPi

Coming Soon. Maybe

## Editor

OpenPLC Editor is an IDE capable of creating programs for the OpenPLC Runtime.

### Install Editor

First, you may need install **base-devel** group using command:

```sh
sudo pacman -S base-devel
```

Next, use this PKGBUILD to install the editor

```
pkgname=openplc-editor
pkgver=r195.64b3e0a
pkgrel=1
pkgdesc="IDE capable of creating programs for the OpenPLC Runtime"
arch=('any')
url="https://github.com/thiagoralves/OpenPLC_Editor"
license=('Custom')
depends=('python-wxpython' 'python-pyserial' 'python-zeroconf'
    'python-numpy' 'python-matplotlib' 'python-lxml' 'python-pyro')
makedepends=('git')
options=('!strip')
optdepends=('docker: recommended runtime format')
source=("${pkgname}::git+${url}.git")
sha256sums=('SKIP')

pkgver() {
	cd ${srcdir}/${pkgname}
	printf "r%s.%s" "$(git rev-list --count HEAD)" "$(git rev-parse --short HEAD)"
}

build() {
	cd ${srcdir}/${pkgname}

    cd matiec/
    autoreconf -i
    ./configure
    make -j$(nproc) -s
}

package() {
	cd ${srcdir}/${pkgname}

    cd matiec
    cp -f ./iec2c ../editor/arduino/bin/

    cd ../
    mkdir -p ${pkgdir}/opt/openplc/
    cp -rf editor/ ${pkgdir}/opt/openplc/
    mkdir -p ${pkgdir}/opt/openplc/matiec/
    cp -rf matiec/lib/ ${pkgdir}/opt/openplc/matiec/

    mkdir -p ${pkgdir}/usr/bin/
    echo "python /opt/openplc/editor/Beremiz.py" > ${pkgdir}/usr/bin/openplc_editor.sh
    chmod a+x ${pkgdir}/usr/bin/openplc_editor.sh

    mkdir -p ${pkgdir}/usr/share/applications/
    echo "[Desktop Entry]
Name=OpenPLC Editor
Categories=Development;
Exec=openplc_editor.sh
Icon=/opt/openplc/editor/images/brz.png
Type=Application
Terminal=false" > ${pkgdir}/usr/share/applications/OpenPLC_Editor.desktop
}
```
