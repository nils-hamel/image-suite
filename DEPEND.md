## Packages and external dependencies installation

The following sections give the installation instructions for the required distribution packages and external dependencies for the supported platforms.

## Required distribution packages

### Ubuntu 16.04 LTS

```
sudo apt-get install build-essential
```

## OpenCV 4.0.1

### Ubuntu 16.04 LTS

This procedure creates a _Build_ directory in the user home directory to perform the compilation. It can be removed after installation.

```
mkdir ~/Build
cd ~/Build
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install build-essential libgtk2.0-dev libjpeg-dev libtiff5-dev libjasper-dev libopenexr-dev cmake python-dev python-numpy python-tk libtbb-dev libeigen3-dev yasm libfaac-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev libvorbis-dev libxvidcore-dev libx264-dev libqt4-dev libqt4-opengl-dev sphinx-common texlive-latex-extra libv4l-dev libdc1394-22-dev libavcodec-dev libavformat-dev libswscale-dev default-jdk ant libvtk5-qt4-dev
wget https://github.com/opencv/opencv/archive/4.0.1.tar.gz
tar -xvzf 4.0.1.tar.gz
cd opencv-4.0.1
mkdir build
cd build
cmake -D WITH_TBB=ON -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_V4L=ON -D INSTALL_C_EXAMPLES=ON -D INSTALL_PYTHON_EXAMPLES=ON -D BUILD_EXAMPLES=ON -D WITH_QT=ON -D WITH_OPENGL=ON -D WITH_VTK=ON .. -DCMAKE_BUILD_TYPE=RELEASE ..
make -j$(nproc)
sudo make install
```