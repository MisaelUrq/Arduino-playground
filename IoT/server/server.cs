using System;

using System.IO.Ports;

namespace Program {
    static class program {
        static SerialPort port;
        static void Main(String[] args) {
            String port_to_connect = "COM5";
            port = new SerialPort(port_to_connect, 9600, Parity.None, 8, StopBits.One);
            port.Open();
            if (args.Length > 0) {
                Console.WriteLine(args[0]);
                port.Write(args[0]);
            }
            port.Close();
        }
    }

}
