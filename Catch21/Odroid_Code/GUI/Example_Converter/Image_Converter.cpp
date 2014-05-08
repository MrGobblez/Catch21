#include "Image_Converter.h"


QImage Image_Converter::convertImage(const cv::Mat& mat)
{

    if(mat.type()==CV_8UC1) // If the mat type is an 8-bit Usigned with 1 Channel
    {
        QVector<QRgb> colorTable;   // Create a vector of Qrgb values

        for(int i = 0; i < 256; i++)
        {
            colorTable.push_back(qRgb(i,i,i)); // Append a QRgb that holds (255,i,i,i)
        }

        const uchar *qImageBuffer = (const uchar*) mat.data; // Create a uchar variable to hold the data from mat

        QImage img(qImageBuffer,mat.cols,mat.rows,mat.step,QImage::Format_Indexed8);
        img.setColorTable(colorTable);
        return img;


    }

    else if(mat.type()==CV_8UC3)
    {
        const uchar *qImageBuffer = (const uchar*) mat.data;
        QImage img(qImageBuffer,mat.cols,mat.rows,mat.step,QImage::Format_RGB888);
        return img.rgbSwapped();
    }

    else
    {
        return QImage();
    }
}
