using System;
using System.Threading;

class Week4_202213111_6
{
    int number = 0;
    
    static void Main(string[] args)
    {
        Week4_202213111_6 pg = new Week4_202213111_6();

        Thread t1 = new Thread(threadFunc);
        Thread t2 = new Thread(threadFunc);

        t1.Start(pg);
        t2.Start(pg); // 2개의 스레드를 시작하고,

        t1.Join();
        t2.Join(); // 2개의 스레드 실행이 끝날 때까지 대기

        Console.WriteLine(pg.number); // 스레드 실행 완료 후 number값 출력
    }

    static void threadFunc(object inst)
    {
        Week4_202213111_6 pg = inst as Week4_202213111_6;

        for (int i = 0; i < 10000; i++)
        {
            pg.number = pg.number + 1; // number 필드 값을 증가
        }
    }
}