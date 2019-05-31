package com;

import java.net.Socket;
import java.io.DataOutputStream;
import java.io.DataInputStream;
import java.net.ServerSocket;
import gnu.io.CommPort;
import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;
import java.lang.Runtime;

public class Server {
    public static void main(String []args) {
        while (true) {
            String msg_received = "";
            try {
                ServerSocket socket = new ServerSocket(1755);
                Socket clientSocket = socket.accept();
                DataInputStream DIS = new DataInputStream(clientSocket.getInputStream());
                msg_received = DIS.readUTF();
                System.out.println(msg_received);
                if (msg_received.compareTo("ON") == 0) {
                    Runtime.getRuntime().exec(new String[] {"server.exe", "O"});
                } else if (msg_received.compareTo("OFFF") == 0) {
                    Runtime.getRuntime().exec(new String[] {"server.exe", "F"});
                }
                clientSocket.close();
                socket.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}
