using System;

using System.IO.Ports;

namespace Program {
    static class program {
        static SerialPort port;

        static void Main() {
            String[] port_names = SerialPort.GetPortNames();
            Console.WriteLine("Ports: \n");
            foreach (String name in port_names) {
                Console.WriteLine("Name: " + name);
            }

            String port_to_connect = "COM5";

            port = new SerialPort(port_to_connect, 9600, Parity.None, 8, StopBits.One);
            port.Open();

            Console.WriteLine("Conectado con arduino.");

            bool key_found = false;
            while (!key_found) {
                String response = port.ReadLine();
                if (response.Length > 1) {
                    if(response.Contains("unlock")) {
                        Console.WriteLine("desbloqueado!!");
                        key_found = true;
                    }
                }
            }
        }
    }

}
