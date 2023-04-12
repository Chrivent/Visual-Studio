using System;
using System.Threading;

class ThreadParam
{
    public int Value1;
    public int Value2;
}

class Week4_202213111_4
{
    static void Main(string[] args)
    {
        Thread t = new Thread(threadFunc);

        ThreadParam param = new ThreadParam();
        param.Value1 = 10;
        param.Value2 = 20;

        t.Start(param);
    }

    static void threadFunc(object initialValue)
    {
        ThreadParam value = (ThreadParam)initialValue;
        Console.WriteLine("{0}, {1}", value.Value1, value.Value2);
        // 출력 결과: 10, 20
    }
}