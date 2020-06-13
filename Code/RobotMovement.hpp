class RobotMovement{
public:
    void followLine();
    void regulateMotor();
};

void RobotMovement::followLine(){
    regulateMotor();
}
void RobotMovement::regulateMotor(){
    const double speed = 20.0; //total speed scalar
    const double kp = 0.4; //constant coefficient for error
    double error;
    int bottomRowIndex = cameraView.height-1;
    std::vector<Pixel> bottomRow = RobotView::getRow(bottomRowIndex);
    if (!RobotView::hasWhitePixels(bottomRow)){
        //if there are no white pixels
        error = 0;
    }else if (RobotView::getRowWhiteness(bottomRow) > 0.8) {
        //if the bottom row is white, the robot is at a T-intersection, and it should turn left
        std::cout<<"White pixels"<<std::endl;
        int middleColumn = (int)(cameraView.width/2.0);
        error = -middleColumn;
    }else{
        Pixel averageWhitePixel = RobotView::averagePixel(RobotView::getWhitePixels(bottomRow));
        std::cout<<"White pixels"<<std::endl;
        int middleColumn = (int)(cameraView.width/2.0);
        error = averageWhitePixel.column-middleColumn;
    }
    std::cout<<"Error: " << error <<std::endl;
    double speedDifference = kp*error;
    double rightMotorSpeed = speed + speedDifference;
    double leftMotorSpeed = speed - speedDifference;
    setMotors(rightMotorSpeed, leftMotorSpeed);
}
