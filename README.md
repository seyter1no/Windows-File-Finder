# Windows file finder

## Getting Started

### Prerequisites

- GCC or g++ complier

### Installation & Building

Installation:

```sh
git clone https://github.com/seyter1no/Windows-File-Finder.git Search_file
```
### For build app:

First of all, if you're a Windows user, you need to have the MinGW-w64 toolchain. Here's what you should do if you don't have it:
1. You can download the latest version of the installer from the MSYS2 page or use this direct link to the installer(https://github.com/msys2/msys2-installer/releases/download/2024-01-13/msys2-x86_64-20240113.exe).

2. Run the installer and follow the instructions of the installation wizard. Please note that MSYS2 requires 64-bit Windows 8.1 or later.

3. In the installation wizard, select the desired folder for installation. Make a note of this directory for future reference. In most cases, the recommended directory is acceptable. The same goes for the step of customizing the Start menu shortcuts. Finally, make sure that Run MSYS2 now is checked and click Finish. This will open the MSYS2 terminal window.

4. In this terminal, install the MinGW-w64 toolkit by running the following command:
```sh
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
```
5. Accept the default number of packages in the toolkit group by pressing the Enter key.
6. Type Y when prompted to continue the installation.
7. Add the path to the MinGW-w64 bin folder to the Windows PATH environment variable by following the steps below:
    1. In the Windows search bar, type Settings to open the Windows Settings window.
    2. Find the Change environment variables for your account item.
    3. Under User variables, select the Path variable, and then click Edit.
    4. Select New and add the MinGW-w64 destination folder you recorded during the installation process to the list. If you used the default settings above, then this will be the path: C:\msys64\ucrt64\bin.
    5. Select OK to save the updated PATH. You will need to reopen any console windows for the new PATH location to be available.

If you have installed or already have the MinGW-w64 toolchain, you need to go to the desired disk and folder with the project through the console and write the following command:

```sh
make -f Makefile
```

Commands to open the desired disk and folder:

```sh
cd d:
cd Search_file
```
## Usage

The build folder contains the main.exe executable file, run it and you can search for the file you need.

You can also do this in the console using the following commands:

```sh
cd /build
./main
<search file>
```