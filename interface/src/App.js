import React from 'react';
import { BrowserRouter as Router, Routes, Route, Link, useNavigate } from 'react-router-dom';
import Overview from './pages/Overview';
import CreateLayout from './pages/CreateLayoutPage';
import LoadLayout from './pages/LayoutListPage';
import Recon from './pages/Recon'; // Import the new Recon component
import VisualPos from './pages/VisualPos'; // Import the VisualPos component
import './App.css'; // Import the CSS file

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

  const handleNavigateToVisualPos = () => {
    navigate('/visual-pos'); // Navigate to VisualPos page
  };

  return (
    <div className="App">
      <header className="App-header">
        <h1>ChairGuru</h1>
        <p>Your ultimate solution for chair layout management and configuration</p>
      </header>
      <div className="button-container">
        <button className="main-button" onClick={handleNavigateToOverview}>Overview</button>
        <button className="main-button" onClick={handleNavigateToCreateLayout}>Create New Layout</button>
        <button className="main-button" onClick={handleNavigateToLoadLayout}>Load Existing Layout</button>
        <button className="main-button" onClick={handleNavigateToRecon}>Reconfigure Chairs</button>
        <button className="main-button" onClick={handleNavigateToVisualPos}>Visualize Positions</button> {/* New button */}
      </div>
      <nav className="App-nav">
        <ul>
          <li><Link to="/overview" className="nav-link">Overview</Link></li>
          <li><Link to="/create-layout" className="nav-link">Create Layout</Link></li>
          <li><Link to="/load-layout" className="nav-link">Load Layout</Link></li>
          <li><Link to="/recon" className="nav-link">Reconfigure Chairs</Link></li>
          <li><Link to="/visual-pos" className="nav-link">Visualize Positions</Link></li> {/* New link */}
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
        <Route path="/recon" element={<Recon />} />
        <Route path="/visual-pos" element={<VisualPos />} /> {/* New route */}
      </Routes>
    </Router>
  );
}

export default Main;
