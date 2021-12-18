package com.example.rubiksolver_controller;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;

public class FinalView extends AppCompatActivity {

    //HashMap<String, char[][]> cube = new HashMap<>();
    HashMap<String, ArrayList<Button>> buttonsMap = new HashMap<>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_final_view);

        //POPULATE HASHMAP WITH ALL THE BUTTONS

        ArrayList<Button> top = new ArrayList<>();
        top.add((Button) findViewById(R.id.top11));top.add((Button) findViewById(R.id.top12));top.add((Button) findViewById(R.id.top13));
        top.add((Button) findViewById(R.id.top21));top.add((Button) findViewById(R.id.top22));top.add((Button) findViewById(R.id.top23));
        top.add((Button) findViewById(R.id.top31));top.add((Button) findViewById(R.id.top32));top.add((Button) findViewById(R.id.top33));
        buttonsMap.put("top", top);

        ArrayList<Button> left = new ArrayList<>();
        left.add((Button) findViewById(R.id.left11));left.add((Button) findViewById(R.id.left12));left.add((Button) findViewById(R.id.left13));
        left.add((Button) findViewById(R.id.left21));left.add((Button) findViewById(R.id.left22));left.add((Button) findViewById(R.id.left23));
        left.add((Button) findViewById(R.id.left31));left.add((Button) findViewById(R.id.left32));left.add((Button) findViewById(R.id.left33));
        buttonsMap.put("left", left);

        ArrayList<Button> front = new ArrayList<>();
        front.add((Button) findViewById(R.id.front11));front.add((Button) findViewById(R.id.front12));front.add((Button) findViewById(R.id.front13));
        front.add((Button) findViewById(R.id.front21));front.add((Button) findViewById(R.id.front22));front.add((Button) findViewById(R.id.front23));
        front.add((Button) findViewById(R.id.front31));front.add((Button) findViewById(R.id.front32));front.add((Button) findViewById(R.id.front33));
        buttonsMap.put("front", front);

        ArrayList<Button> right = new ArrayList<>();
        right.add((Button) findViewById(R.id.right11));right.add((Button) findViewById(R.id.right12));right.add((Button) findViewById(R.id.right13));
        right.add((Button) findViewById(R.id.right21));right.add((Button) findViewById(R.id.right22));right.add((Button) findViewById(R.id.right23));
        right.add((Button) findViewById(R.id.right31));right.add((Button) findViewById(R.id.right32));right.add((Button) findViewById(R.id.right33));
        buttonsMap.put("right", right);

        ArrayList<Button> back = new ArrayList<>();
        back.add((Button) findViewById(R.id.back11));back.add((Button) findViewById(R.id.back12));back.add((Button) findViewById(R.id.back13));
        back.add((Button) findViewById(R.id.back21));back.add((Button) findViewById(R.id.back22));back.add((Button) findViewById(R.id.back23));
        back.add((Button) findViewById(R.id.back31));back.add((Button) findViewById(R.id.back32));back.add((Button) findViewById(R.id.back33));
        buttonsMap.put("back", back);

        ArrayList<Button> bottom = new ArrayList<>();
        bottom.add((Button) findViewById(R.id.bottom11));bottom.add((Button) findViewById(R.id.bottom12));bottom.add((Button) findViewById(R.id.bottom13));
        bottom.add((Button) findViewById(R.id.bottom21));bottom.add((Button) findViewById(R.id.bottom22));bottom.add((Button) findViewById(R.id.bottom23));
        bottom.add((Button) findViewById(R.id.bottom31));bottom.add((Button) findViewById(R.id.bottom32));bottom.add((Button) findViewById(R.id.bottom33));
        buttonsMap.put("bottom", bottom);



        Intent intent = getIntent();
        //this.cube = (HashMap<String, char[][]>)intent.getSerializableExtra("cube");

        //read hashmap and color grid
//        ArrayList<char[]> cubestate = new ArrayList<>();
//
//        int cubevalueindex = 6,cubevalueindex2 = 6,cubevalueindex3 = 9;
        for (String key:Storage.cube.keySet()){
            char[][] thisFace = Storage.cube.get(key);
            for (int i=0;i<3;i++){
//                if(key == "back") {
//                    cubestate.add(cubevalueindex,thisFace[i]);
//                    cubevalueindex += 1;
//                }
//                else if(key == "front") {
//                    cubestate.add(cubevalueindex2,thisFace[i]);
//                    cubevalueindex2 += 1;
//                }
//                else if(key == "right") {
//                    cubestate.add(cubevalueindex3,thisFace[i]);
//                    cubevalueindex3 += 1;
//                }
//                else {
//                    cubestate.add(thisFace[i]);
//                }
                for (int j=0;j<3;j++){
                    int buttonIndex = i*3 + j;
                    Button btn = buttonsMap.get(key).get(buttonIndex);

                    if (thisFace[i][j] == 'W'){
                        btn.setBackgroundColor(Color.WHITE);
                    }
                    else if (thisFace[i][j] == 'Y'){
                        btn.setBackgroundColor(Color.YELLOW);
                    }
                    else if (thisFace[i][j] == 'O'){
                        btn.setBackgroundColor(Color.MAGENTA);
                    }
                    else if (thisFace[i][j] == 'R'){
                        btn.setBackgroundColor(Color.RED);
                    }
                    else if (thisFace[i][j] == 'B'){
                        btn.setBackgroundColor(Color.BLUE);
                    }
                    else if (thisFace[i][j] == 'G'){
                        btn.setBackgroundColor(Color.GREEN);
                    }
                    else{
                        btn.setBackgroundColor(Color.LTGRAY);
                    }
                }
            }
        }
//        Collections.swap(cubestate,4,7);
//        Collections.swap(cubestate,5,11);
//        Collections.swap(cubestate,6,12);
//        Collections.swap(cubestate,10,13);
//
//
//        for(int k = 0; k < cubestate.size(); k++) {
//            System.out.println("cubevalues = " + cubestate.get(k)[0] + cubestate.get(k)[1] + cubestate.get(k)[2]);
//        }
    }


    public void ChangeType(View view) {
        ArrayList<char[]> cubestate = new ArrayList<>();
        int cubevalueindex = 6,cubevalueindex2 = 6,cubevalueindex3 = 9;
        for (String key:Storage.cube.keySet()) {
            char[][] thisFace = Storage.cube.get(key);
            for (int i = 0; i < 3; i++) {
                if (key == "back") {
                    cubestate.add(cubevalueindex, thisFace[i]);
                    cubevalueindex += 1;
                } else if (key == "front") {
                    cubestate.add(cubevalueindex2, thisFace[i]);
                    cubevalueindex2 += 1;
                } else if (key == "right") {
                    cubestate.add(cubevalueindex3, thisFace[i]);
                    cubevalueindex3 += 1;
                } else {
                    cubestate.add(thisFace[i]);
                }
            }
        }
        Collections.swap(cubestate,4,7);
        Collections.swap(cubestate,5,11);
        Collections.swap(cubestate,6,12);
        Collections.swap(cubestate,10,13);
        String cubeState_str;
        cubeState_str = "";

        for(int k = 0; k < cubestate.size(); k++) {
            //System.out.println("cubevalues = " + cubestate.get(k)[0] + cubestate.get(k)[1] + cubestate.get(k)[2]);
            cubeState_str = cubeState_str + cubestate.get(k)[0] + cubestate.get(k)[1] + cubestate.get(k)[2];
            System.out.println("cubeString = " + cubeState_str);
        }
        if(view.getId() == R.id.button10) {  // Buttoon의 ID를 찾아서 실행이 된다.
            Toast.makeText(this, cubeState_str, Toast.LENGTH_SHORT).show();
        }
    }




    public void finalGoTop(View view){
        Intent intent = new Intent(this, com.example.rubiksolver_controller.TopActivity.class);
        //intent.putExtra("cube", this.cube);
        startActivity(intent);
    }

    public void finalGoFront(View view){
        Intent intent = new Intent(this, FrontActivity.class);
        //intent.putExtra("cube",this.cube);
        startActivity(intent);
    }

    public void finalGoLeft(View view){
        Intent intent = new Intent(this, LeftActivity.class);
        //intent.putExtra("cube",this.cube);
        startActivity(intent);
    }

    public void finalGoRight(View view){
        Intent intent = new Intent(this, com.example.rubiksolver_controller.RightActivity.class);
        //intent.putExtra("cube",this.cube);
        startActivity(intent);
    }

    public void finalGoBottom(View view){
        Intent intent = new Intent(this, com.example.rubiksolver_controller.BottomActivity.class);
        //intent.putExtra("cube",this.cube);
        startActivity(intent);
    }

    public void finalGoBack(View view){
        Intent intent = new Intent(this, com.example.rubiksolver_controller.BackActivity.class);
        //intent.putExtra("cube", this.cube);
        startActivity(intent);
    }

}
