import React, { useEffect, useState } from 'react';
import { Link } from 'react-router-dom';
import './LayoutListPage.css';

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
    <div className="layout-list-container">
      <header>
        <nav>
          <ul className="nav-links">
            <li>
              <Link to="/" className="nav-link">Home</Link>
            </li>
            <li>
              <button onClick={fetchLayouts} className="refresh-button">Refresh Layouts</button>
            </li>
          </ul>
        </nav>
      </header>
      <h1>Layouts</h1>
      {layouts.length === 0 ? (
        <p className="no-layouts-message">No layouts found.</p>
      ) : (
        <div className="layouts-grid">
          {layouts.map((layout) => (
            <div key={layout._id} className="layout-boundary">
              <h2>{layout.layoutName || 'Untitled Layout'}</h2>
              <div className="boundary">
                {layout.items.map(({ id, x, y, rotation }, index) => (
                  <div
                    key={index}
                    className="chair"
                    style={{
                      left: `${x}px`,
                      top: `${y}px`,
                      transform: `rotate(${rotation}deg)`,
                    }}
                  >
                    Chair {id}
                  </div>
                ))}
              </div>
            </div>
          ))}
        </div>
      )}
    </div>
  );
};

export default LayoutListPage;
