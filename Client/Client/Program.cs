using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using static System.Runtime.InteropServices.JavaScript.JSType;
using String = System.String;

// Client app is the one sending messages to a Server/listener.
// Both listener and client can send messages back and forth once a
// communication is established.
public class SocketClient
{
    public static int Main(String[] args)
    {
        StartClient();
        return 0;
    }

    public static void StartClient()
    {
        void callMenu()
        {
            Console.WriteLine("1 - Send message\n");
            Console.WriteLine("2 - Recieve message\n");
            Console.WriteLine("0 - Exit\n");
        }
        byte[] bytes = new byte[1024];

        try
        {
            // Connect to a Remote server
            // Get Host IP Address that is used to establish a connection
            // In this case, we get one IP address of localhost that is IP : 127.0.0.1
            // If a host has multiple addresses, you will get a list of addresses
            IPHostEntry host = Dns.GetHostEntry("localhost");
            IPAddress ipAddress = host.AddressList[0];
            IPEndPoint remoteEP = new IPEndPoint(ipAddress, 11000);

            // Create a TCP/IP  socket.
            Socket sender = new Socket(ipAddress.AddressFamily,
                SocketType.Stream, ProtocolType.Tcp);

            // Connect the socket to the remote endpoint. Catch any errors.
            try
            {
                // Connect to Remote EndPoint
                sender.Connect(remoteEP);

                Console.WriteLine("Socket connected to {0}",
                    sender.RemoteEndPoint.ToString());

                
                // Encode the data string into a byte array.
                byte[] msg = Encoding.ASCII.GetBytes("This is a test<EOF>");

                // Send the data through the socket.
                int bytesSent = sender.Send(msg);

                // Receive the response from the remote device.
                int bytesRec = sender.Receive(bytes);
                Console.WriteLine("Echoed test = {0}",
                    Encoding.ASCII.GetString(bytes, 0, bytesRec));

                // Release the socket.
                int state = 1;
                while (state != 0)
                {
                    callMenu();
                    state = Convert.ToInt16(Console.ReadLine());
                    if (state > 2 || state < 0)
                    {
                        Console.WriteLine("Wrong state");
                        sender.Shutdown(SocketShutdown.Both);
                        sender.Close();
                    }
                    if (state == 1)
                    {
                        int num = Convert.ToInt16(Console.ReadLine());
                        byte[] msg1 = Encoding.ASCII.GetBytes(num.ToString());
                        sender.Send(msg1);

                    }
                    if (state == 2)
                    {
                        int bytesRec1 = sender.Receive(bytes);
                        Console.WriteLine("recieved data = {0}",
                        Encoding.ASCII.GetString(bytes, 0, bytesRec1));
                    }
                }
                sender.Shutdown(SocketShutdown.Both);
                sender.Close();

            }
            catch (ArgumentNullException ane)
            {
                Console.WriteLine("ArgumentNullException : {0}", ane.ToString());
            }
            catch (SocketException se)
            {
                Console.WriteLine("SocketException : {0}", se.ToString());
            }
            catch (Exception e)
            {
                Console.WriteLine("Unexpected exception : {0}", e.ToString());
            }

        }
        catch (Exception e)
        {
            Console.WriteLine(e.ToString());
        }
    }
}