#include "robot.hpp"
#include <algorithm>
#include "RobotView.hpp"
#include "RobotMovement.hpp"

int promptTask(){
    int taskType;
    std::cout<<"---CHOOSE TASK---"<<std::endl;
    std::cout<<"Enter '1' for Core"<<std::endl;
    std::cout<<"Enter '2' for Completion"<<std::endl;
    std::cout<<"Enter '3' for Challenge"<<std::endl;
    std::cout<<"Task: ";
    std::cin >> taskType;
    return taskType;
}

int main(){
    if (initClientRobot() != 0){
        std::cout<<"Error initializing robot"<<std::endl;
    }
    RobotMovement robotMovement{};
    int taskType = promptTask();
    while(true){
        takePicture();
        robotMovement.doTask(taskType);
        usleep(10000);
    } //while

} // main


