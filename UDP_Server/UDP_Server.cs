using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

class UDP_Server
{
    // 클라이언트들의 소켓을 저장할 리스트
    static List<EndPoint> clientIPs = new List<EndPoint>();

    static void Main(string[] args)
    {
        Thread serverThread = new Thread(serverFunc);
        serverThread.IsBackground = true;
        serverThread.Start();

        Console.WriteLine("* 야옹야옹이 게임용 서버 프로그램입니다.");
        Console.WriteLine("종료하려면 아무 키나 누르세요...");
        Console.ReadLine();
    }

    private static void serverFunc(object obj)
    {
        Socket srvSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
        IPEndPoint endPoint = new IPEndPoint(IPAddress.Any, 10200);

        srvSocket.Bind(endPoint);

        byte[] recvBytes = new byte[1024];
        EndPoint clientEP = new IPEndPoint(IPAddress.None, 0);

        while (true)
        {
            int nRecv = srvSocket.ReceiveFrom(recvBytes, ref clientEP);
            string txt = Encoding.UTF8.GetString(recvBytes, 0, nRecv);
            Console.WriteLine("- 수신 데이터: " + txt);

            if (txt == "Disconnect")
            {
                for (int i = clientIPs.Count - 1; i >= 0; i--)
                {
                    if (clientEP.ToString() == clientIPs[i].ToString())
                    {
                        clientIPs.RemoveAt(i);
                        break;
                    }
                }
            }
            else
            {
                // 모든 클라이언트들에게 데이터 전송
                foreach (var cp in clientIPs)
                {
                    if (clientEP.ToString() != cp.ToString())
                        srvSocket.SendTo(recvBytes, nRecv, SocketFlags.None, cp);
                }

                // 새로운 클라이언트인 경우 소켓을 리스트에 추가
                if (!clientIPs.Contains(clientEP))
                    clientIPs.Add(clientEP);
            }
        }
    }
}
