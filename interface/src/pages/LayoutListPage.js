import React, { useEffect, useState } from 'react';
import { Link } from 'react-router-dom';
import LayoutCard from '../components/LayoutCard';

const LayoutListPage = () => {
  const [layouts, setLayouts] = useState([]);

  const fetchLayouts = () => {
    fetch(`${process.env.REACT_APP_API_URL}/api/load-layouts`)
      .then((response) => response.json())
      .then((data) => setLayouts(data.layouts))
      .catch((error) => console.error('Error loading layouts:', error));
  };

  useEffect(() => {
    fetchLayouts();

    const interval = setInterval(fetchLayouts, 60000);

    return () => clearInterval(interval);
  }, []);

  return (
    <div>
      <header>
        <nav>
          <ul>
            <li>
              <Link to="/">Home</Link>
            </li>
            <li>
              <button onClick={fetchLayouts}>Refresh Layouts</button>
            </li>
          </ul>
        </nav>
      </header>
      <h1>Layouts</h1>
      {layouts.length === 0 ? (
        <p>No layouts found.</p>
      ) : (
        layouts.map((layout) => (
          <LayoutCard key={layout._id} layout={layout} />
        ))
      )}
    </div>
  );
};

export default LayoutListPage;
