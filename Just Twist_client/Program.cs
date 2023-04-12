using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;

class Client
{
    static EventWaitHandle wait = new EventWaitHandle(false, EventResetMode.AutoReset);
    static string nickName = "client";
    const int orderBufSize = 512;

    static string test;

    static void Send(TcpClient tcpClient)
    {
        while (true)
        {
            try
            {
                NetworkStream stream = tcpClient.GetStream();

                byte[] orderBuf;

                while (true)
                {
                    wait.WaitOne();

                    string order = test;

                    order = order + ":" + nickName;
                    orderBuf = Encoding.Unicode.GetBytes(order);

                    stream.Write(orderBuf, 0, orderBuf.Length);
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e);

                return;
            }
        }
    }

    static void Receive(TcpClient tcpClient)
    {
        while (true)
        {
            try
            {
                NetworkStream stream = tcpClient.GetStream();

                byte[] orderBuf;

                while (true)
                {
                    orderBuf = new byte[orderBufSize];
                    
                    stream.Read(orderBuf, 0, orderBuf.Length);

                    string order = Encoding.Unicode.GetString(orderBuf);

                    if (string.IsNullOrEmpty(order) == false)
                        Console.WriteLine(order);
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e);

                return;
            }
        }
    }

    static void Main(string[] args)
    {
        while (true)
        {
            try
            {
                TcpClient tcpClient = new TcpClient();

                tcpClient.Connect(new IPEndPoint(IPAddress.Loopback, 49446));

                Thread sendThread = new Thread(() => Send(tcpClient));
                Thread receiveThread = new Thread(() => Receive(tcpClient));

                sendThread.Start();
                receiveThread.Start();

                break;
            }
            catch
            {
                continue;
            }
        }

        try
        {
            while (true)
            {
                string str = Console.ReadLine();

                if (string.IsNullOrEmpty(str))
                   continue;

                test = str;

                wait.Set();
            }
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
        }

    }
}
