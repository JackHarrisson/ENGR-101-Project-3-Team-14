#include "robot.hpp"
#include <algorithm>
#include "RobotView.hpp"
#include "RobotMovement.hpp"

int main(){
    cameraView.width = 150;
    cameraView.height = 100;
    cameraView.data = new char[cameraView.width * cameraView.height*3];
    cameraView.n_bytes = cameraView.width * cameraView.height*3;
    RobotMovement robotMovement{};

    if (connectNetwork()!=0){
        return -1;
    }
    std::string fileName = "i0.ppm";
    while(true){
        takePicture();
        SavePPMFile(fileName,cameraView);
        OpenPPMFile(fileName, cameraView);
        robotMovement.doCompletion();
        usleep(10000);
    } //while

} // main

