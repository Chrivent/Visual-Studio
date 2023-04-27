using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
// 몇몇 내용을 추가합니다.
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace NetworkGameServer
{
    class NetworkServer
    {
        static List<TcpClient> clientsList = new List<TcpClient>();
        
        static void Main(string[] args)
        {
            // 서버를 동작시키는데 별도의 스레드로 구동
            Thread serverThread = new Thread(serverFunc);

            serverThread.IsBackground = true;
            serverThread.Start();
            Thread.Sleep(500);

            Console.WriteLine(" *** 서버가 정상 구동 되었습니다. ***");
            Console.WriteLine(" 서버를 종료하려면 아무키나 누르세요...");
            Console.ReadLine();

            serverThread.Interrupt();
        }

        static void serverFunc()
        {
            // 네트워크 기능 추가
            TcpListener listener = new TcpListener(IPAddress.Any, 10200);
            listener.Start();
            Console.WriteLine("Waiting for client connections...");

            while (true)
            {
                TcpClient client = listener.AcceptTcpClient();
                clientsList.Add(client); // 새로운 클라이언트 연결을 리스트에 추가
                Console.WriteLine("Client connected.");

                // 새로운 클라이언트와 통신하기 위한 스레드 시작
                Thread clientThread = new Thread(() => ClientHandler(client));
                clientThread.Start();
            }
        }

        static void ClientHandler(TcpClient client)
        {
            NetworkStream stream = client.GetStream();
            byte[] buffer = new byte[1024];
            int bytes;

            try
            {
                while ((bytes = stream.Read(buffer, 0, buffer.Length)) != 0)
                {
                    string data = Encoding.Default.GetString(buffer, 0, bytes);
                    Console.WriteLine(data);

                    // 모든 클라이언트에게 메시지 전송
                    foreach (TcpClient c in clientsList)
                    {
                        if (c != client) // 메시지를 보낸 클라이언트를 제외하고 전송
                        {
                            NetworkStream sendStream = c.GetStream();
                            byte[] msg = Encoding.Default.GetBytes(data);
                            sendStream.Write(msg, 0, msg.Length);
                        }
                    }
                }
            }
            catch (IOException ex)
            {
                // 클라이언트와의 연결이 끊어졌을 때 발생하는 예외 처리
                Console.WriteLine("Client disconnected: " + ex.Message);
            }

            // Clean up the client connection.
            client.Close();
            clientsList.Remove(client); // 연결을 리스트에서 제거
        }
    }
}
