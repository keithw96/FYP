Steps to set up and build the project on a raspberry pi

Enable OpenGL ES drivers
 -type sudo raspi-config
 -go to G7-Advanced 
 -A8-GL Driver
 -set to G3 GL (FULL KMS)
 
 Build and install SFML 2.5
  -Download SFML Source: https://github.com/SFML/SFML.git
  -Download dependancies: sudo apt-get install cmake libflac-dev libogg-dev libvorbis-dev libopenal-dev libjpeg8-dev libfreetype6-dev libudev-dev libraspberrypi-dev
  -cd to directory and build using cmake
  -cmake -DSFML_RPI=1 -DEGL_INCLUDE_DIR=/opt/vc/include -DEGL_LIBRARY=/opt/vc/lib/libbrcmEGL.so -DGLES_INCLUDE_DIR=/opt/vc/include -DGLES_LIBRARY=/opt/vc/lib/libbrcmGLESv2.so
  -sudo make install
  
 Run Project
 -cd to $projectdirector/Build
 -sudo ./FYP
