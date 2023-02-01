package com.lucas.avcpp

/**
 * @author lucas
 * @since 2023/1/18.
 * @des
 */
class AvCpp {
    companion object {
        init {
            System.loadLibrary("av_cpp_sample")
        }
    }

    external fun recordVideo()


    external fun pcm2aac(
        inPCMFile: String,
        inSampleRate: Int,
        inSampleFmt: String,
        inChannels: Int,
        outAACFilePath: String
    ): Int

    /**
     * pcm重采样
     *
     * @param inPCMFile 目标pcm文件
     * @param inSampleRate 目标采样率
     * @param inSampleFmt 目标采样格式
     * @param inChannels 目标声道数
     * @param outPCMFile 输出pcm文件
     * @param outSampleRate 输出采样率
     * @param outSampleFmt 输出采样格式
     * @param outChannels 输出声道数
     */
    external fun resamplePCM(
        inPCMFile: String,
        inSampleRate: Int,
        inSampleFmt: String,
        inChannels: Int,
        outPCMFile: String,
        outSampleRate: Int,
        outSampleFmt: String,
        outChannels: Int
    ): Int
}