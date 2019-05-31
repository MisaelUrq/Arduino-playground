package com;

import java.net.Socket;
import java.io.DataOutputStream;
import java.io.DataInputStream;
import java.net.ServerSocket;

public class Client {
    public static void main(String []args) {
        String msg_received;

        try {
            Socket socket = new Socket(args[0], 1755);
            DataOutputStream DOS = new DataOutputStream(socket.getOutputStream());
            DOS.writeUTF("ON");
            socket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
