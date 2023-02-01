#include "video_record.hpp"
#include "log.hpp"

int VideoRecord::initDevice(){
    avdevice_register_all();
//    AVInputFormat *inputFormat = av_find_input_format("dshow");
//    ALOGD("find device :%d",inputFormat== nullptr)
}
int VideoRecord::record(){

}