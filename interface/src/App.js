import React, { useState, useEffect } from 'react';
import { BrowserRouter as Router, Routes, Route, Link } from 'react-router-dom';
import Overview from './pages/Overview';
import CreateLayout from './pages/CreateLayoutPage';
import LoadLayout from './pages/LayoutListPage';
import Recon from './pages/Recon';
import VisualPos from './pages/VisualPos';
import AutoMove from './pages/AutoMove'; // Import the AutoMove component
import './App.css'; // Import the CSS file

function App() {
  const [layouts, setLayouts] = useState([]); // Store the layouts from the database
  const [currentLayoutIndex, setCurrentLayoutIndex] = useState(0); // Index of the currently displayed layout

  // Fetch layouts from the API
  useEffect(() => {
    const fetchLayouts = async () => {
      try {
        const response = await fetch(`${process.env.REACT_APP_API_URL}/api/load-layouts`);
        if (!response.ok) {
          throw new Error('Failed to fetch layouts');
        }
        const data = await response.json();
        setLayouts(data.layouts || []); // Set layouts from the API response
      } catch (error) {
        console.error('Error fetching layouts:', error);
      }
    };

    fetchLayouts();
  }, []);

  // Rotate through the layouts every 3 seconds
  useEffect(() => {
    if (layouts.length > 1) {
      const interval = setInterval(() => {
        setCurrentLayoutIndex((prevIndex) => (prevIndex + 1) % layouts.length);
      }, 3000); // Change layout every 3 seconds

      return () => clearInterval(interval); // Cleanup interval on unmount
    }
  }, [layouts]);

  return (
    <div className="App">
      <header className="App-header">
        <h1>ChairGuru</h1>
        <p>Your ultimate solution for chair layout management and configuration</p>
      </header>

      {/* Navigation Links */}
      <nav className="App-nav">
        <ul>
          <li><Link to="/overview" className="nav-link">Overview</Link></li>
          <li><Link to="/create-layout" className="nav-link">Create Layout</Link></li>
          <li><Link to="/load-layout" className="nav-link">Load Layout</Link></li>
          <li><Link to="/recon" className="nav-link">Reconfigure Chairs</Link></li>
          <li><Link to="/visual-pos" className="nav-link">Visualize Positions</Link></li>
          <li><Link to="/auto-move" className="nav-link">AutoMove</Link></li>
        </ul>
      </nav>

      {/* Layout Rotation */}
      <div className="layout-visual">
        {layouts.length > 0 ? (
          <div>
            <h2>{layouts[currentLayoutIndex]?.layoutName || 'Untitled Layout'}</h2>
            <div className="layout-container">
              {layouts[currentLayoutIndex]?.items?.map((item, index) => (
                <div
                  key={index}
                  className="chair"
                  style={{
                    transform: `translate(${item.x}px, ${item.y}px) rotate(${item.rotation}deg)`,
                  }}
                >
                  Chair {index + 1}
                </div>
              ))}
            </div>
          </div>
        ) : (
          <p>Loading layouts...</p>
        )}
      </div>
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
        <Route path="/visual-pos" element={<VisualPos />} />
        <Route path="/auto-move" element={<AutoMove />} />
      </Routes>
    </Router>
  );
}

export default Main;
