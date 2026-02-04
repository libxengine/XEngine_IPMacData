[中文](README.md) || [English](README.en.md)  
# XEngine_IPMac
This repository has development and master branches. If you want to use the code, please use the master branch.  
As long as the repository is not paused, it will be continuously maintained and developed. Please use it with confidence.

## Introduction
IP address and MAC address ownership query  

## Software Features
1. Support for IP address ownership query
2. Support for MAC address vendor query
3. Provides database interface methods without restricting the usage language

## Installation Guide

#### XEngine Environment
To compile our examples, you need the XEngine environment, version V9.x or above. You can refer to its README document for installing XEngine.  
GITEE: https://gitee.com/libxengine/libxengine  
GITHUB: https://github.com/libxengine/libxengine

###### Quick Deployment
Clone the repository:  
`git clone https://gitee.com/libxengine/libxengine.git`  
or  
`git clone https://github.com/libxengine/libxengine.git`  

For Windows, execute the `XEngine_WINEnv.bat` script.  
For Linux, execute: `sudo ./XEngine_LINEnv.sh -i 3`  
For macOS, execute: `./XEngine_LINEnv.sh -i 3`

#### Windows Compilation
You can directly use Visual Studio (VS).

#### Linux or macOS Compilation
Execute the following commands in the `XEngine_Source` directory:  
`make` to compile  
`make FLAGS=InstallAll` to install the library  
`make FLAGS=CleanAll` to clean the compilation

## Data Structures
#### IP Data Structure
Please refer to the data source.

#### MAC Data Structure
csv,Please refer to the data source.

## Usage Instructions

1. Switch to the MASTER branch
2. Download the code
3. Compile
4. Install
5. Run

## Directory Structure
- XEngine_DBFile    db file 
- XEngine_Source    Source code directory structure 

## Contributing
We hope everyone can contribute more code.

1. Fork this repository
2. Create a new `Feat_xxx` branch
3. Submit your code
4. Create a Pull Request

## Follow Us
If you find this software helpful, please give us a STAR.

## Submitting Issues

If you have any questions or find bugs and have suggestions, you can submit them in the issues section.

## Data Sources
#### IP Database
@geolite2 uptime:2026.02.04

#### MAC Database
@MACLookup uptime:2026.02.04
