using System.Collections;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Diagnostics;
using System.IO;

public class NetworkClient_cs
{
    static void Main(string[] args)
    {
        // 네트워크 기능 추가
        TcpClient client = new TcpClient("localhost", 10200);
        NetworkStream stream = client.GetStream();

        // 보내는 스레드
        Thread sendThread = new Thread(() =>
        {
            while (true)
            {
                string message = Console.ReadLine();
                byte[] data = Encoding.Default.GetBytes(message);
                stream.Write(data, 0, data.Length);
            }
        });

        // 받는 스레드
        Thread receiveThread = new Thread(() =>
        {
            while (true)
            {
                byte[] data = new byte[1024];
                int bytes = stream.Read(data, 0, data.Length);
                string responseData = Encoding.Default.GetString(data, 0, bytes);
                Console.WriteLine(responseData);
            }
        });

        sendThread.Start();
        receiveThread.Start();

        // 스레드가 끝나기 전까지 대기
        sendThread.Join();
        receiveThread.Join();

        // Clean up the client connection.
        client.Close();
        Console.WriteLine("Disconnected from server.");
    }
}