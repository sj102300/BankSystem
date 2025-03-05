import React, { useState } from 'react';
import { useNavigate } from 'react-router-dom';
import axios from 'axios';
import './CreateFixedDepositAccount.css';

const CreateFixedDepositAccount = () => {
  const navigate = useNavigate();
  const [formData, setFormData] = useState({
    cusId: '',
    interestRate: 2.0, // 기본값 설정
    monthlyPayment: '',
    duedate: ''
  });
  const [error, setError] = useState('');

  const handleChange = (e) => {
    const { name, value } = e.target;
    setFormData(prevState => ({
      ...prevState,
      [name]: value
    }));
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    setError('');

    // 데이터 유효성 검사
    const validatedData = {
      cusId: parseInt(formData.cusId),
      interestRate: parseFloat(formData.interestRate),
      monthlyPayment: parseInt(formData.monthlyPayment),
      duedate: formData.duedate
    };

    console.log("보낼 데이터:", JSON.stringify(validatedData));

    try {
      const response = await axios.post('/api/accounts/fixed-deposit', validatedData, {
        headers: {
          'Content-Type': 'application/json'
        }
      });

      if (response.data) {
        console.log('정기예금 계좌 생성 성공:', response.data);
        navigate('/dashboard/accounts'); // 계좌 목록으로 돌아가기
      }
    } catch (error) {
      console.error('정기예금 계좌 생성 실패:', error);
      setError(error.response?.data?.message || '정기예금 계좌 생성에 실패했습니다.');
    }
  };

  return (
    <div className="create-account-container">
      <div className="create-account-box">
        <h2>정기예금 계좌 생성</h2>
        <form onSubmit={handleSubmit}>
          <div className="form-group">
            <label htmlFor="cusId">고객 ID</label>
            <input
              type="number"
              id="cusId"
              name="cusId"
              value={formData.cusId}
              onChange={handleChange}
              required
            />
          </div>
          <div className="form-group">
            <label htmlFor="interestRate">이자율 (%)</label>
            <input
              type="number"
              id="interestRate"
              name="interestRate"
              step="0.1"
              value={formData.interestRate}
              onChange={handleChange}
              required
            />
          </div>
          <div className="form-group">
            <label htmlFor="monthlyPayment">월 납입금</label>
            <input
              type="number"
              id="monthlyPayment"
              name="monthlyPayment"
              value={formData.monthlyPayment}
              onChange={handleChange}
              required
            />
          </div>
          <div className="form-group">
            <label htmlFor="duedate">만기일</label>
            <input
              type="date"
              id="duedate"
              name="duedate"
              value={formData.duedate}
              onChange={handleChange}
              required
            />
          </div>
          {error && <div className="error-message">{error}</div>}
          <div className="button-group">
            <button type="submit" className="submit-button">
              계좌 생성
            </button>
            <button
              type="button"
              className="cancel-button"
              onClick={() => navigate('/dashboard/accounts')}
            >
              취소
            </button>
          </div>
        </form>
      </div>
    </div>
  );
};

export default CreateFixedDepositAccount;
