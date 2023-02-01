#ifndef VIDEO_RECORD_HPP
#define VIDEO_RECORD_HPP
#ifndef INT64_C
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif
extern "C"{
#include "libavdevice/avdevice.h"
}

using namespace std;

class VideoRecord{
private:

public:
    int initDevice();
    int record();
};

#endif