# NumEngine

NumEngine is a lightweight game engine/framework made to run on the numworks calculator. 

It allows you to set up a project directory, open it in Visual Studio Code, build the project, and run it directly on a calculator. This engine provides a simple C++ interface for developing games.

## Features

- **Open and manage project directories**: Easily set up or select a project folder.
- **Build projects**: Compile the project with `make` and generate a binary (`.bin`) or calculator package (`.nwa`).
- **Run projects on a calculator**: Directly deploy the built project onto a compatible calculator.
- **Open project in Visual Studio Code**: Launch your project in VSCode for quick edits.
- **View project folder**: Open the project folder in your system’s file explorer for easy access.

## Installation

To get started with NumEngine, you'll need to install several dependencies.
If you are on a **debian** based distribution (like ubuntu or linux mint) you can use these steps to install:

1. Clone the project and navigate to its directory:
    ```bash
    git clone https://github.com/riley0122/numengine
    cd numengine
    ```

2. Run the provided installation script:
    ```bash
    ./install-deps.sh
    ```

This script installs:

- GCC 13 and related tools
- ARM Embedded Toolchain (`arm-none-eabi-gcc`)
- OpenGL dependencies (`mesa-utils`, `libglew-dev`, `libglfw3-dev`, `libglm-dev`, etc.)
- Node.js and `nwlink`

### Manual installation (if needed)

If you prefer manual installation, ensure you have the following packages installed:

- `gcc-13`, `make`, `cmake`
- ARM Embedded Toolchain (`arm-none-eabi-gcc`)
- OpenGL-related libraries: 
  - `mesa-utils`
  - `libglu1-mesa-dev`
  - `freeglut3-dev`
  - `libglew-dev`
  - `libglfw3-dev`
  - `libglm-dev`
- Node.js and `npm` (for `nwlink` package)

To install ARM Embedded Toolchain manually:
```bash
TOOLCHAIN_URL="https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2?rev=78196d3461ba4c9089a67b5f33edf82a&hash=D484B37FF37D6FC3597EBE2877FB666A41D5253B"

wget $TOOLCHAIN_URL -O gcc-arm-none-eabi.tar.bz2
mkdir -p /opt/gcc-arm-none-eabi
tar -xvjf gcc-arm-none-eabi.tar.bz2 -C /opt/gcc-arm-none-eabi --strip-components=1
echo "export PATH=\$PATH:/opt/gcc-arm-none-eabi/bin" >> ~/.bashrc
source ~/.bashrc
```
## Usage

1. **Open NumEngine**:
    - Run `python3 main.py` to start the GUI.
    
2. **Set up a project**:
    - Click on "Open Project" and select the project folder.

3. **Open in VSCode**:
    - Click "Open in VSCode" to edit the project.

4. **Build the project**:
    - Click "Build Project" to compile the project.
    - The compiled files will appear in the `target/` directory.

5. **Run on calculator**:
    - Click "Run Project on Calculator" to compile and install the project on a calculator.

## Project Structure

- `src/`: Contains the C++ source files for the project.
  - `game`
    - `code.cpp`: Main logic for the program, which calls the `start()` and `update()` methods.
  - `meta`: Auto generated metadata files.
  - `numengine`: The numengine framework.
  - `eadk`: The interface used to call functions on the calculator.
  
- `Makefile`: Handles the build process for compiling and linking the project into a binary (`.bin`) and calculator package (`.nwa`).
- `CmakeLists.txt`: Handles building the project for running locally with openGL for development.

## Building and Running

- To **build** the project: `make`
- To **clean** the build files: `make clean`
- to **run** the project on the calculator: `make run`

## License

This project is licensed under the GNU General Public License v3.0. 

You are free to:
- Use this software for any purpose.
- Modify and adapt the software to your needs.
- Share the software and your modifications, under the same license.

