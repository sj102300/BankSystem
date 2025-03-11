#include <thread>
#include "services.h"

int main(void)
{
    // gRPC 서버를 별도의 스레드에서 실행
    std::thread server_thread(RunServer);
    server_thread.detach(); // 메인 스레드에서 분리

    std::cout << "Main thread continues execution..." << std::endl;

    // 메인 스레드에서 다른 작업 수행 가능
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}