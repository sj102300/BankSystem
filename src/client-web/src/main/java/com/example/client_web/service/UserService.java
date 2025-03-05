package com.example.client_web.service;

import org.springframework.stereotype.Service;

import java.util.HashMap;
import java.util.Map;

@Service
public class UserService {

    private final Map<String, String> users = new HashMap<>();

    public UserService() {
        users.put("admin", "password123"); // 간단한 예제 (실제 환경에서는 DB를 사용해야 함)
    }

    public boolean validateUser(String username, String password) {
        return users.containsKey(username) && users.get(username).equals(password);
    }
}

