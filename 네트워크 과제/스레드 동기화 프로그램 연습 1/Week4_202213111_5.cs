using System;
using System.Threading;

class Week4_202213111_5
{
    static int sum = 0;

    static void MyThread(object arg)
    {
        int num = (int)arg;
        for (int i = 1; i <= num; i++)
            sum += i;
    }

    static void Main(string[] args)
    {
        int num = 100;
        Thread hThread = new Thread(MyThread);

        Console.WriteLine("스레드 실행 전. 계산 결과 = {0}", sum);

        // [호기심이 많은 친구들을 위한 학습 주제 (2)]
        // 이번 주 Study 파일에 추가로 조사하여 발표에 도전해 보세요!
        //hThread.Suspend() hThread.Resume().
        // 참고로 이 프로그램의 구현에는 불필요합니다. ^^

        hThread.Start(num);
        hThread.Join();
        Console.WriteLine("스레드 실행 후, 계산 결과 = {0}", sum);
    }
}