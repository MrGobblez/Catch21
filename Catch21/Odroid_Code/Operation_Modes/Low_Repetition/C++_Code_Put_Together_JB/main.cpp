#include "Write_To_Memory_JB.h"
#include "Read_From_Memory_JB.h"

int main()
{
    Write_To_Memory_JB write;
    Read_From_Memory_JB read;

    write.startWritingThreadJB(true);

    read.startReadThreadJB(false);

    write.joinWritingThreadJB();

    read.joinReadThreadJB();
}
