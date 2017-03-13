X-Ray Engine 1.6 expansion
==========================

This repository contains X-Ray Engine sources based on version 1.6.02.
The original engine is used in S.T.A.L.K.E.R. Call of Pripyat game released by GSC Game World.

It is a place to share ideas on what to implement, gather people that want to work on the engine,
and work on the source code.

Changelist is available in [wiki](https://github.com/OpenXRay/xray-16/wiki/Changes).

Build instructions: [doc/howto/build.txt](doc/howto/build.txt)

If you find a bug or have an enhancement request, file an [Issue](https://github.com/openxray/xray-16/issues).

Pull requests appreciated! However, the following things should be taken into consideration:
* We want to keep the game as close as possible to the vanilla game, so instead of introducing new gameplay features,
  consider adding non-gameplay features, fixing bugs, improving performance and code quality
* Major changes should be discussed before implementation
* Follow the [procedures](doc/procedure)

Be advised that this project is not sanctioned by GSC Game World in any way – and they remain the copyright holders
of all the original source code.

#Linux
##Linux dependencies
###Ubuntu:
```
sudo apt-get install libsdl2-dev libtheora-dev libvorbis-dev libfreeimage-dev liblua5.1-0-dev libssl-dev liblzo2-dev libjpeg-dev libncurses5-dev lua5.1
```
##Linux build instructions
```
git submodule init
git submodule update
cd src && mkdir build && cd build
cmake ..
make
```
##TODO
* Resolve xrEngine linking issues
* Port filesystem API to Posix (memory mapping etc.)
* Port ttapi to Posix 
* Port xrInput to SDL
* Implement SDL main loop (in device.cpp?)
* Get rid of D3D types
* Implement OpenAl Soft
* Network?
