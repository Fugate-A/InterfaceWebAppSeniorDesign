import React from 'react';
import { BrowserRouter as Router, Routes, Route, Link, useNavigate } from 'react-router-dom';
import Button from './ButtonExample'; // Assuming you have a ButtonExample component
import Overview from './Overview'; // Import the Overview page component

function App() {
  // Use the useNavigate hook to programmatically navigate to another route
  const navigate = useNavigate();

  // Function to handle button click and navigate to Overview page
  const handleNavigateToOverview = () => {
    navigate('/overview'); // Navigate to the Overview page
  };

  return (
    <div className="App">
      <header className="App-header">
        <h1>Home Page</h1> {/* Main title for Home Page */}
        <Button /> {/* Example Button */}
        <h2>Welcome to the Home Page!</h2>
        <p>Click the button below to navigate to the Overview page.</p>
        <button onClick={handleNavigateToOverview}>Go to Overview</button> {/* Navigate button */}
      </header>
      <nav>
        <ul>
          <li>
            <Link to="/overview">Overview</Link> {/* Link to Overview */}
          </li>
        </ul>
      </nav>
    </div>
  );
}

// Main component to wrap App with Router
function Main() {
  return (
    <Router>
      <Routes>
        <Route path="/" element={<App />} /> {/* Set App as Home */}
        <Route path="/overview" element={<Overview />} /> {/* Overview Route */}
      </Routes>
    </Router>
  );
}

export default Main; // Export Main component
