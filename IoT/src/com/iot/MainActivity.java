package com.iot;

import android.app.Activity;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.view.View.OnClickListener;
import android.view.View;

import com.iot.R;

public class MainActivity extends Activity
{
    @Override
    protected void onCreate(Bundle icicle)
    {
        super.onCreate(icicle);
        setContentView(R.layout.main);

        Button button_on  = (Button) findViewById(R.id.button1);
        Button button_off = (Button) findViewById(R.id.button2);
        final EditText text_input = (EditText) findViewById(R.id.text_input);

        if (button_on != null) {
            button_on.setOnClickListener(new OnClickListener() {
                @Override
                public void onClick(View v) {
                    IoTThread client_service = new IoTThread(text_input.getText().toString());
                    client_service.Start("ON");
                }
            });
        }

        if (button_off != null) {
            button_off.setOnClickListener(new OnClickListener() {
                @Override
                public void onClick(View v) {
                    IoTThread client_service = new IoTThread(text_input.getText().toString());
                    client_service.Start("OFF");
                }
            });
        }
    }


}
