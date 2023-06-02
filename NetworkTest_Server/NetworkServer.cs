using System.Text;
using System.Net;
using System.Net.Sockets;
using MySqlX.XDevAPI;
using System.Data;
using Org.BouncyCastle.Utilities;
using MySql.Data.MySqlClient;

class NetworkServer
{
    static List<TcpClient> clients = new List<TcpClient>();
    static NetworkDatabase? database;

    static void Main(string[] args)
    {
        Console.Write("Enter database name : ");
        string? databaseName = Console.ReadLine();

        using (database = new NetworkDatabase(databaseName!))
        {
            if (database.connect)
            {
                Thread serverThread = new Thread(ServerThread);

                serverThread.IsBackground = true;
                serverThread.Start();

                Console.WriteLine("*** Server is running ***");
                Console.WriteLine("Press any key to exit...");
                Console.ReadLine();

                foreach (TcpClient client in clients)
                {
                    NetworkStream stream = client.GetStream();
                    byte[] bytes = Encoding.Default.GetBytes("Down/:");
                    stream.Write(bytes, 0, bytes.Length);
                    client.Close();
                }

                serverThread.Interrupt();
            }
        }

        Console.WriteLine("Server is down");
    }

    static void ServerThread()
    {
        TcpListener listener = new TcpListener(IPAddress.Any, 10200);
        listener.Start();

        while (true)
        {
            TcpClient client = listener.AcceptTcpClient();
            clients.Add(client);

            Thread clientThread = new Thread(() => ClientThread(client));
            clientThread.Start();
        }
    }

    static void ClientThread(TcpClient client)
    {
        NetworkStream stream = client.GetStream();
        byte[] bytes = new byte[1024];
        string? nickname = null;

        try
        {
            int count = stream.Read(bytes, 0, bytes.Length);
            string connectData = Encoding.Default.GetString(bytes, 0, count);
            WriteLog(connectData);

            SendToOtherClient(client, connectData);

            string connectCommand = connectData.Split("/")[0];
            nickname = connectData.Substring(connectCommand.Length + 1).Split(":")[0];

            while ((count = stream.Read(bytes, 0, bytes.Length)) != 0)
            {
                string data = Encoding.Default.GetString(bytes, 0, count);
                string command = data.Split("/")[0];

                if (command == "Disconnect")
                    throw new Exception();

                WriteLog(data);

                if (command == "Database(Send)")
                    SendToDatabase(data);
                else if (command == "Database(Receive)")
                    ReceiveFromDatabase(client, data);
                else
                    SendToOtherClient(client, data);
            }
        }
        catch (Exception ex)
        {
            WriteLog("Disconnect/" + nickname + ":", ex);
        }

        SendToOtherClient(client, "Disconnect/" + nickname + ":");

        client.Close();
        clients.Remove(client);
    }

    static void WriteLog(string data, Exception? ex = null)
    {
        string command = data.Split("/")[0];
        string nickname = data.Substring(command.Length + 1).Split(":")[0];
        string msg = data.Substring(command.Length + nickname.Length + 2);

        switch (command)
        {
            case "Connect":
                Console.WriteLine("[" + GetTIme() + "] [" + command + "] " + nickname + " is connected to server");
                break;

            case "Disconnect":
                Console.WriteLine("[" + GetTIme() + "] [" + command + "] " + nickname + " is disconnected to server (" + ex!.Message + ")");
                break;

            case "Chat":
                Console.WriteLine("[" + GetTIme() + "] [" + command + "] " + nickname + " : " + msg);
                break;

            case "Database(Send)":
                Console.WriteLine("[" + GetTIme() + "] [" + command + "] " + nickname + " => " + msg);
                break;

            case "Database(Receive)":
                Console.WriteLine("[" + GetTIme() + "] [" + command + "] " + nickname + " => " + msg);
                break;

            default:
                Console.WriteLine("[" + GetTIme() + "] [" + command + "] " + nickname + " - " + msg);
                break;
        }
    }

    static string GetTIme()
    {
        return
            DateTime.Now.Year + "/" +
            DateTime.Now.Month + "/" +
            DateTime.Now.Day + " " +
            DateTime.Now.Hour + ":" +
            DateTime.Now.Minute + ":" +
            DateTime.Now.Second;
    }

    static void SendToOtherClient(TcpClient client, string data)
    {
        foreach (TcpClient c in clients)
        {
            if (c != client && c.Connected)
            {
                NetworkStream stream = c.GetStream();
                byte[] bytes = Encoding.Default.GetBytes(data);
                stream.Write(bytes, 0, bytes.Length);
            }
        }
    }

    static void SendToDatabase(string data)
    {
        string command = data.Split("/")[0];
        string nickname = data.Substring(command.Length + 1).Split(":")[0];
        string msg = data.Substring(command.Length + nickname.Length + 2);

        database!.SendQuery(msg);
    }

    static void ReceiveFromDatabase(TcpClient client, string data)
    {
        string command = data.Split("/")[0];
        string nickname = data.Substring(command.Length + 1).Split(":")[0];
        string msg = data.Substring(command.Length + nickname.Length + 2);

        NetworkStream stream = client.GetStream();
        byte[] bytes = Encoding.Default.GetBytes("Database(Receive)/:" + database!.ReceiveQuery(msg));
        stream.Write(bytes, 0, bytes.Length);
    }
}
