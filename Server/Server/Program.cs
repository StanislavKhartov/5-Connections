using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

// Socket Listener acts as a server and listens to the incoming
// messages on the specified port and protocol.
public class SocketListener
{
    public static int Main(String[] args)
    {
        StartServer();
        return 0;
    }

  
    public static void StartServer()
    {
        // Get Host IP Address that is used to establish a connection
        // In this case, we get one IP address of localhost that is IP : 127.0.0.1
        // If a host has multiple addresses, you will get a list of addresses
        IPHostEntry host = Dns.GetHostEntry("localhost");
        IPAddress ipAddress = host.AddressList[0];
        IPEndPoint localEndPoint = new IPEndPoint(ipAddress, 11000);

        void callMenu()
        {
            Console.WriteLine("1 - Send message\n");
            Console.WriteLine("2 - Recieve message\n");
            Console.WriteLine("0 - Exit\n");
        }

        try
        {

            // Create a Socket that will use Tcp protocol
            Socket listener = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            // A Socket must be associated with an endpoint using the Bind method
            listener.Bind(localEndPoint);
            // Specify how many requests a Socket can listen before it gives Server busy response.
            // We will listen 10 requests at a time
            listener.Listen(10);

            Console.WriteLine("Waiting for a connection...");
            Socket handler = listener.Accept();

            // Incoming data from the client.
            string data = null;
            byte[] bytes = null;

            while (true)
            {
                bytes = new byte[1024];
                int bytesRec = handler.Receive(bytes);
                data += Encoding.ASCII.GetString(bytes, 0, bytesRec);
                if (data.IndexOf("<EOF>") > -1)
                {
                    break;
                }
            }

            Console.WriteLine("Text received : {0}", data);

            byte[] msg = Encoding.ASCII.GetBytes(data);
            handler.Send(msg);
            int state = 1;
            while (state != 0)
            {
                callMenu();
                state = Convert.ToInt16(Console.ReadLine());
                if (state > 2 || state < 0)
                {
                    Console.WriteLine("Wrong state");
                    handler.Shutdown(SocketShutdown.Both);
                    handler.Close();
                }
                if (state == 1)
                {
                    int num = Convert.ToInt16(Console.ReadLine());
                    byte[] msg1 = Encoding.ASCII.GetBytes(num.ToString());
                    handler.Send(msg1);

                }
                if (state == 2)
                {
                    int bytesRec = handler.Receive(bytes);
                    string data1 = Encoding.ASCII.GetString(bytes, 0, bytesRec);
                    Console.WriteLine("Text received : {0}", data1);
                }
            }
            handler.Shutdown(SocketShutdown.Both);
            handler.Close();
        }
        catch (Exception e)
        {
            Console.WriteLine(e.ToString());
        }

        Console.WriteLine("\n Press any key to continue...");
        Console.ReadKey();
    }
}