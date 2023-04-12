using System;
using System.Diagnostics.Metrics;
using System.Threading;

class ThreadSample
{
    public static void Main()
    {
        ThreadSample ts = new ThreadSample();
    }

    public ThreadSample()
    {
        int i;
        Thread newCounter = new Thread(new ThreadStart(Counter)); Thread newCounter2 = new Thread(new ThreadStart(Counter2));

        newCounter.Start();
        newCounter2.Start();

        for (i = 0; i < 10; i++)
        {
            Console.WriteLine("main: {0}", i);
            Thread.Sleep(1000);
        }
    }

    void Counter()
    {
        int i;
        for (i = 0; i < 10; i++)
        {
            Console.WriteLine(" thread: {0}", i);
            Thread.Sleep(2000);
        }
    }

    void Counter2()
    {
        int i;
        for (i = 0; i < 10; i++)
        {
            Console.WriteLine(" thread: {0}", i);
            Thread.Sleep(3000);
        }
    }
}