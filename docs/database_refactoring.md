# 데이터베이스 구조 개선

## 개선 사항
1. 객체지향적 설계 적용
   - 각 테이블을 독립적인 헤더 파일로 분리
   - 데이터베이스 접근을 위한 싱글톤 패턴 구현
   - 상속을 통한 확장 가능한 구조 설계

2. 디렉토리 구조 개선
   - core/: 데이터베이스 핵심 인터페이스
   - bank/: 은행 시스템 관련 데이터베이스 구현
   - bank/models/: 은행 시스템 데이터 모델

## 파일 구조
```
src/db/
├── core/           # 데이터베이스 핵심 인터페이스
│   └── database.h
│   └── database.cc
├── bank/           # 은행 관련 데이터베이스
│   ├── models/     # 은행 데이터 모델
│   │   ├── customer.h
│   │   ├── account.h
│   │   └── transaction_log.h
│   └── bank_database.h
```

## 확장성
1. 새로운 데이터베이스 추가
   - core/database.h를 상속받아 새로운 데이터베이스 클래스 구현 가능
   - 각 데이터베이스는 독립적인 디렉토리에서 관리

2. 모듈화
   - 각 데이터베이스의 모델과 구현이 분리되어 있음
   - 코드의 재사용성과 유지보수성 향상

## 사용 방법
```cpp
// 데이터베이스 초기화
auto db = BankDatabase::getInstance("bank.db");
db->initStorage();

// 데이터베이스 접근
auto& storage = db->getStorage();

// 예시: 고객 정보 조회
auto customers = storage.get_all<Customer>();
```

## 장점
1. 코드의 모듈화
   - 각 테이블 관련 코드가 독립적으로 관리됨
   - 유지보수가 용이해짐

2. 싱글톤 패턴
   - 데이터베이스 연결의 일관성 보장
   - 리소스 효율적 관리

3. 확장성
   - 새로운 테이블 추가가 용이
   - 다른 종류의 데이터베이스로 전환 가능
