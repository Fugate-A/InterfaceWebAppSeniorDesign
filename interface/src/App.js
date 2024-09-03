import React from 'react';
import { BrowserRouter as Router, Routes, Route, Link, useNavigate } from 'react-router-dom';
import Button from './components/ButtonExample'; // Import ButtonExample from components
import Overview from './pages/Overview'; // Import Overview from pages
import CreateLayout from './pages/CreateLayoutPage'; // Import CreateLayout from pages
import LoadLayout from './pages/LayoutListPage'; // Import LoadLayout from pages

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

  return (
    <div className="App">
      <header className="App-header">
        <h1>Home Page</h1> 
        <Button /> 
        <h2>Welcome to the Home Page!</h2>
        <p>Click the button below to navigate to different pages.</p>
        <button onClick={handleNavigateToOverview}>Go to Overview</button> {/* Navigate button to Overview */}
        <button onClick={handleNavigateToCreateLayout}>Create New Layout</button> {/* Navigate button to CreateLayout */}
        <button onClick={handleNavigateToLoadLayout}>Load Existing Layout</button> {/* Navigate button to LoadLayout */}
      </header>
      <nav>
        <ul>
          <li>
            <Link to="/overview"></Link> {/* Link to Overview */}
          </li>
          <li>
            <Link to="/create-layout"></Link> {/* Link to CreateLayout */}
          </li>
          <li>
            <Link to="/load-layout"></Link> {/* Link to LoadLayout */}
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
        <Route path="/create-layout" element={<CreateLayout />} /> {/* CreateLayout Route */}
        <Route path="/load-layout" element={<LoadLayout />} /> {/* LoadLayout Route */}
      </Routes>
    </Router>
  );
}

export default Main;
