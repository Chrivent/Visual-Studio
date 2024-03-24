using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

class Program
{
    static async Task Main()
    {
        // 접속할 서버의 주소 및 포트 설정
        IPAddress serverAddress = IPAddress.Loopback;
        int serverPort = 9001;

        // 소켓 생성 및 연결
        using (var clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
        {
            var serverEndPoint = new IPEndPoint(serverAddress, serverPort);

            try
            {
                await clientSocket.ConnectAsync(serverEndPoint);

                Console.WriteLine($"Connected to {serverAddress}:{serverPort}");

                // 데이터 수신을 위한 비동기 수신 메서드 호출
                await ReceiveData(clientSocket);
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error: {ex.Message}");
            }
        }
    }

    static async Task ReceiveData(Socket clientSocket)
    {
        byte[] buffer = new byte[1024];
        int bytesRead;

        try
        {
            while ((bytesRead = await clientSocket.ReceiveAsync(buffer, SocketFlags.None)) > 0)
            {
                string receivedData = Encoding.UTF8.GetString(buffer, 0, bytesRead);
                Console.WriteLine($"Received: {receivedData}");
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error receiving data: {ex.Message}");
        }
    }
}
