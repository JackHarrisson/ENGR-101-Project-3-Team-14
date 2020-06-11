class RobotMovement{
private:
    /**
    * Gets the error between middle of the row and middle of the white pixel
    */
    double getErrorFromWhitePixel(int rowIndex);
public:
    void followLine();
    void regulateMotor();

};
double RobotMovement::getErrorFromWhitePixel(int rowIndex){
    Pixel averageWhitePixel = RobotView::getAverageWhitePixel(rowIndex);
    int centralColumn = (int)(cameraView.width/2.0);
    return averageWhitePixel.column-centralColumn;
}
void RobotMovement::followLine(){
    regulateMotor();
}
void RobotMovement::regulateMotor(){
    const double speed = 20.0; //total speed scalar
    const double kp = 0.4; //constant coefficient for error
    double error;
    int bottomRowIndex = cameraView.height-1;
    if (!RobotView::rowHasWhitePixels(bottomRowIndex)){
        //if there are no white pixels
        error = 0;
    }else{
        error = getErrorFromWhitePixel(bottomRowIndex);
    }
    std::cout<<"Error: " << error <<std::endl;
    double speedDifference = kp*error;
    double rightMotorSpeed = speed + speedDifference;
    double leftMotorSpeed = speed - speedDifference;
    setMotors(rightMotorSpeed,leftMotorSpeed);
}