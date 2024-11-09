import React, { useEffect, useState } from 'react';
import './VisualPos.css'; // Ensure to create a basic CSS file for visualization

const VisualPos = () => {
  const [positions, setPositions] = useState([]);
  const [loading, setLoading] = useState(true);
  const [errorMessage, setErrorMessage] = useState('');

  const fetchPositions = async () => {
    setLoading(true);
    try {
      const response = await fetch(`${process.env.REACT_APP_API_URL}/api/current-chair-positions`);
      if (!response.ok) {
        throw new Error('Failed to fetch positions');
      }
      const data = await response.json();
      setPositions(data.positions || []);
      setLoading(false);
    } catch (error) {
      console.error('Error fetching positions:', error);
      setErrorMessage('Failed to load positions. Please try again later.');
      setLoading(false);
    }
  };

  useEffect(() => {
    fetchPositions();
    const interval = setInterval(fetchPositions, 1000); // Fetch positions every second
    return () => clearInterval(interval); // Cleanup on unmount
  }, []);

  return (
    <div className="visual-pos-container">
      <h1>Chair Positions</h1>
      {loading ? (
        <p>Loading positions...</p>
      ) : errorMessage ? (
        <p className="error">{errorMessage}</p>
      ) : (
        <div className="visualization-area">
          <div className="center-dot"></div> {/* The central reference point */}
          {positions.map((pos, index) => {
            const distance = pos.range || 0; // Distance from the anchor
            const angle = (index / positions.length) * 2 * Math.PI; // Spread points evenly in a circle
            const x = 200 + distance * Math.cos(angle); // X-coordinate based on distance and angle
            const y = 200 + distance * Math.sin(angle); // Y-coordinate based on distance and angle
            return (
              <div
                key={index}
                className="position-dot"
                style={{
                  left: `${x}px`,
                  top: `${y}px`,
                }}
                title={`Chair: ${pos.shortAddress}, Anchor: ${pos.anchorId}, Range: ${distance}m`}
              ></div>
            );
          })}
        </div>
      )}
    </div>
  );
};

export default VisualPos;
