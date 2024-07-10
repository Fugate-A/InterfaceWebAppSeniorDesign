import React from 'react';

const Button = () => {
  const handleClick = async () => {
    try {
      const response = await fetch('http://localhost:5000/api/example');
      const data = await response.json();
      console.log(data); // Log the response from backend
    } catch (error) {
      console.error('Error fetching data:', error);
    }
  };

  return (
    <button onClick={handleClick}>
      Click me to call backend API
    </button>
  );
};

export default Button;
