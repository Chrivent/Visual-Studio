using System.IO;
using System.Net;
using System.Net.Http;
using System.Net.Sockets;
using System.Text;

class Server
{
    static List<TcpClient> clients = new List<TcpClient>();

    static object clientLock = new object();

    const int orderBufSize = 512;

    static void Main()
    {
        try
        {
            TcpListener listener = new TcpListener(IPAddress.Any, 49446);

            listener.Start();

            while (true)
            {
                try
                {
                    TcpClient client = listener.AcceptTcpClient();

                    clients.Add(client);

                    Thread clientThread = new Thread(() => Client(client));

                    clientThread.Start();
                }
                catch (Exception e)
                {
                    Console.WriteLine("[Listening] " + e.Message);

                    continue;
                }
            }
        }
        catch (Exception e)
        {
            Console.WriteLine(e.Message);
        }
    }

    static void Client(TcpClient client)
    {
        while (true)
        {
            try
            {
                if (!client.Connected || client.Client.Poll(0, SelectMode.SelectRead))
                    throw new Exception();

                NetworkStream stream = client.GetStream();

                byte[] orderBuf = new byte[orderBufSize];

                stream.Read(orderBuf, 0, orderBuf.Length);

                string order = Encoding.Unicode.GetString(orderBuf);

                Console.WriteLine(order);

                orderBuf = Encoding.Unicode.GetBytes(order);

                if (string.IsNullOrEmpty(order) == false)
                {
                    lock (clientLock)
                    {
                        foreach (TcpClient otherClient in clients)
                        {
                            if (otherClient == client)
                                continue;

                            NetworkStream otherStream = otherClient.GetStream();

                            otherStream.Write(orderBuf, 0, orderBuf.Length);
                        }
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);

                lock (clientLock)
                    clients.Remove(client);

                client.Close();

                return;
            }
        }
    }
}
