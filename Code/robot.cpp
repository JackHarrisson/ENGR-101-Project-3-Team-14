#include "robot.hpp"

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

        // read a row of pixels, and check how many of them are white
        for (int row = cameraView.height - 1; row < cameraView.height; row++) { // this just reads the row closest to the robot
            for (int col = 0; col < cameraView.width; col++) {
                if ((int)get_pixel(cameraView, row, col, 3) == 255) {
                    whitePix[col] = 1;
                    totWhite++;
                } else {
                    whitePix[col] = 0;
                }
            }
            /**
             * This following code checks whether the robot should turn left or right or go straight ahead
             */
            int lineLeft; // the index of the first white pixel
            for (int i = 0; i < cameraView.width; i++) {
                if (whitePix[i] == 1) {
                    lineLeft = i;
                    break;
                }
            }

            // this gives how much non-white pixels should be on either side of the white line
            int lineSpacing = (cameraView.width - totWhite)/2;

            // this checks how the robot should move in order to get the white line in the centre of its vision
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

        // if there is no white pixels, turn around and look for white pixels
        if (totWhite == 0) {
            vLeft = 0;
            vRight = 10;
        }

        setMotors(vLeft,vRight);
        std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
        usleep(10000);
    } //while

} // main 