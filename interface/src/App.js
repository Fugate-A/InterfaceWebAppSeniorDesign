import React from 'react';
import { BrowserRouter as Router, Routes, Route, Link, useNavigate } from 'react-router-dom';
import Button from './components/ButtonExample'; 
import Overview from './pages/Overview';
import CreateLayout from './pages/CreateLayoutPage';
import LoadLayout from './pages/LayoutListPage'; 
import Recon from './pages/Recon'; // Import the new Recon component

function App() {
  const navigate = useNavigate();

  const handleNavigateToOverview = () => {
    navigate('/overview');
  };

  const handleNavigateToCreateLayout = () => {
    navigate('/create-layout'); 
  };

  const handleNavigateToLoadLayout = () => {
    navigate('/load-layout');
  };

  const handleNavigateToRecon = () => {
    navigate('/recon'); // Navigate to Recon page
  };

  return (
    <div className="App">
      <header className="App-header">
        <h1>Home Page</h1> 
        <Button /> 
        <h2>Welcome to the Home Page!</h2>
        <p>Click the button below to navigate to different pages.</p>
        <button onClick={handleNavigateToOverview}>Go to Overview</button>
        <button onClick={handleNavigateToCreateLayout}>Create New Layout</button>
        <button onClick={handleNavigateToLoadLayout}>Load Existing Layout</button>
        <button onClick={handleNavigateToRecon}>Go to Recon</button> {/* Button to navigate to Recon */}
      </header>
      <nav>
        <ul>
          <li>
            <Link to="/overview">Overview</Link>
          </li>
          <li>
            <Link to="/create-layout">Create Layout</Link>
          </li>
          <li>
            <Link to="/load-layout">Load Layout</Link>
          </li>
          <li>
            <Link to="/recon">Recon</Link> {/* Link to Recon */}
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
        <Route path="/" element={<App />} />
        <Route path="/overview" element={<Overview />} />
        <Route path="/create-layout" element={<CreateLayout />} />
        <Route path="/load-layout" element={<LoadLayout />} />
        <Route path="/recon" element={<Recon />} /> {/* Route for Recon */}
      </Routes>
    </Router>
  );
}

export default Main;
