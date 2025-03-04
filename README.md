# 인터넷 뱅킹 서버 시스템

## 📌 개발 목표
- MSA 구조를 통해 확장성 좋은 시스템 구축
- 객체 지향 설계로 코드 재사용성과 유지보수성 향상
- SQLite-ORM을 활용하여 SQL 없이 효율적인 데이터베이스 조작 및 관리
- Protobuf를 사용한 통신 메시지 정의
- gRPC를 활용한 클라이언트-서버 간 고성능 데이터 송수신 구현
- cmake를 활용한 빌드 자동화로 개발 생산성 향상


## 1️⃣ 프로젝트 구조도
![프로젝트 구조도](https://github.com/user-attachments/assets/02392e0f-2606-4177-8cc2-45ed180d1b6b)

**1. 서버(Server)**
  * 기술 스택
    : C++, SQLite3, SQLite-ORM, gRPC, protobuf
  * 인터넷 뱅킹의 핵심 로직 담당
  * gRPC를 이용하여 미들웨어(Spring Boot)와 고속 통신
  * SQLite를 이용해 별도의 설치 없이 경량 FileDB 구축
  * 개발시 SQLite-ORM을 활용해 소스코드에 직접적인 SQL문 없이 DB 접근 및 관리(휴먼에러 감소)
  
**2. 미들웨어(Middleware)**
   * 기술 스택
     : Spring Boot, gRPC, protobuf
   * 클라이언트 요청 처리 및 서버와의 인터페이스 역할 수행
   * 클라이언트와는 REST API를 이용 / 서버와는 gRPC를 이용하여 통신
  
**3. 클라이언트(Client)**
   * 기술 스택
     : React.js, axios
   * Axios를 이용한 REST API 통신
   * UI로 기능 조작
  
**4. 통신 방식 및 데이터 교환**
   * 클라이언트 ↔ 미들웨어: REST API(Axios) 기반 요청/응답
   * 미들웨어 ↔ 서버: gRPC + Protocol Buffers를 활용한 고성능 바이너리 데이터 통신
   * 서버 ↔ 데이터베이스: SQLite ORM을 사용하여 SQL 없이 데이터 조작

## 2️⃣ 클래스 다이어그램
![객체 추상화 다이어그램](https://github.com/user-attachments/assets/cf751aba-d1ff-4fdb-9886-7dbb2733ef66)
* Account 클래스를 기반으로 모든 계좌 유형을 상속을 통해 확장하도록 설계
* 공통 속성과 메서드를 상위 클래스에 정의하여 중복 코드 최소화
* 비즈니스 로직 명확히 정의 - 계좌의 유형별로 담당하는 기능을 명확히 정의

## 3️⃣ ERD
![ERD](https://github.com/user-attachments/assets/4ce797c9-4f5a-46f8-bd2d-75b12a56b1d6)

## 📂 프로젝트 파일 구조
```
├── 3rd_party            #외부 라이브러리
│   └── sqlite_orm 
├── generate_protos.sh   #proto 빌드용
├── protos               #gRPC 프로토콜 버퍼 정의
│   ├── account.proto
│   ├── bank.proto
│   ├── customer.proto
│   └── protoStyle.md   #protobuf 코딩 규칙
├── protos_build        #proto 빌드 후 소스파일 생성 위치
├── src
│   ├── CMakeLists.txt
│   └── Server
│       ├── CMakeLists.txt
│       ├── common          #프로젝트 내에 필요한 공통 함수
│       │   └── myUtil.h
│       ├── controller         #기능 구현
│       │   ├── account_controller.cc
│       │   ├── account_controller.h
│       │   ├── customer_controller.cc
│       │   ├── customer_controller.h
│       │   ├── transaction_controller.cc
│       │   └── transaction_controller.h
│       ├── db
│       │   ├── bank
│       │   │   ├── bank_database.h         #tables를 이용하여 DB instance 생성 및 관리
│       │   │   ├── tables                  #DB table 생성 및 CRUD 기능
│       │   │   │   ├── accountdb.cc
│       │   │   │   ├── accountdb.h
│       │   │   │   ├── customerdb.cc
│       │   │   │   ├── customerdb.h
│       │   │   │   ├── fixedDepositdb.cc
│       │   │   │   ├── fixedDepositdb.h
│       │   │   │   ├── savingsdb.cc
│       │   │   │   ├── savingsdb.h
│       │   │   │   ├── transaction_logdb.cc
│       │   │   │   └── transaction_logdb.h
│       │   │   └── utils
│       │   │       └── get_current_time.h
│       │   ├── core      #싱글톤 패턴을 이용하여 sqlite와 연동
│       │   │   ├── database.cc
│       │   │   └── database.h
│       │   └── tableTree    #ERD
│       ├── grpcService     #API 구현
│       │   ├── bankManagerImpl.cc
│       │   └── bankManagerImpl.h
│       ├── main
│       │   └── test
│       ├── main.cc         #메인 실행파일
│       ├── services.cc     #gRPC 연동 소스파일
│       └── services.h      #gRPC 연동 헤더파일
└── 회의록             #리팩토링 작업 과정
```
