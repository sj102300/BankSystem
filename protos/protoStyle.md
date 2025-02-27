# gRPC 및 Protocol Buffers 명명 규칙

## 1. 서비스 및 메서드 명명 규칙
### 서비스(Service) 이름
- 서비스 이름은 반드시 `PascalCase`를 사용합니다.
- API의 도메인 이름을 반영하여 명명합니다.
- 접미사로 `Service`를 붙이는 것이 일반적입니다.

```proto
service VehicleService {
    rpc GetVehicle (GetVehicleRequest) returns (GetVehicleResponse);
    rpc ListVehicles (ListVehiclesRequest) returns (ListVehiclesResponse);
}
```

## 2. RPC 메서드 명명 규칙
- **메서드 이름은 동사를 포함한 `PascalCase`** 를 사용합니다.
- CRUD 동작을 나타내는 경우 `Get`, `List`, `Create`, `Update`, `Delete`를 사용합니다.
- 단일 리소스를 가져오는 경우 `Get`, 여러 개의 리소스를 반환하는 경우 `List`를 사용합니다.

```proto
service UserService {
    rpc GetUser (GetUserRequest) returns (GetUserResponse);  // 단일 조회
    rpc ListUsers (ListUsersRequest) returns (ListUsersResponse); // 목록 조회
    rpc CreateUser (CreateUserRequest) returns (CreateUserResponse); // 생성
    rpc UpdateUser (UpdateUserRequest) returns (UpdateUserResponse); // 수정
    rpc DeleteUser (DeleteUserRequest) returns (DeleteUserResponse); // 삭제
}
```

## 3. Request 및 Response 메시지 명명 규칙
- `Request` 및 `Response`는 반드시 메서드 이름과 일치해야 합니다.
- 메시지 이름은 `PascalCase`를 사용하며, 뒤에 `Request` 또는 `Response`를 붙입니다.

```proto
message GetUserRequest {
    int64 user_id = 1;
}

message GetUserResponse {
    User user = 1;
}
```

## 4. 메시지 필드 명명 규칙
- 필드 이름은 `snake_case`를 사용합니다.
- 예약어와 충돌하지 않도록 필드명을 정합니다.
- `id`와 같은 주요 식별자는 첫 번째 필드로 배치합니다.

```proto
message User {
    int64 user_id = 1;
    string name = 2;
    string email = 3;
}
```

- 중첩된 데이터 구조의 경우, `repeated` 필드를 사용할 때 `plural` 형태를 사용합니다.

```proto
message ListUsersResponse {
    repeated User users = 1;  // 복수 형태 사용
}
```

## 5. 패키지 및 네임스페이스
- 패키지는 일반적으로 **도메인 기반 네이밍**을 따릅니다.
- 패키지 이름은 `snake_case`를 사용하고, 도메인과 프로젝트명을 반영하여 계층 구조를 만듭니다.

```proto
package com.example.vehicles;
```

### 예제
```proto
syntax = "proto3";

package com.example.user;

service UserService {
    rpc GetUser (GetUserRequest) returns (GetUserResponse);
}

message GetUserRequest {
    int64 user_id = 1;
}

message GetUserResponse {
    User user = 1;
}

message User {
    int64 user_id = 1;
    string name = 2;
    string email = 3;
}
```

## 6. gRPC 스트리밍 명명 규칙
### 서버 스트리밍(Server Streaming)
- 응답이 스트리밍되는 경우 `stream` 키워드를 사용하며, `Subscribe` 또는 `Watch` 등의 명칭을 사용합니다.

```proto
service ChatService {
    rpc SubscribeMessages (SubscribeMessagesRequest) returns (stream ChatMessage);
}
```

### 클라이언트 스트리밍(Client Streaming)
- 일반적으로 `Upload` 등의 동사를 사용합니다.

```proto
service FileService {
    rpc UploadFile (stream FileChunk) returns (UploadFileResponse);
}
```

### 양방향 스트리밍(Bidirectional Streaming)
- `stream`을 요청 및 응답 메시지 양쪽에 사용합니다.

```proto
service ChatService {
    rpc ChatStream (stream ChatMessage) returns (stream ChatMessage);
}
```

## 7. 공통 메시지 패턴
### Pagination (페이지네이션)
- `page_size`와 `page_token`을 사용하여 페이징 처리합니다.

```proto
message ListUsersRequest {
    int32 page_size = 1;
    string page_token = 2;
}

message ListUsersResponse {
    repeated User users = 1;
    string next_page_token = 2;
}
```

### Error Handling (에러 핸들링)
- 표준 gRPC의 **Status API**를 활용하거나, 직접 `error` 메시지를 정의합니다.

```proto
message Error {
    int32 code = 1;
    string message = 2;
}
```

## 8. Field Number 규칙
- `1~15`: 성능 최적화를 위해 작은 크기의 데이터를 저장하는 필드에 사용합니다.
- `16~`: 기본적으로 사용하며, 추가적인 확장을 고려합니다.

## 정리
1. **서비스 이름** → `PascalCase` + `Service` 접미사 (`VehicleService`)
2. **RPC 메서드 이름** → `PascalCase` (`GetUser`, `ListUsers`, `CreateUser`)
3. **Request/Response 메시지** → `PascalCase` + `Request/Response` (`GetUserRequest`, `GetUserResponse`)
4. **필드명** → `snake_case` (`user_id`, `page_token`)
5. **패키지명** → 도메인 기반 (`com.example.user`)
6. **Stream 메서드** → `Subscribe`, `Watch`, `Upload` 등의 키워드 포함
7. **페이지네이션** → `page_size`, `page_token` / `next_page_token` 사용
8. **에러 핸들링** → `Error` 메시지 정의 또는 `gRPC Status API` 사용

