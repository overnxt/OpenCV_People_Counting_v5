# OpenCV_People_Counting_v5
A project based on Raspberry Pi 3 and OpenCV for supporting Smart Bus System
Many thanks to Andrews Sobral for his project: https://github.com/andrewssobral/simple_vehicle_counting
I have used his source code as a base structure for my project and added some features such as:
 - Whenever the counting system detect "objects", it will send a request to a local/internet server to update the "objects counter". (Qt Network)
 - Use smart pointers instead of opencv pointers :))
 - Add preprocessor for header files
 - Replace his Background Subtraction Algorithm with Opencv Background Subtraction Algorithm: MOG (opencv_contrib module) (This alogrithm works perfectly on my Raspberry Pi 3)
## Dependencies
 - OpenCV 3 with extra modules from https://github.com/opencv/opencv and https://github.com/opencv/opencv_contrib 
 - Basic requirement for building C++ Modern Applications (Considering GNU G++ version that supports C++11/14 feature):
	1. Debian/Ubuntu (apt-get): sudo apt-get install build-essential libgl1-mesa-dev
	2. Fedora/RHEL/CentOS (yum): sudo yum groupinstall "C Development Tools and Libraries" 
				     sudo yum install mesa-libGL-devel
 - Qt libraries : qt5-default (for qmake and common libqt5), libqt5core5, libqt5network5
## Build commands
 - qmake
 - make
## Screenshots
![](screenshots/Screenshot_20180812_120441.png)
![](screenshots/Screenshot_20180812_120515.png)

```
 ____ _____ ___ _____    ___   ___     ____   ___  _  ___  
|  _ \_   _|_ _|_   _|  / _ \ ( _ )   |___ \ / _ \/ |( _ ) 
| |_) || |  | |  | |   | | | |/ _ \     __) | | | | |/ _ \ 
|  __/ | |  | |  | |   | |_| | (_) |   / __/| |_| | | (_) |
|_|    |_| |___| |_|    \___/ \___/___|_____|\___/|_|\___/ 
                                 |_____|                   
 _____ _     _             ___                         _____                  
|_   _| |__ (_) ___ _   _ / _ \ _   _  __ _ _ __   __ |_   _|   _  __ _ _ __  
  | | | '_ \| |/ _ \ | | | | | | | | |/ _` | '_ \ / _` || || | | |/ _` | '_ \ 
  | | | | | | |  __/ |_| | |_| | |_| | (_| | | | | (_| || || |_| | (_| | | | |
  |_| |_| |_|_|\___|\__,_|\__\_\\__,_|\__,_|_| |_|\__, ||_| \__,_|\__,_|_| |_|
                                                  |___/                       
 _   _ _ _  _   ____   ____ ____ _   _ _ _____  __   
| \ | / | || | |  _ \ / ___/ ___| \ | / |___ / / /_  
|  \| | | || |_| | | | |  | |   |  \| | | |_ \| '_ \ 
| |\  | |__   _| |_| | |__| |___| |\  | |___) | (_) |
|_| \_|_|  |_| |____/ \____\____|_| \_|_|____/ \___/ 
 ```                                                    
