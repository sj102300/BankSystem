package com.example.client_web.controller;

import bank.Bank;
import bank.customer.Customer;
import com.example.client_web.dto.LoginRequest;
import com.example.client_web.grpc.GrpcClientService;
import com.example.client_web.service.UserService;
import jakarta.servlet.http.HttpSession;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.Collections;

import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api")
@CrossOrigin(origins = "http://localhost:3000", allowCredentials = "true") // React와 연동할 경우 CORS 설정
public class UserController {

    private final GrpcClientService grpcClientService;

    public UserController(GrpcClientService grpcClientService) {
        this.grpcClientService = grpcClientService;
    }

    @PostMapping("/login")
    public ResponseEntity<?> login(@RequestBody LoginRequest request, HttpSession session) {
            Customer.LogInResponse response = grpcClientService.Login(request.getUsername(), request.getPassword());
            if (response.getSuccess()) {
                return ResponseEntity.ok(Collections.singletonMap("message", "로그인 성공"));
            } else {
                return ResponseEntity.ok(Collections.singletonMap("message", "로그인 fail"));
            }
    }

    @GetMapping("/logout")
    public ResponseEntity<?> logout(HttpSession session) {
        session.invalidate(); // 세션 삭제
        return ResponseEntity.ok(Collections.singletonMap("message", "로그아웃 성공"));
    }
}
