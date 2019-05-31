package com.iot;

import android.widget.Button;
import android.widget.EditText;
import java.net.Socket;
import java.io.DataOutputStream;


public class IoTThread implements Runnable {
    private Thread thread;
    private String msg;
    private String port;

    public IoTThread(String port) {
        this.port = port;
    }

    @Override
    public void run() {
        try {
            Socket socket = new Socket(port, 1755);
            DataOutputStream DOS = new DataOutputStream(socket.getOutputStream());
            DOS.writeUTF(msg);
            socket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void Start(String msg) {
        this.msg = msg;
        thread = new Thread(this);
        thread.start();
    }
}
