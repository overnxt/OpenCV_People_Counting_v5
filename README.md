# OpenCV_People_Counting_v5
A project based on Raspberry Pi 3 and OpenCV for supporting Smart Bus System
Many thanks to Andrews Sobral for his project: https://github.com/andrewssobral/simple_vehicle_counting
I have used his source code as a base structure for my project and added some features such as:
 - Whenever the counting system detect "objects", it will send a request to a local/internet server to update the "objects counter". (Qt Network)
 - Use smart pointers instead of opencv pointers :))
 - Add preprocessor for header files
 - Replace his Background Subtraction Algorithm with Opencv Background Subtraction Algorithm: MOG (opencv_contrib module) (This alogrithm works perfectly on my Raspberry Pi 3)
 
