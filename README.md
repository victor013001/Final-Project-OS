# Final-Project-OS

The project is focus on test the RIOS OS on an ESP32 for the OS course. 

## Requirements

To run the project is required a Linux distribution or macOS or WSL, the RIOS OS, an ESP32 and the Toolchain for the ESP32.

To get the RIOT operating system in the version that was used for the development of the project use the following commands
```bash
  cd $HOME
```
```bash
  git clone https://github.com/RIOT-OS/RIOT.git
```
```bash
  git checkout 2021.04-branch
```

To clone this repository use the following commands

```bash
  cd $HOME/RIOT
```
```bash
  git clone https://github.com/victor013001/Final-Project-OS.git
```

To get the Toolchains for the ESP32 use the following commands

```bash
  sudo apt install build-essential cppcheck curl doxygen git graphviz make pcregrep python python3 python3-flake8 unzip wget
```
```bash
  mkdir -p $HOME/esp
```
```bash
  cd $HOME/esp
```
```bash
  git clone https://github.com/gschorcht/xtensa-esp32-elf.git
```
```bash
  export PATH=$PATH:$HOME/esp/xtensa-esp32-elf/bin
```
```bash
  cd $HOME/esp
```
```bash
  git clone https://github.com/espressif/esp-idf.git
```
```bash
  cd esp-idf
```
```bash
  git checkout f198339ec09e90666150672884535802304d23ec
```
```bash
  git submodule init
```
```bash
  git submodule update
```
```bash
  export ESP32_SDK_DIR=$HOME/esp/esp-idf
```
```bash
  sudo apt install python3-pip
```
```bash
  sudo pip install pyserial
```

To make environment variables permanent

```bash
  gedit ~/.profile
```

at the end of the file write

```bash
  export ESP32_SDK_DIR=$HOME/esp/esp-idf
  export PATH=$PATH:$HOME/esp/xtensa-esp32-elf/bin
```

## Flashing ESP32

The project can be compile and flash to the ESP32 using the following command
```bash
    make flash BOARD=esp32-wroom-32 -C [project_location]/Final-Project-OS/RGB
```
```bash
    make flash BOARD=esp32-wroom-32 -C [project_location]/Final-Project-OS/Threads
```

## Authors
This project is developed by:

- Jhonatan Tamayo Morales
- Kieffer Alexander Páez
- Victor Manuel Osorio Garcia