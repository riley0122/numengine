# Install dependencies for debian systems.

echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
echo "@                             @"
echo "@   Installing dependencies   @"
echo "@                             @"
echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"

# Update repo
sudo apt-get update
# Building dependencies
if ! which gcc-13 >/dev/null; then
    sudo apt-get install cmake make gcc-13
fi
# OpenGL deps
sudo apt-get install mesa-utils livglu1-mesa-dev freeglut3-dev mesa-common-dev
sudo apt-get install libglew-dev libglfw3-dev libglm-dev
sudo apt-get install libau-dev libmpg123-dev
# GLFW
cd /usr/local/lib
sudo git clone https://github.com/glfw/glfw.git
cd glfw
sudo cmake .
sudo make
sudo make install

# Install ARM embedded toolchain
if which arm-none-eabi-cpp >/dev/null; then
    echo "Arm toolchain already installed."
else
    TOOLCHAIN_URL="https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2\?rev\=78196d3461ba4c9089a67b5f33edf82a\&hash\=D484B37FF37D6FC3597EBE2877FB666A41D5253B"

    if which wget >/dev/null; then
        echo "Using wget"
        sudo wget ${TOOLCHAIN_URL} -O gcc-arm-none-eabi.tar.bz2
    elif which curl >/dev/null; then
        echo "Using curl"
        sudo curl -L ${TOOLCHAIN_URL} --output gcc-arm-none-eabi.tar.bz2
    else
        echo "Neither curl nor wget are installed!"
        exit 1
    fi

    sudo mkdir -p ./gcc-arm-none-eabi
    sudo tar -xvjf gcc-arm-none-eabi.tar.bz2 -C ./gcc-arm-none-eabi  --strip-components=1

    sudo cp -r ./gcc-arm-none-eabi /opt/gcc-arm-none-eabi

    sudo echo "export PATH=\$PATH:/opt/gcc-arm-none-eabi/bin" >> ~/.bashrc
    if which zsh >/dev/null; then
        sudo echo "export PATH=\$PATH:/opt/gcc-arm-none-eabi/bin" >> ~/.zshrc
        source ~/.zshrc
    else
        source ~/.bashrc
    fi

    sudo rm ./gcc-arm-none-eabi.tar.bz2
    sudo rm -r ./gcc-arm-none-eabi
fi

# Install nwlink (and node if not installed)
if which npm >/dev/null; then 
    echo "npm is installed"
else
    sudo apt-get install nodejs
    sudo apt-get install npm
    sudo chown -R $(whoami) ~/.npm
fi

npm install nwlink -g

if ! which python3 >/dev/null; then
    sudo apt-get install python3 python3-pip python3-venv
fi

echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
echo "@                             @"
echo "@          Finished!          @"
echo "@                             @"
echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
echo ""
echo "To finalise the install, make sure to start a new terminal or source ~/.bashrc or ~/.zshrc"
