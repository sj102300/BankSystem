import React, { useState, useEffect } from 'react';
import axios from 'axios';
import './AccountList.css';

const AccountList = () => {
  const [accounts, setAccounts] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  useEffect(() => {
    fetchAccounts();
  }, []);

  const fetchAccounts = async () => {
    try {
      const response = await axios.get('/api/accounts');
      setAccounts(response.data);
      setLoading(false);
    } catch (err) {
      setError('계좌 정보를 불러오는데 실패했습니다.');
      setLoading(false);
    }
  };

  if (loading) return <div className="loading">로딩 중...</div>;
  if (error) return <div className="error">{error}</div>;

  return (
    <div className="account-list-container">
      <h2>계좌 목록</h2>
      <div className="account-grid">
        {accounts.map((account) => (
          <div key={account.id} className="account-card">
            <div className="account-type">{account.accountType}</div>
            <div className="account-number">{account.accountNumber}</div>
            <div className="account-balance">
              잔액: {account.balance.toLocaleString()}원
            </div>
            <div className="account-status">
              상태: <span className={`status-${account.status.toLowerCase()}`}>
                {account.status}
              </span>
            </div>
          </div>
        ))}
      </div>
    </div>
  );
};

export default AccountList;
