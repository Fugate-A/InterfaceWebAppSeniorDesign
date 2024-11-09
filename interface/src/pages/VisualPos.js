import React, { useEffect, useState } from 'react';
import './VisualPos.css'; // Ensure you have the corresponding CSS file for styling

const VisualPos = () => {
  const [positions, setPositions] = useState([]);
  const [loading, setLoading] = useState(true);
  const [errorMessage, setErrorMessage] = useState('');

  // Fetch positions from the server
  const fetchPositions = async () => {
    setLoading(true);
    try {
      const response = await fetch(`${process.env.REACT_APP_API_URL}/api/current-chair-positions`);
      if (!response.ok) {
        throw new Error('Failed to fetch positions');
      }
      const data = await response.json();
      console.log('Fetched Positions:', data.positions); // Debugging
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
    return () => clearInterval(interval); // Cleanup interval on unmount
  }, []);

  // Environment variables for dynamic area and scaling
  const demoRoomWidthMeters = parseFloat(process.env.REACT_APP_DRW) || 2; // Width in meters (default to 2m)
  const scaleFactor = 100; // Pixels per meter (adjust for visualization size)

  const areaWidthPx = demoRoomWidthMeters * scaleFactor; // Total width of the visualization area in pixels
  const areaHeightPx = 200; // Fixed height for simplicity

  // Calculate tag positions relative to anchors
  const calculateTagPosition = (anchorX, anchorY, range) => {
    const adjustedRange = Math.max(0, range); // Ensure non-negative range
    return {
      x: anchorX + adjustedRange * scaleFactor,
      y: anchorY, // Tags remain on the same horizontal level for simplicity
    };
  };

  return (
    <div className="visual-pos-container" style={{ width: `${areaWidthPx}px`, height: `${areaHeightPx}px` }}>
      <h1>Anchor and Tag Positions</h1>
      {loading ? (
        <p>Loading positions...</p>
      ) : errorMessage ? (
        <p className="error">{errorMessage}</p>
      ) : (
        <div className="visualization-area" style={{ position: 'relative', width: '100%', height: '100%' }}>
          {/* Place anchors in fixed positions */}
          <div
            className="anchor-dot"
            style={{ left: '0px', top: `${areaHeightPx / 2}px`, backgroundColor: 'blue' }}
            title="Anchor 1 (Blue - Left)"
          >
            A1
          </div>
          <div
            className="anchor-dot"
            style={{ left: `${areaWidthPx - 20}px`, top: `${areaHeightPx / 2}px`, backgroundColor: 'red' }}
            title="Anchor 2 (Red - Right)"
          >
            A2
          </div>

          {/* Visualize tag positions dynamically */}
          {positions.map((pos, index) => {
            const anchorX = pos.anchorId === '1' ? 0 : areaWidthPx - 20; // Anchor X position (left or right)
            const anchorY = areaHeightPx / 2; // Anchor Y position (centered vertically)
            const tagPosition = calculateTagPosition(anchorX, anchorY, pos.range);

            return (
              <div
                key={index}
                className="tag-dot"
                style={{
                  left: `${tagPosition.x}px`,
                  top: `${tagPosition.y}px`,
                  backgroundColor: 'green',
                }}
                title={`Tag: ${pos.shortAddress}, Anchor: ${pos.anchorId}, Range: ${pos.range}m`}
              ></div>
            );
          })}
        </div>
      )}
    </div>
  );
};

export default VisualPos;
