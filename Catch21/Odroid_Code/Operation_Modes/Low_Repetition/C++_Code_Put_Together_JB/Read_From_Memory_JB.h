#ifndef READ_FROM_MEMORY_JB_H
#define READ_FROM_MEMORY_JB_H

#include <boost/thread.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

class Read_From_Memory_JB
{
public:
    Read_From_Memory_JB();

    void startReadThreadJB(bool speed);

    void joinReadThreadJB();

    void readFromMemoryJB(bool speed);

private:

    boost::thread readingThread;
};

#endif // READ_FROM_MEMORY_JB_H
