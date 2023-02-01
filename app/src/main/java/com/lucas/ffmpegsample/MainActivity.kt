package com.lucas.ffmpegsample

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.blankj.utilcode.util.FileIOUtils
import com.blankj.utilcode.util.FileUtils
import com.blankj.utilcode.util.ResourceUtils
import com.lucas.avcpp.AvCpp
import com.lucas.ffmpegsample.databinding.ActivityMainBinding
import java.io.File

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding
    private var audioFileDir = lazy { File(filesDir,"audio") }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
        cpAssetsFile()
        val avCpp = AvCpp()
//        avCpp.recordVideo()


        avCpp.resamplePCM(
            File(audioFileDir.value,"audio_48000_2_s16le.pcm").absolutePath,
            48000, "s16", 2,
            File(audioFileDir.value,"audio_44100_1_s16le.pcm").absolutePath,
            44100, "s16", 1
        )
        avCpp.pcm2aac( File(audioFileDir.value,"audio_44100_1_s16le.pcm").absolutePath,
            44100, "s16", 1,
            File(audioFileDir.value,"audio_44100_1.aac").absolutePath)


//        avCpp.resamplePCM(
//            File(audioFileDir.value,"audio_48000_2_s16le.pcm").absolutePath,
//            48000, "s16", 2,
//            File(audioFileDir.value,"audio_44100_1_fltp.pcm").absolutePath,
//            44100, "fltp", 1
//        )
    }

    //复制文件到内部存储
    private fun cpAssetsFile() {
        ResourceUtils.copyFileFromAssets("audio",audioFileDir.value.absolutePath)
//        ResourceUtils.copyFileFromAssets("audio/audio_mp3.mp3",audioFileDir.value.absolutePath)
    }


}