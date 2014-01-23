x11
===

capture xvfb , convert to jpeg

sudo apt-get install xvfb
/usr/bin/Xvfb :88 -screen 0 960x544x24+32 +extension Composite -nocursor -ac -fbdir ~/ &
xlogo
DISPLAY=:88 xlogo &
sudo apt-get install imagemagick
convert ./Xvfb_screen0 ~/screen.jpg

