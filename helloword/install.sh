#!/bin/bash
echo "Currently supports only Ubuntu"
echo "Install gnu"
echo "Update.."
sudo apt update
echo "Prepare repo.."
sudo apt-get install python-software-properties -y
sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
echo "installing gcc.."
sudo apt-get install gcc-4.8 -y
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 50
echo "installing g++.."
sudo apt-get install g++-4.8 -y
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8 50
echo "installing git.."
sudo apt-get install git -y
echo "GNU Installed"
