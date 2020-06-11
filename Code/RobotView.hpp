
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
    bool isWhite() const{
        return (luminosity == 255);
    }
};
class RobotView{
public:
    static Pixel getPixel(int row, int column);
    static bool rowHasWhitePixels(int rowIndex);
    /** Gets the middle pixel from the white blob at row specified by parameter index*/
    static Pixel getAverageWhitePixel(int rowIndex);
    static std::vector<Pixel> getRow(int rowIndex);
};
Pixel RobotView::getPixel(int row, int column){
    int red = get_pixel(cameraView,row,column,0);
    int green = get_pixel(cameraView,row,column,1);
    int blue = get_pixel(cameraView,row,column,2);
    int luminosity = get_pixel(cameraView,row,column,3);
    Pixel pixel = Pixel(row,column,red,green,blue,luminosity);
    return pixel;
}
bool RobotView::rowHasWhitePixels(int rowIndex){
    std::vector<Pixel> row = getRow(rowIndex);
    return std::any_of(row.begin(),row.end(),[](Pixel p){return p.isWhite();});
}
Pixel RobotView::getAverageWhitePixel(int rowIndex){
    std::vector<Pixel> row = getRow(rowIndex);
    double columnSum = 0.0;
    int whitePixels = 0;
    for (Pixel pixel:row){
        if (pixel.isWhite()){
            columnSum+=pixel.column;
            whitePixels++;
        }
    }
    int averageColumn = (int)(columnSum/whitePixels);
    Pixel averageWhitePixel = getPixel(rowIndex,averageColumn);
    return averageWhitePixel;
}
std::vector<Pixel> RobotView::getRow(int rowIndex){
    std::vector<Pixel> pixels;
    for (int column =0;column<cameraView.width;column++)
        pixels.emplace_back(getPixel(rowIndex,column));
    return pixels;
}