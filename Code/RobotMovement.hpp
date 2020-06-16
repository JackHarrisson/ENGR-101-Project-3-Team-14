
#include <math.h>
class RobotMovement{
public:
    void doTask(int task);
private:
    void followLine();
    void regulateMotor();
    void rotate(const double& degrees);
    void doCore();
    void doCompletion();
    void doChallenge();
    void goTo(int distanceAhead);
    void turnCheck();
    void turnLeft();
    void turnRight();
    void moveDistance(double distance);
    void initialise();
    double direction = 0.0; //in degrees;
    const double WHEEL_RADIUS = 8.0;
    const double ROBOT_WIDTH = 30.0;
    double speed = 20.0; //total speed scalar
    bool initialised = false;
    void turnAroundWall();
};
void RobotMovement::doTask(int task){
    if (task == 1)
        doCore();
    else if (task == 2)
        doCompletion();
    else if (task == 3)
        doChallenge();
    else
        std::cout<<"Task Not Recognised"<<std::endl;
}
void RobotMovement::doChallenge(){
    if (!initialised)
        initialise();
    else
        turnCheck();
}
void RobotMovement::initialise(){
    goTo(160); //moves 300 pixels
    initialised = true;
}

void RobotMovement::turnCheck(){
    std::vector<Pixel> bottomRow = RobotView::getRow(cameraView.height-1);
    std::vector<Pixel> bottomRowLeft;
    std::copy_if(bottomRow.begin(),bottomRow.end(),std::back_inserter(bottomRowLeft),
            [](Pixel p){return p.column < cameraView.width/2;});

    Pixel bottomRedPixel = bottomRow[cameraView.width/2];

    if (bottomRedPixel.isRed()){
        moveDistance(10);
        setMotors(0,0);
        turnRight();
        setMotors(speed,speed);
    }
    else if (!RobotView::hasRedPixels(bottomRowLeft)){
        turnAroundWall();
    }
    else{
        setMotors(speed,speed);
    }

}

void RobotMovement::turnAroundWall(){
    moveDistance(80);
    turnLeft();
    moveDistance(80);
    turnLeft();
}
void RobotMovement::moveDistance(double distance){
    double motorSpeed = speed;
    double pixelSpeed = (motorSpeed*M_PI*WHEEL_RADIUS)/180.0;
    while (distance > 0){
        if (distance - pixelSpeed < 0) {
            motorSpeed = (distance * 180.0) / (M_PI * WHEEL_RADIUS);
            pixelSpeed = (motorSpeed*M_PI*WHEEL_RADIUS)/180.0;
        }
        setMotors(motorSpeed,motorSpeed);
        setMotors(0,0);
        distance-=pixelSpeed;
        usleep(10000);
    }
}
void RobotMovement::doCore(){
    followLine();
}
void RobotMovement::doCompletion() {
    std::vector<Pixel> leftEdge = RobotView::getLeftEdge();
    std::vector<Pixel> rightEdge = RobotView::getRightEdge();
    if (RobotView::hasWhitePath(leftEdge) || RobotView::hasWhitePath(rightEdge)){
        Pixel averageWhitePixel;
        bool turnRight = RobotView::hasWhitePath(rightEdge);
        if (turnRight){
            averageWhitePixel = RobotView::averagePixel(RobotView::getWhitePixels(rightEdge));
        }else{
            averageWhitePixel = RobotView::averagePixel(RobotView::getWhitePixels(leftEdge));
        }
        int distanceAhead = RobotView::rowsBetweenPixel(averageWhitePixel);
        goTo(distanceAhead);
        if (turnRight)
            this->turnRight();
        else
            this->turnLeft();
    }
    else
        followLine();
}
void RobotMovement::goTo(int distance) {
    double motorSpeed = (distance*180.0)/(M_PI*WHEEL_RADIUS); //the motor speed needed to be able to travel parameter distance in one tick
    setMotors(motorSpeed,motorSpeed);
    setMotors(0,0);
}

void RobotMovement::followLine(){
    regulateMotor();
}
void RobotMovement::turnLeft(){
    rotate(-90.0);
}
void RobotMovement::turnRight(){
    rotate(90.0);
}
void RobotMovement::rotate(const double& degrees){
    double leftMotorSpeed = (degrees*ROBOT_WIDTH)/(2.0*WHEEL_RADIUS);
    double rightMotorSpeed = -leftMotorSpeed;
    setMotors(leftMotorSpeed,rightMotorSpeed);
    direction+=degrees;
    setMotors(0,0);
}

void RobotMovement::regulateMotor(){
    const double kp = 0.3; //constant coefficient for error
    double error;
    int bottomRowIndex = cameraView.height-1;
    std::vector<Pixel> bottomRow = RobotView::getRow(bottomRowIndex);
    if (!RobotView::hasWhitePixels(bottomRow)){
        //if there are no white pixels
        error = 0;
    }else{
        Pixel averageWhitePixel = RobotView::averagePixel(RobotView::getWhitePixels(bottomRow));
        int middleColumn = (int)(cameraView.width/2.0);
        error = averageWhitePixel.column-middleColumn;
    }
    double speedDifference = kp*error;
    double rightMotorSpeed = speed + speedDifference;
    double leftMotorSpeed = speed - speedDifference;
    setMotors(rightMotorSpeed,leftMotorSpeed);
}
