using System;
using System.Threading;

class Week4_202213111_2
{
    static void Main(string[] args)
    {
        Thread t = new Thread(threadFunc);

        // [호기심이 많은 친구들을 위한 학습 주제 (1)]
        // 이번 주 Study 파일에 추가로 조사하여 발표에 도전해 보세요!
        // Background 란 어떤 개념일까요?
        // 아래의 문장은 과연 어떤 역할을 할까요?
        // t.IsBackground = true;

        t.Start();
        // 더는 주 스레드가 실행할 명령어가 없으므로 주 스레드는 제거
        //t.Join(); // t 스레드가 종료될 때까지 현재 스레드를 무한 대기
        Console.WriteLine("주 스레드 종료!");
    }

    static void threadFunc()
    {
        Console.WriteLine("10초 후에 프로그램 종료");
        Thread.Sleep(1000 * 10); // 10초 동안 실행 중지
        // 현재 주 스레드는 종료됐어도 t 스레드는 존속
        Console.WriteLine("스레드 종료!");
    }
}