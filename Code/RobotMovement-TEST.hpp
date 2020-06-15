//#define M_PI 3.14159265359
#include <math.h>
class RobotMovement{
public:
    void followLine();
    void regulateMotor();
    void rotate(const double& degrees);
    void doCompletion();
    void doChallenge();
    void goTo(int distanceAhead);
private:
    void turnCheck();
    void turnLeft();
    void turnRight();
    void moveDistance(double distance);
    void initialise();
    double direction = 0.0; //in degrees;
    const double WHEEL_RADIUS = 8.0;
    const double ROBOT_WIDTH = 30.0;
    double robotX = 10.0; //robot centre x-coordinate, initial value 10.0
    double robotY = 100.0; //robot centre y-coordinate, initial value 100.0
    double speed = 20.0; //total speed scalar
    bool initialised = false;
    bool ensureTurn = false;

    void turnAroundWall();
};
void RobotMovement::doChallenge(){
	std::vector<Pixel> bottomRow = RobotView::getRow(cameraView.height-1);
	std::cout<<"Row contains red: "<<std::any_of(bottomRow.begin(),bottomRow.end(),[](Pixel p){return p.red==255;})<<std::endl;
	setMotors(speed,speed);
}

void RobotMovement::initialise(){
    moveDistance(150);
    initialised = true;
}
void RobotMovement::turnCheck() {
	int bottomRowIndex = cameraView.height-1;
	
	std::vector<unsigned char> bottomRowRedValues; //red values of bottom row
	std::vector<Pixel> bottomRow = RobotView::getRow(bottomRowIndex);
	
	for (int col =0;col<cameraView.width;col++){
		unsigned char redValue = get_pixel(cameraView,bottomRowIndex,col,0);
		bottomRowRedValues.push_back(redValue);
    }
    
    std::cout<<"Has Red Pixels: "<<RobotView::hasRedPixels(bottomRow)<<std::endl;
    if (std::none_of(bottomRowRedValues.begin(),bottomRowRedValues.end(),[](unsigned char val){return val == 255;})){
		setMotors(0,0);
        std::cout<<"----------------------"<<std::endl;
        for (int i=0;i<bottomRow.size();i++){
            std::cout<<"Column " << i<<": ("<<bottomRow[i].red<<", "<<bottomRow[i].green<<", "<<bottomRow[i].blue<<", "<<bottomRow[i].luminosity<<")"<<std::endl;
        }
        std::cout<<"----------------------"<<std::endl;
        usleep(99999999);
    }
    setMotors(speed,speed);
}

void RobotMovement::turnAroundWall(){
    moveDistance(160);
    turnLeft();
    moveDistance(80);
    turnLeft();
    moveDistance(100);
}
void RobotMovement::moveDistance(double distance){
	std::cout<<"Moving.. "<<std::endl;
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
void RobotMovement::doCompletion() {
    std::vector<Pixel> leftEdge = RobotView::getLeftEdge();
    std::vector<Pixel> rightEdge = RobotView::getRightEdge();
    if (RobotView::hasWhitePath(leftEdge) || RobotView::hasWhitePath(rightEdge)){
        Pixel averageWhitePixel;
        bool turnLeft = RobotView::hasWhitePath(leftEdge);
        if (turnLeft){
            averageWhitePixel = RobotView::averagePixel(RobotView::getWhitePixels(leftEdge));
            turnLeft=true;
        }else{
            averageWhitePixel = RobotView::averagePixel(RobotView::getWhitePixels(rightEdge));
            turnLeft = false;
        }
        int distanceAhead = RobotView::rowsBetweenPixel(averageWhitePixel);
        goTo(distanceAhead);
        if (turnLeft)
            this->turnLeft();
        else
            this->turnRight();
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
    const double kp = 0.4; //constant coefficient for error
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
    std::cout<<"Error: " << error <<std::endl;
    double speedDifference = kp*error;
    double rightMotorSpeed = speed + speedDifference;
    double leftMotorSpeed = speed - speedDifference;
    setMotors(rightMotorSpeed,leftMotorSpeed);
}
