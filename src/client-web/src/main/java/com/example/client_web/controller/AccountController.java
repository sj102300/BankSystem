package com.example.client_web.controller;

import bank.Bank;
import bank.account.Account;
import bank.customer.Customer;
import com.example.client_web.dto.CreateFixedDepositAccountRequest;
import com.example.client_web.dto.LoginRequest;
import com.example.client_web.grpc.GrpcClientService;
import jakarta.servlet.http.HttpSession;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;

import java.util.Collections;

@RestController
@RequestMapping("/api")
@CrossOrigin(origins = "http://localhost:3000", allowCredentials = "true") // React와 연동할 경우 CORS 설정
public class AccountController {

    private final GrpcClientService grpcClientService;

    public AccountController(GrpcClientService grpcClientService) {
        this.grpcClientService = grpcClientService;
    }

    @PostMapping("/accounts/fixed-deposit")
    public ResponseEntity<?> CreateFixedDepositAccount(@RequestBody CreateFixedDepositAccountRequest request) {
        Account.CreateFixedDepositAccountRequest req = Account.CreateFixedDepositAccountRequest.newBuilder().
                setCusId(request.getCusId()).setInterestRate(request.getInterestRate())
                .setMonthlyPayment(request.getMonthlyPayment()).setDuedate(request.getDuedate()).build();
        Account.CreateFixedDepositAccountResponse response = grpcClientService.CreateFixedDepositAccount(req);
        return ResponseEntity.ok(Collections.singletonMap("정기예금 계좌 ", "생성 성공"));
    }
}