
## HTTP 1.0 vs. HTTP 1.1 vs HTTP 2.0 vs HTTP 3.0
### HTTP 1.0 -> HTTP 1.1
connection을 한번 보낼때마다 계속 3way handshake를 진행해서 오버헤드가 발생
-> Keep-Alive로 일정시간동안은 connection을 유지하도록 하여 오버헤드 감소시킴

### HTTP 1.1 -> HTTP 2.0
* Head-of-blocking: 먼저 보낸애가 큰 파일을 보내고 있으면 뒤에 있는 애가 그 큰 파일이 다 가는동안 아무 응답을 받을 수 없음
=> 일정 크기로 큰 파일도 뒤에 요청한 애도 응답을 받을 수 있도록 함 (Multiplexing 방식) / 하나의 연결로 여러 요청과 응답을 동시에 처리

* 서버 푸시: 서버가 능동적으로 데이터 전송 가능, gRPC의 서버스트리밍 기능도 이 서버 푸시 기능을 활용하여 실시간 데이터 전송

* 바이너리 프레이밍: 바이너리 프레임으로 데이터 전송, HTTP 1.1은 텍스트 기반이라 느리지만, HTTP 2.0은 바이너리 기반이라서 더 빠르다

### HTTP 2.0 -> HTTP 3.0
* RTT 발생 , 긴 커넥션 유지 -> 개인정보 누출 우려, TCP 자체의 Head-of-LineBlocking
* => 결국 TCP가 문제이니 UDP를 사용하고 TCP의 기능을 윗 계층에서 구현하자 

### Shell Script
Shell Script(쉘 스크립트)는 리눅스/유닉스 환경에서 명령어를 자동 실행하도록 작성하는 스크립트 언어


### Singleton vs Static
둘다 한번만 생성해서 공유하는 패턴

