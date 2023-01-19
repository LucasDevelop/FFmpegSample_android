package com.lucas.ffmpegsample

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import com.lucas.avcpp.AvCpp
import com.lucas.ffmpegsample.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        AvCpp().resamplePCM("", 0, "", 0,
            "", 0, "", 0)
    }


    companion object {
        // Used to load the 'ffmpegsample' library on application startup.
        init {
            System.loadLibrary("av_cpp_sample")
        }
    }
}