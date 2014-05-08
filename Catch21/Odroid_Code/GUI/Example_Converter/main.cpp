#include <iostream>
#include <QtGui>
#include <QImage>
#include <QPixmap>
#include <opencv2/core/core.hpp>
#include "Image_Converter.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Image_Converter conv;
    QImage convertedImage;
    QLabel lbl;
    QPixmap pixmap;

    cv::Mat frame;
    cv::VideoCapture capture;
    //cv::namedWindow("Opencv Image:",CV_WINDOW_AUTOSIZE);
    capture.open(0);

       // Create a window to show the frames

       // Play the video in a loop till it ends
       while(char(cv::waitKey(1)) != 'q' && capture.isOpened())
       {

           capture >> frame;

           // Check if the frame is empty
           if(frame.empty())
           {
               std::cout << "No picture in frame" << std::endl;
               return 0;
           }
           //cv::imshow("Opencv Image:",frame);

           convertedImage = conv.convertImage(frame);

           //Show the image
           if(!convertedImage.isNull())
           {
               pixmap = QPixmap::fromImage(convertedImage);
               lbl.setPixmap(pixmap);
               lbl.show();
           }
        }

    return app.exec();
}

