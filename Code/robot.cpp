#include "robot.hpp"

int isWhite(ImagePPM image, int row, int col) {
    if ((int)get_pixel(cameraView, row, col, 3) == 255) {
        return 1;
    } else {
        return 0;
    }
}

int main(){
    cameraView.width = 150;
    cameraView.height = 100;
    cameraView.data = new char[cameraView.width * cameraView.height*3];
    cameraView.n_bytes = cameraView.width * cameraView.height*3;

    if (connectNetwork()!=0){
        return -1;
    }

    std::string fileName = "i0.ppm";

    double vLeft = 10.0;
    double vRight = 10.0;

    while(1){
        takePicture();
        SavePPMFile(fileName,cameraView);
        OpenPPMFile(fileName, cameraView);

        int totPix = cameraView.width * cameraView.height; // total pixels
        int whitePix[cameraView.width]; // 0 = not white; 1 = white
        int totWhite = 0; // total white pixels

        for (int row = cameraView.height - 1; row < cameraView.height; row++) {
            for (int col = 0; col < cameraView.width; col++) {
                if ((int)get_pixel(cameraView, row, col, 3) == 255) {
                    whitePix[col] = 1;
                    totWhite++;
                } else {
                    whitePix[col] = 0;
                }
            }
            // now check how much the robot should turn
            int lineLeft; // the index of the first white pixel
            for (int i = 0; i < cameraView.width; i++) {
                if (whitePix[i] == 1) {
                    lineLeft = i;
                    break;
                }
            }

            //----- this gives how much non-white pixels should be on either side of the white line
            int lineSpacing = (cameraView.width - totWhite)/2;

            if (lineSpacing - lineLeft < 0) {
                // turn right
                vLeft = 15;
                vRight = 10;
            } else if (lineSpacing - lineLeft > 0) {
                // turn left
                vRight = 15;
                vLeft = 10;
            } else {
                vLeft = 10;
                vRight = 10;
            }
        }

        if (totWhite == 0) {
            vLeft = 0;
            vRight = 0;
        }

        setMotors(vLeft,vRight);
        std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
        usleep(10000);
    } //while

} // main 