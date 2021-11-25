package com.example.rubiksolver_controller;

import androidx.appcompat.app.AppCompatActivity;
import com.google.android.filament.utils.*;
import android.os.Bundle;
import android.view.Choreographer;
import android.view.SurfaceView;

public class MainActivity extends AppCompatActivity {

    private SurfaceView m_surfaceView;
    private Choreographer m_choreographer;
    private ModelViewer m_modelViewer;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        m_surfaceView = new SurfaceView(this);
        this.setContentView(m_surfaceView);
        m_choreographer = Choreographer.getInstance();
        m_modelViewer = new ModelViewer(m_surfaceView);
        m_surfaceView.setOnTouchListener(m_modelViewer);
    }

    private Choreographer.FrameCallback m_frameCallback = new Choreographer.FrameCallback() {
        @Override
        public void doFrame(long currentTime) {
            m_choreographer.postFrameCallback(this);
            m_modelViewer.render(currentTime);
        }
    };

    @Override
    protected void onResume() {
        super.onResume();
        m_choreographer.postFrameCallback(m_frameCallback);
    }

    @Override
    protected void onPause() {
        super.onPause();
        m_choreographer.removeFrameCallback(m_frameCallback);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        m_choreographer.removeFrameCallback(m_frameCallback);
    }
}