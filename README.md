# 인터넷 뱅킹 서버 시스템

## 📌 프로젝트 소개
인터넷 뱅킹 서비스의 기본 기능을 제공하는 서버 시스템입니다.

## 📌 개발 목표
- MSA 구조를 통해 확장성 좋은 시스템 구축
- 객체 지향 설계로 코드 재사용성과 유지보수성 향상
- SQLite-ORM을 활용하여 SQL 없이 효율적인 데이터베이스 조작 및 관리
- Protobuf를 사용한 통신 메시지 정의
- gRPC를 활용한 클라이언트-서버 간 고성능 데이터 송수신 구현
- cmake를 활용한 빌드 자동화로 개발 생산성 향상

## 🚀 기술 스택
- **언어**: C++
- **데이터베이스**: SQLite3, SQLite-ORM
- **통신 프로토콜**: gRPC
- **프로토콜 버퍼**: protoc

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
│       │   └── tableTree
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
