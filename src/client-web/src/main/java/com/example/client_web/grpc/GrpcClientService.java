package com.example.client_web.grpc;

import bank.Bank;
import bank.BankServiceGrpc;
import bank.account.Account;
import bank.customer.Customer;
import io.grpc.ManagedChannel;
import io.grpc.ManagedChannelBuilder;
import jdk.jfr.Unsigned;
import org.springframework.stereotype.Service;

@Service
public class GrpcClientService {
    private final BankServiceGrpc.BankServiceBlockingStub stub;

    public GrpcClientService() {
        // gRPC 서버에 연결 (gRPC 서버가 실행 중이어야 함)
        ManagedChannel channel = ManagedChannelBuilder.forAddress("172.22.189.79", 3001)
                .usePlaintext()
                .build();

        this.stub = BankServiceGrpc.newBlockingStub(channel);
    }

    public Customer.LogInResponse Login(String userId, String password) {
        Customer.LogInRequest req = Customer.LogInRequest.newBuilder()
                .setUserID(userId).setPassword(password).build();
        return stub.login(req);
    }

    public Account.CreateFixedDepositAccountResponse CreateFixedDepositAccount(Account.CreateFixedDepositAccountRequest request) {
        return stub.createFixedDepositAccount(request);
    }

    public Bank.DepositResponse deposit(long amount) {
        Bank.DepositRequest request = Bank.DepositRequest.newBuilder()
                .setInputMoney(amount)
                .build();

        return stub.deposit(request);
    }
}
