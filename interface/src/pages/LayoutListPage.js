import React, { useEffect, useState } from 'react';
import { Link } from 'react-router-dom';
import LayoutCard from '../components/LayoutCard'; // Import the LayoutCard component

const LayoutListPage = () => {
  const [layouts, setLayouts] = useState([]);

  const fetchLayouts = () => {
    fetch(`${process.env.REACT_APP_API_URL}/api/load-layouts`)
      .then((response) => response.json())
      .then((data) => setLayouts(data.layouts))
      .catch((error) => console.error('Error loading layouts:', error));
  };

  useEffect(() => {
    fetchLayouts(); // Load layouts when component mounts

    // Optional: Set up a periodic refresh (e.g., every 60 seconds)
    const interval = setInterval(fetchLayouts, 60000); // Refresh every 60 seconds

    return () => clearInterval(interval); // Clean up interval on component unmount
  }, []);

  return (
    <div>
      <header>
        <nav>
          <ul>
            <li>
              <Link to="/">Home</Link> {/* Link back to the main page */}
            </li>
            <li>
              <button onClick={fetchLayouts}>Refresh Layouts</button> {/* Button to manually refresh */}
            </li>
          </ul>
        </nav>
      </header>
      <h1>Layouts</h1>
      {layouts.length === 0 ? (
        <p>No layouts found.</p> // Message if no layouts are available
      ) : (
        layouts.map((layout) => (
          <LayoutCard key={layout._id} layout={layout} /> // Render each layout using LayoutCard
        ))
      )}
    </div>
  );
};

export default LayoutListPage;
