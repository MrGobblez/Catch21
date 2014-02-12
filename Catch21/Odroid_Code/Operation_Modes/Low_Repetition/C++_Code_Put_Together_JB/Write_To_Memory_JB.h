#ifndef WRITE_TO_MEMORY_JB_H
#define WRITE_TO_MEMORY_JB_H

#include <opencv2/highgui/highgui.hpp>
#include <boost/thread.hpp>
#include <opencv2/core/core.hpp>

class Write_To_Memory_JB
{
public:
    Write_To_Memory_JB();

    void startWritingThreadJB(bool window);

    void joinWritingThreadJB();

    void writeToMemoryJB(bool showWind);

private:

    boost::thread writingThread;
};

#endif // WRITE_TO_MEMORY_JB_H
