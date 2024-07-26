import React from 'react';
import { useNavigate } from 'react-router-dom'; // Import useNavigate hook

const ButtonToPassLanding = () => {
  const navigate = useNavigate(); // Initialize the hook

  const handleClick = () => {
    navigate('/overview'); // Navigate to the Overview page
  };

  return (
    <button onClick={handleClick}>
      Go to Overview Page
    </button>
  );
};

export default ButtonToPassLanding;
