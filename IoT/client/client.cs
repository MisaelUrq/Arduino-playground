using System;
using System.Windows.Forms;
using System.Net.Sockets;
using System.Text;



namespace ConsoleApplication
{
    class Program
    {

        static void Main(string[] args)
        {
            System.Net.Sockets.TcpClient clientSocket = new System.Net.Sockets.TcpClient();
            clientSocket.Connect("162.168.0.18", 8888);
            Console.WriteLine("Client Socket Program - Server Connected ...");

            NetworkStream serverStream = clientSocket.GetStream();
            byte[] outStream = System.Text.Encoding.ASCII.GetBytes("ON$");
            serverStream.Write(outStream, 0, outStream.Length);
            serverStream.Flush();

            byte[] inStream = new byte[10025];
            serverStream.Read(inStream, 0, (int)clientSocket.ReceiveBufferSize);
            string returndata = System.Text.Encoding.ASCII.GetString(inStream);
        }
    }
}
