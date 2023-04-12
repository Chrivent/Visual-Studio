using System;
using System.Threading;

class Week4_202213111_3
{
    static void MyThread(object arg)
    {
        while (true) ;
    }

    static void Main(string[] args)
    {
        // 우선순위 값의 범위를 출력
        Console.WriteLine("우선순위: {0} ~ {1}",
        (int)ThreadPriority.Lowest, (int)ThreadPriority.Highest);

        // CPU 개수를 알아냄
        int NumberOfProcessors = Environment.ProcessorCount;

        // CPU 개수만큼 스레드를 생성
        for (int i = 0; i < NumberOfProcessors; i++)
        {
            // 스레드를 생성
            Thread hThread = new Thread(MyThread);
            hThread.IsBackground = true;
            // 우선순위를 높게 설정
            hThread.Priority = ThreadPriority.AboveNormal;
            hThread.Start();
        }

        // 우선순위를 낮게 설정한다.
        Thread.CurrentThread.Priority = ThreadPriority.BelowNormal;
        Thread.Sleep(1000);
        Console.WriteLine("주 스레드 실행!");
    }
}