sudo mkdir /usr/include/agl/motion
sudo cp -Rap *.h /usr/include/agl/motion/
make release
sudo cp -Rap ../lib/*.so /usr/lib/
