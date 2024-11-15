import React, { useEffect, useState } from 'react';
import './VisualPos.css'; // Ensure you have the corresponding CSS file for styling

const VisualPos = () => {
  const [positions, setPositions] = useState([]);
  const [loading, setLoading] = useState(true);
  const [errorMessage, setErrorMessage] = useState('');
  const [successMessage, setSuccessMessage] = useState('');

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

  // Function to handle sending the tag command
  const handleTagCommand = async () => {
    try {
      const response = await fetch(`${process.env.REACT_APP_API_URL}/api/send-command`, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({
          command: 'pos',
          value: 100, // Send 100 position updates
        }),
      });

      if (!response.ok) {
        throw new Error('Failed to send command');
      }

      const result = await response.json();
      console.log('Command result:', result);
      setSuccessMessage('Tag command sent successfully!');
    } catch (error) {
      console.error('Error sending tag command:', error);
      setErrorMessage('Failed to send tag command. Please try again.');
    }
  };

  // Environment variables for dynamic area and scaling
  const demoRoomWidthMeters = parseFloat(process.env.REACT_APP_DRW) || 2; // Width in meters (default to 2m)
  const scaleFactor = 100; // Pixels per meter (adjust for visualization size)

  const areaWidthPx = demoRoomWidthMeters * scaleFactor; // Total width of the visualization area in pixels
  const areaHeightPx = demoRoomWidthMeters * scaleFactor; // Make it square

  // Calculate triangulated tag position
  const calculateTagPosition = (anchor1, anchor2, range1, range2) => {
    if (!anchor1 || !anchor2 || range1 == null || range2 == null) return null;

    // Anchor positions in the square (in pixels)
    const anchor1Pos = { x: 0, y: 0 }; // Top-left corner
    const anchor2Pos = { x: areaWidthPx, y: 0 }; // Top-right corner

    // Triangulate tag position based on distances
    const x = (Math.pow(range1, 2) - Math.pow(range2, 2) + Math.pow(areaWidthPx / scaleFactor, 2)) / (2 * areaWidthPx / scaleFactor);
    const y = Math.sqrt(Math.abs(Math.pow(range1, 2) - Math.pow(x, 2))); // Use Math.abs to prevent NaN

    return { x: x * scaleFactor, y: y * scaleFactor };
  };

  return (
    <div className="visual-pos-container" style={{ width: `${areaWidthPx}px`, height: `${areaHeightPx}px` }}>
      <h1>Anchor and Tag Positions</h1>
      {successMessage && <p className="success">{successMessage}</p>}
      {errorMessage && <p className="error">{errorMessage}</p>}
      {loading ? (
        <p>Loading positions...</p>
      ) : (
        <div className="visualization-area" style={{ position: 'relative', width: '100%', height: '100%' }}>
          {/* Place anchors in fixed positions */}
          <div
            className="anchor-dot"
            style={{ left: '0px', top: '0px', backgroundColor: 'blue' }}
            title="Anchor 1 (Blue - Top Left)"
          >
            A1
          </div>
          <div
            className="anchor-dot"
            style={{ left: `${areaWidthPx - 20}px`, top: '0px', backgroundColor: 'red' }}
            title="Anchor 2 (Red - Top Right)"
          >
            A2
          </div>

          {/* Visualize triangulated tag positions */}
          {(() => {
            const anchor1 = positions.find((p) => p.anchorId === 'anchor1');
            const anchor2 = positions.find((p) => p.anchorId === 'anchor2');

            if (anchor1 && anchor2) {
              const tagPosition = calculateTagPosition(anchor1, anchor2, anchor1.range, anchor2.range);
              if (tagPosition) {
                return (
                  <div
                    className="tag-dot"
                    style={{
                      left: `${tagPosition.x}px`,
                      top: `${tagPosition.y}px`,
                      backgroundColor: 'green',
                    }}
                    title={`Tag: ${positions[0]?.shortAddress || 'Unknown'}, X: ${(tagPosition.x / scaleFactor).toFixed(2)}m, Y: ${(tagPosition.y / scaleFactor).toFixed(2)}m`}
                  ></div>
                );
              }
            }
            return null;
          })()}
        </div>
      )}
      <button className="tag-command-button" onClick={handleTagCommand}>
        Start Tag Code (100 Updates)
      </button>
    </div>
  );
};

export default VisualPos;
