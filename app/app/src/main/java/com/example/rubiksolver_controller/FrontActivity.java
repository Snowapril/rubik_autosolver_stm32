package com.example.rubiksolver_controller;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;

import java.util.ArrayList;
import java.util.HashMap;

public class FrontActivity extends AppCompatActivity {

    HashMap<Integer, Integer> flags = new HashMap();
    //HashMap<String, char[][]> cube;
    ArrayList<Button> buttons= new ArrayList<>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_front);

        //Intent intent = getIntent();
        //this.cube = (HashMap<String, char[][]>)intent.getSerializableExtra("cube");

        flags.put(11,1);flags.put(12, 1);flags.put(13, 1);
        flags.put(21,1);flags.put(22, 1);flags.put(23, 1);
        flags.put(31,1);flags.put(32, 1);flags.put(33, 1);

        buttons.add((Button) findViewById(R.id.button));
        buttons.add((Button) findViewById(R.id.button2));
        buttons.add((Button) findViewById(R.id.button3));
        buttons.add((Button) findViewById(R.id.button4));
        buttons.add((Button) findViewById(R.id.button5));
        buttons.add((Button) findViewById(R.id.button6));
        buttons.add((Button) findViewById(R.id.button7));
        buttons.add((Button) findViewById(R.id.button8));
        buttons.add((Button) findViewById(R.id.button9));

        char[][] thisFace = com.example.rubiksolver_controller.Storage.cube.get("front");
        for (int i=0;i<3;i++){
            for (int j=0;j<3;j++){
                int buttonIndex = i*3 + j;
                if (thisFace[i][j]=='W'){
                    buttons.get(buttonIndex).setBackgroundColor(Color.WHITE);
                }
                else if (thisFace[i][j]=='Y'){
                    buttons.get(buttonIndex).setBackgroundColor(Color.YELLOW);
                }
                else if (thisFace[i][j]=='O'){
                    buttons.get(buttonIndex).setBackgroundColor(Color.rgb(255, 165, 0));
                }
                else if (thisFace[i][j]=='R'){
                    buttons.get(buttonIndex).setBackgroundColor(Color.RED);
                }
                else if (thisFace[i][j]=='B'){
                    buttons.get(buttonIndex).setBackgroundColor(Color.BLUE);
                }
                else if (thisFace[i][j]=='G'){
                    buttons.get(buttonIndex).setBackgroundColor(Color.GREEN);
                }
                else{
                    buttons.get(buttonIndex).setBackgroundColor(Color.LTGRAY);
                }
            }
        }

    }

    public void changeColorFront(int i, int j, Button btn) {
        char[][] thisFace = com.example.rubiksolver_controller.Storage.cube.get("front");
        if (flags.get(10*i+j)==1){
            btn.setBackgroundColor(Color.WHITE);
            flags.put(10*i+j,2);
            thisFace[i-1][j-1]='W';
        }
        else if (flags.get(10*i+j)==2){
            btn.setBackgroundColor(Color.YELLOW);
            flags.put(10 * i + j, 3);
            thisFace[i-1][j-1]='Y';
        }
        else if (flags.get(10*i+j)==3){
            btn.setBackgroundColor(Color.rgb(255, 165, 0));
            flags.put(10 * i + j, 4);
            thisFace[i-1][j-1]='O';//Orange
        }
        else if (flags.get(10*i+j)==4){
            btn.setBackgroundColor(Color.RED);
            flags.put(10*i+j,5);
            thisFace[i-1][j-1]='R';
        }
        else if (flags.get(10*i+j)==5){
            btn.setBackgroundColor(Color.BLUE);
            flags.put(10 * i + j, 6);
            thisFace[i-1][j-1]='B';
        }
        else if (flags.get(10*i+j)==6){
            btn.setBackgroundColor(Color.GREEN);
            flags.put(10 * i + j, 1);
            thisFace[i-1][j-1]='G';
        }
        com.example.rubiksolver_controller.Storage.cube.put("front",thisFace);
    }

    public void changeColorFront11(View view){
        Button btn = (Button) findViewById(R.id.button);
        changeColorFront(1, 1, btn);
    }

    public void changeColorFront12(View view){
        Button btn = (Button) findViewById(R.id.button2);
        changeColorFront(1, 2, btn);
    }

    public void changeColorFront13(View view){
        Button btn = (Button) findViewById(R.id.button3);
        changeColorFront(1, 3, btn);
    }

    public void changeColorFront21(View view){
        Button btn = (Button) findViewById(R.id.button4);
        changeColorFront(2, 1, btn);
    }

    public void changeColorFront22(View view){
        Button btn = (Button) findViewById(R.id.button5);
        changeColorFront(2, 2, btn);
    }

    public void changeColorFront23(View view){
        Button btn = (Button) findViewById(R.id.button6);
        changeColorFront(2, 3, btn);
    }

    public void changeColorFront31(View view){
        Button btn = (Button) findViewById(R.id.button7);
        changeColorFront(3, 1, btn);
    }

    public void changeColorFront32(View view){
        Button btn = (Button) findViewById(R.id.button8);
        changeColorFront(3, 2, btn);
    }

    public void changeColorFront33(View view){
        Button btn = (Button) findViewById(R.id.button9);
        changeColorFront(3, 3, btn);
    }


    public void frontGoTop(View view){
        Intent intent = new Intent(this, com.example.rubiksolver_controller.TopActivity.class);
        //intent.putExtra("cube",this.cube);
        startActivity(intent);
    }

    public void frontGoLeft(View view){
        Intent intent = new Intent(this, LeftActivity.class);
        //intent.putExtra("cube",this.cube);
        startActivity(intent);
    }

    public void frontGoRight(View view){
        Intent intent = new Intent(this, com.example.rubiksolver_controller.RightActivity.class);
        //intent.putExtra("cube",this.cube);
        startActivity(intent);
    }

    public void frontGoBottom(View view){
        Intent intent = new Intent(this, com.example.rubiksolver_controller.BottomActivity.class);
        //intent.putExtra("cube",this.cube);
        startActivity(intent);
    }

    public void frontGoBack(View view){
        Intent intent = new Intent(this, com.example.rubiksolver_controller.BackActivity.class);
        //intent.putExtra("cube",this.cube);
        startActivity(intent);
    }

    public void home(View view){
        Intent intent = new Intent(this, MainActivity.class);
        startActivity(intent);
    }

    public void view(View view){
        Intent intent = new Intent(this, com.example.rubiksolver_controller.FinalView.class);
        //intent.putExtra("cube",this.cube);
        startActivity(intent);
    }
}
