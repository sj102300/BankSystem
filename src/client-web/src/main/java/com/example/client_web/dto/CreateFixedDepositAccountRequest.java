package com.example.client_web.dto;

public class CreateFixedDepositAccountRequest {
    private Long cusId;
    private Double interestRate;
    private Integer monthlyPayment;
    private String duedate;

    // 기본 생성자
    public CreateFixedDepositAccountRequest() {}

    // 생성자
    public CreateFixedDepositAccountRequest(Long cusId, Double interestRate, Integer monthlyPayment, String duedate) {
        this.cusId = cusId;
        this.interestRate = interestRate;
        this.monthlyPayment = monthlyPayment;
        this.duedate = duedate;
    }

    // Getter & Setter
    public Long getCusId() {
        return cusId;
    }

    public void setCusId(Long cusId) {
        this.cusId = cusId;
    }

    public Double getInterestRate() {
        return interestRate;
    }

    public void setInterestRate(Double interestRate) {
        this.interestRate = interestRate;
    }

    public Integer getMonthlyPayment() {
        return monthlyPayment;
    }

    public void setMonthlyPayment(Integer monthlyPayment) {
        this.monthlyPayment = monthlyPayment;
    }

    public String getDuedate() {
        return duedate;
    }

    public void setDuedate(String duedate) {
        this.duedate = duedate;
    }
}