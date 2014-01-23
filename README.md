x11
===
sudo apt-get install xvfb imagemagick libjpeg-dev

===
capture xvfb , convert to jpeg

/usr/bin/Xvfb :88 -screen 0 960x544x24+32 +extension Composite -nocursor -ac -fbdir ~/ &
xlogo
DISPLAY=:88 xlogo &
sudo apt-get install 
convert ./Xvfb_screen0 ~/screen.jpg

