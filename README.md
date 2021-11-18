# dwm - dynamic window manager
----
dwm is an extremely fast, small, and dynamic window manager for X.

This is my build of arco-dwm from [ArcoLinux](https://arcolinux.com). I've replaced the keybindings with my own from [dwm-sudohero](https://github.com/ghsinfosec/dwm-sudohero) and added in the scratchpads patch.

## Requirements
------------
In order to build dwm you need the Xlib header files.


## Installation (ghsinfosec build)
------------
To install my build:
```
git clone https://github.com/ghsinfosec/dwm-arco-ghsinfosec.git
cd dwm-arco-ghsinfosec
sudo make clean install
```
You will also need to make symbolic links for the dmsearch and showkeys scripts in order for those keybindings to work with dmenu on my build:
```
cd dwm-arco-ghsinfosec/scripts
sudo ln -s $(pwd)/dmsearch /usr/local/bin/dmsearch
sudo ln -s $(pwd)/showkeys /usr/local/bin/showkeys
```
**Note:** You may need to edit the `showkeys` script depending on the location you installed dwm-arco-ghsinfosec. By default it is assumed that you have installed it in `$HOME`.


## Installation (DIY)
---
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):
```
    make clean install
```

## Running dwm
-----------
Add the following line to your .xinitrc to start dwm using startx:
```
    exec dwm
```
In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:
```
    DISPLAY=foo.bar:1 exec dwm
```
(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:
```
    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec dwm
```

## Configuration
-------------
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.
