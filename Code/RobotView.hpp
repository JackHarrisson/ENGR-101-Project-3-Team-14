struct Pixel{
    int row, column,red,green,blue,luminosity;
    Pixel(int row,int column,int red,int green,int blue,int luminosity){
        this->row=row;
        this->column=column;
        this->red=red;
        this->green=green;
        this->blue=blue;
        this->luminosity=luminosity;
    }
    Pixel(){
    }
    bool isWhite() const{
        return (luminosity == 255);
    }
    bool isRed() const{
        return (red == 255 && green!=255 && blue!=255);
    }

};

class RobotView{
public:
    static Pixel getPixel(int row, int column);
    static bool hasWhitePixels(std::vector<Pixel> pixels);
    static bool hasRedPixels(std::vector<Pixel> pixels);
    /** Gets the middle pixel from the white blob at row specified by parameter index*/
    static std::vector<Pixel> getRow(int rowIndex);
    static std::vector<Pixel> getColumn(int columnIndex);
    static bool hasWhitePath(std::vector<Pixel> pixels);
    static Pixel averagePixel(std::vector<Pixel> pixels);
    static std::vector<Pixel> getWhitePixels(std::vector<Pixel> pixels);
    static int rowsBetweenPixel(Pixel pixel); //the rows between centre of robot, and parameter in-view pixel
    static std::vector<Pixel> getLeftEdge();
    static std::vector<Pixel> getRightEdge();
};
Pixel RobotView::getPixel(int row, int column){
    int red = get_pixel(cameraView,row,column,0);
    int green = get_pixel(cameraView,row,column,1);
    int blue = get_pixel(cameraView,row,column,2);
    int luminosity = get_pixel(cameraView,row,column,3);
    Pixel pixel = Pixel(row,column,red,green,blue,luminosity);
    return pixel;
}

bool RobotView::hasWhitePixels(std::vector<Pixel> pixels){
    return std::any_of(pixels.begin(),pixels.end(),[](Pixel p){return p.isWhite();});
}
bool RobotView::hasRedPixels(std::vector<Pixel> pixels){
    return std::any_of(pixels.begin(),pixels.end(),[](Pixel p){return p.isRed();});
}

/**Checks if parameter group of pixels has a white path*/
bool RobotView::hasWhitePath(std::vector<Pixel> pixels){
    bool hasWhitePixel = false;
    //checks if the group of white pixels actually ends
    //- needed to prevent false positives
    for (Pixel& pixel:pixels){
        if (pixel.isWhite())
            hasWhitePixel=true;
        else if (hasWhitePixel) {
            return true;
        }
    }
    return false;
}

std::vector<Pixel> RobotView::getWhitePixels(std::vector<Pixel> pixels){
    std::vector<Pixel> whitePixels;
    std::copy_if(pixels.begin(),pixels.end(),std::back_inserter(whitePixels),[](Pixel p){return p.isWhite();});
    return whitePixels;
}
Pixel RobotView::averagePixel(std::vector<Pixel> pixels){
    double columnSum = 0.0;
    double rowSum =0.0;
    for (Pixel pixel:pixels){
        columnSum+=pixel.column;
        rowSum+=pixel.row;
    }
    int averageRow = (int)(rowSum/pixels.size());
    int averageColumn = (int)(columnSum/pixels.size());
    return getPixel(averageRow,averageColumn);
}

std::vector<Pixel> RobotView::getLeftEdge() {
    return getColumn(0);
}
std::vector<Pixel> RobotView::getRightEdge() {
    return getColumn(cameraView.width-1);
}
std::vector<Pixel> RobotView::getRow(int rowIndex){
    std::vector<Pixel> pixels;
    for (int column =0;column<cameraView.width;column++)
        pixels.emplace_back(getPixel(rowIndex,column));
    return pixels;
}
std::vector<Pixel> RobotView::getColumn(int columnIndex){
    std::vector<Pixel> pixels;
    for (int row =0;row<cameraView.height;row++)
        pixels.emplace_back(getPixel(row,columnIndex));
    return pixels;
}
int RobotView::rowsBetweenPixel(Pixel pixel) {
    const int CAMERA_FORWARD = 100; //distance between robot centre and centre of camera FoV
    int distanceFromFoV = (int)(CAMERA_FORWARD - cameraView.height/2.0); //distance between robot centre and bottom edge
    return (distanceFromFoV)+(cameraView.height-pixel.row);
}
