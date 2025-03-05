import React from 'react';
import { Outlet, useNavigate } from 'react-router-dom';
import { useAuth } from '../../context/AuthContext';
import './Dashboard.css';

const Dashboard = () => {
  const { user, logout } = useAuth();
  const navigate = useNavigate();

  const handleLogout = () => {
    logout();
    navigate('/login');
  };

  const menuItems = [
    { id: 'account', title: '계좌 목록', path: '/dashboard/accounts' },
    { id: 'create-fixed-deposit', title: '정기예금 계좌 생성', path: '/dashboard/accounts/create-fixed-deposit' },
    // 추후 메뉴 추가 예정
  ];

  return (
    <div className="dashboard-container">
      <div className="dashboard-sidebar">
        <div className="user-info">
          <span>👤 {user?.username || '사용자'}</span>
          <button onClick={handleLogout} className="logout-button">로그아웃</button>
        </div>
        <nav className="menu-list">
          {menuItems.map((item) => (
            <button
              key={item.id}
              className="menu-item"
              onClick={() => navigate(item.path)}
            >
              {item.title}
            </button>
          ))}
        </nav>
      </div>
      <div className="dashboard-content">
        <Outlet />
      </div>
    </div>
  );
};

export default Dashboard;
