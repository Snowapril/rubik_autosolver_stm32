package com.example.rubiksolver_controller;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import java.util.HashMap;

//import com.google.android.filament.utils.*;
//
//import android.content.Intent;
//import android.os.Bundle;
//import android.view.Choreographer;
//import android.view.SurfaceView;
//import android.view.View;
//import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    //HashMap<String,char[][]> cube;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Storage.cube=new HashMap<>();
        Storage.cube.put("top", new char[3][3]);
        Storage.cube.put("front", new char[3][3]);
        Storage.cube.put("left", new char[3][3]);
        Storage.cube.put("right", new char[3][3]);
        Storage.cube.put("bottom", new char[3][3]);
        Storage.cube.put("back", new char[3][3]);

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        CharSequence text = "Cube cleared.";
        Toast toast=Toast.makeText(this, text, Toast.LENGTH_SHORT);
        toast.show();
    }

    public void onStart(View view){
        Intent intent = new Intent(this, TopActivity.class);
        //intent.putExtra("cube", Storage.cube);
        startActivity(intent);
    }
}


//public class MainActivity extends AppCompatActivity {
//
//    private SurfaceView m_surfaceView;
//    private Choreographer m_choreographer;
//    private ModelViewer m_modelViewer;
//
//    @Override
//    protected void onCreate(Bundle savedInstanceState) {
//        super.onCreate(savedInstanceState);
//        setContentView(R.layout.activity_main);
//
//        m_surfaceView = new SurfaceView(this);
//        this.setContentView(m_surfaceView);
//        m_choreographer = Choreographer.getInstance();
//        m_modelViewer = new ModelViewer(m_surfaceView);
//        m_surfaceView.setOnTouchListener(m_modelViewer);
//    }
//
//    private Choreographer.FrameCallback m_frameCallback = new Choreographer.FrameCallback() {
//        @Override
//        public void doFrame(long currentTime) {
//            m_choreographer.postFrameCallback(this);
//            m_modelViewer.render(currentTime);
//        }
//    };
//
//    @Override
//    protected void onResume() {
//        super.onResume();
//        m_choreographer.postFrameCallback(m_frameCallback);
//    }
//
//    @Override
//    protected void onPause() {
//        super.onPause();
//        m_choreographer.removeFrameCallback(m_frameCallback);
//    }
//
//    @Override
//    protected void onDestroy() {
//        super.onDestroy();
//        m_choreographer.removeFrameCallback(m_frameCallback);
//    }
//}