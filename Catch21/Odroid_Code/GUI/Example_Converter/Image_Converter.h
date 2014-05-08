#ifndef IMAGE_CONVERTER_H
#define IMAGE_CONVERTER_H

#include <QtGui/QImage>
#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>

class Image_Converter
{
public:
    QImage convertImage(const cv::Mat&);

};

#endif // IMAGE_CONVERTER_H
