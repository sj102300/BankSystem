# BankSystem 개선사항

## 1. ATM 클래스 싱글톤 패턴 적용
- ATM 클래스를 싱글톤 패턴으로 변경하여 단일 인스턴스만 생성되도록 수정
- 복사 및 이동 생성자/할당 연산자를 삭제하여 인스턴스 복제 방지
- static 메서드들을 인스턴스 메서드로 변경

## 2. SQLite 데이터베이스 통합
- SQLite를 사용하여 영구적인 데이터 저장소 구현
- 계좌 정보를 저장하는 accounts 테이블 생성
- 거래 내역을 기록하는 transactions 테이블 생성

## 3. 거래 로깅 시스템
- 모든 입출금 거래에 대한 자동 로깅 기능 추가
- 거래 유형, 금액, 시간 등 상세 정보 기록
- 계좌별 거래 내역 조회 기능 구현

## 4. 데이터베이스 스키마

### accounts 테이블
```sql
CREATE TABLE accounts (
    account_number TEXT PRIMARY KEY,
    customer_name TEXT NOT NULL,
    balance REAL NOT NULL
);
```

### transactions 테이블
```sql
CREATE TABLE transactions (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    account_number TEXT NOT NULL,
    type TEXT NOT NULL,
    amount REAL NOT NULL,
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
);
```
