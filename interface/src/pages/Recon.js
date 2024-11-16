import React, { useEffect, useState } from 'react';
import './Recon.css'; // Ensure that you have basic styles for the recon page

const Recon = () => {
  // Global scaling factors
  const STEPS_PER_METER = 655; // Steps for 1 meter
  const STEPS_PER_ROTATION = 1625; // Steps for 360° rotation
  const BOUNDARY_WIDTH = 500; // Virtual boundary width (e.g., 1000px)
  const REAL_WORLD_WIDTH = 3; // Real-world width in meters

  const pixelToMeter = REAL_WORLD_WIDTH / BOUNDARY_WIDTH;

  // Chair IP mapping
  const chairIPMap = {
    chair1: '192.168.4.3',
    chair2: '192.168.4.4',
  };

  const [layouts, setLayouts] = useState([]);
  const [selectedLayout, setSelectedLayout] = useState(null); // Current layout
  const [desiredLayout, setDesiredLayout] = useState(null); // Desired layout
  const [currentPositions, setCurrentPositions] = useState([]); // Positions for animation
  const [loading, setLoading] = useState(true);
  const [errorMessage, setErrorMessage] = useState('');
  const [atFinalLayout, setAtFinalLayout] = useState(false); // Track when chairs reach the final layout
  const [reconFinished, setReconFinished] = useState(false); // Track when reconfiguration is finished

  // Scale pixel coordinates to real-world meters
  const scaleToMeters = (value) => (value / BOUNDARY_WIDTH) * REAL_WORLD_WIDTH;

  // Scale meters back to pixels for visualization
  const scaleToPixels = (value) => (value / REAL_WORLD_WIDTH) * BOUNDARY_WIDTH;

  // Fetch layouts from the backend
  const fetchLayouts = async () => {
    setLoading(true);
    try {
      const response = await fetch(`${process.env.REACT_APP_API_URL}/api/load-layouts`);
      if (!response.ok) {
        throw new Error('Failed to fetch layouts');
      }
      const data = await response.json();

      // Scale database-stored positions to match the boundary
      const scaledLayouts = data.layouts.map((layout) => ({
        ...layout,
        items: layout.items.map((item) => ({
          ...item,
          x: scaleToPixels(item.x),
          y: scaleToPixels(item.y),
        })),
      }));
      setLayouts(scaledLayouts);
      setLoading(false);
    } catch (error) {
      console.error('Error fetching layouts:', error);
      setErrorMessage('Failed to load layouts. Please try again later.');
      setLoading(false);
    }
  };

  useEffect(() => {
    fetchLayouts();
  }, []);

  // Handle layout selection
  const handleLayoutSelection = (event) => {
    const layoutId = event.target.value;
    if (layoutId) {
      const layout = layouts.find((layout) => layout._id === layoutId);
      setSelectedLayout(layout);
      setCurrentPositions(layout.items || []); // Initialize current positions
    } else {
      setSelectedLayout(null);
      setCurrentPositions([]);
    }
  };

  const handleDesiredLayoutSelection = (event) => {
    const layoutId = event.target.value;
    if (layoutId) {
      const layout = layouts.find((layout) => layout._id === layoutId);
      setDesiredLayout(layout);
    } else {
      setDesiredLayout(null);
    }
  };

  // Handle reconfiguration
  const handleReconfigure = async () => {
    if (!selectedLayout || !desiredLayout) {
      alert('Please select both a current layout and a desired layout.');
      return;
    }

    try {
      const moveResponse = await fetch(`${process.env.REACT_APP_API_URL}/api/move-to-layout`, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({
          layout1Items: selectedLayout.items.map((item) => ({
            ...item,
            x: scaleToMeters(item.x),
            y: scaleToMeters(item.y),
          })),
          layout2Items: desiredLayout.items.map((item) => ({
            ...item,
            x: scaleToMeters(item.x),
            y: scaleToMeters(item.y),
          })),
          obstacles: [],
        }),
      });

      if (!moveResponse.ok) {
        throw new Error('Failed to move to the desired layout');
      }

      const result = await moveResponse.json();

      if (result.movements) {
        animateChairs(result.movements); // Start animating chairs
      } else {
        console.error('No movement data returned from the server.');
        alert('Error: No movement data returned.');
      }
    } catch (error) {
      console.error('Error during reconfiguration:', error);
      alert('Failed to reconfigure layout. Please try again.');
    }
  };

  // Send movement command to a specific chair
  const sendMovementCommand = async (anchorId, command, steps) => {
    try {
      if (!anchorId) {
        throw new Error("anchorId is undefined. Command not sent.");
      }

      const chairIP = chairIPMap[anchorId.toLowerCase()]; // Normalize to lowercase
      if (!chairIP) {
        throw new Error(`Unknown anchorId: ${anchorId}`);
      }

      const response = await fetch(`${process.env.REACT_APP_API_URL}/api/send-command`, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({ anchorId, command, value: steps }),
      });

      if (!response.ok) {
        const errorText = await response.text();
        throw new Error(`Failed to send command to ${anchorId}: ${errorText}`);
      } else {
        console.log(`Command sent to ${anchorId}: ${command}, ${steps}`);
      }
    } catch (error) {
      console.error(error.message);
    }
  };

  const animateChairs = (movements) => {
    if (!movements || !Array.isArray(movements)) {
      console.error('No valid movement data provided.');
      return;
    }

    movements.forEach(async (movement, index) => {
      if (!movement || !movement.anchorId || !movement.movementPath) {
        console.error(`Invalid movement data for chair at index ${index}`);
        return;
      }

      const { anchorId, movementPath } = movement;
      const totalDeltaX =
        (movementPath[movementPath.length - 1].x - movementPath[0].x) * pixelToMeter;
      const totalDeltaY =
        (movementPath[movementPath.length - 1].y - movementPath[0].y) * pixelToMeter;
      const totalRotation =
        movementPath[movementPath.length - 1].rotation - movementPath[0].rotation;

      try {
        if (totalDeltaX !== 0) {
          const commandX = totalDeltaX > 0 ? 'translateRight' : 'translateLeft';
          const stepsX = Math.abs(totalDeltaX) * STEPS_PER_METER;
          await sendMovementCommand(anchorId, commandX, Math.round(stepsX));
        }

        if (totalDeltaY !== 0) {
          const commandY = totalDeltaY > 0 ? 'moveForward' : 'moveBackward';
          const stepsY = Math.abs(totalDeltaY) * STEPS_PER_METER;
          await sendMovementCommand(anchorId, commandY, Math.round(stepsY));
        }

        if (totalRotation !== 0) {
          const commandRotation =
            totalRotation > 0 ? 'rotateClockwise' : 'rotateCounterClockwise';
          const stepsRotation =
            Math.abs(totalRotation) * (STEPS_PER_ROTATION / 360);
          await sendMovementCommand(anchorId, commandRotation, Math.round(stepsRotation));
        }

        setCurrentPositions((prevPositions) => {
          const updatedPositions = [...prevPositions];
          updatedPositions[index] = movementPath[movementPath.length - 1];
          return updatedPositions;
        });
      } catch (error) {
        console.error(`Error sending movement commands for chair ${anchorId}:`, error);
      }
    });

    checkIfAllChairsAtFinalPosition();
  };

  const checkIfAllChairsAtFinalPosition = () => {
    if (
      currentPositions.every(
        (pos, index) =>
          calculateDistance(pos, desiredLayout.items[index]) < 0.01 &&
          Math.abs(pos.rotation - desiredLayout.items[index].rotation) < 1
      )
    ) {
      setAtFinalLayout(true);
      setReconFinished(true);
      console.log('Reconfiguration complete.');
    }
  };

  const calculateDistance = (pos1, pos2) => {
    if (!pos1 || !pos2) return Infinity;
    return Math.sqrt(Math.pow(pos2.x - pos1.x, 2) + Math.pow(pos2.y - pos1.y, 2));
  };

  return (
    <div className="recon-container">
      <h1>Reconfiguration</h1>
      <h2>Current Layout: {selectedLayout ? selectedLayout.layoutName : 'No Layout Selected'}</h2>
      <h2>Desired Layout: {desiredLayout ? desiredLayout.layoutName : 'No Desired Layout Selected'}</h2>

      <button
        className="reconfigure-button"
        onClick={handleReconfigure}
        disabled={!selectedLayout || !desiredLayout}
      >
        Reconfigure
      </button>

      {reconFinished && <h3>Recon finished</h3>}
      {atFinalLayout && <h3>All chairs have reached {desiredLayout.layoutName}</h3>}

      {errorMessage && <p style={{ color: 'red' }}>{errorMessage}</p>}

      {loading ? (
        <p>Loading...</p>
      ) : (
        <>
          <label htmlFor="layout-select">Choose a current layout:</label>
          <select id="layout-select" onChange={handleLayoutSelection}>
            <option value="">--Select a layout--</option>
            {layouts.map((layout) => (
              <option key={layout._id} value={layout._id}>
                {layout.layoutName || 'Untitled Layout'}
              </option>
            ))}
          </select>

          <label htmlFor="desired-layout-select">Choose a desired layout:</label>
          <select id="desired-layout-select" onChange={handleDesiredLayoutSelection}>
            <option value="">--Select a desired layout--</option>
            {layouts.map((layout) => (
              <option key={layout._id} value={layout._id}>
                {layout.layoutName || 'Untitled Layout'}
              </option>
            ))}
          </select>

          <div className="layout-display">
            {currentPositions.map((item, index) =>
              item && item.x !== undefined && item.y !== undefined ? (
                <div
                  key={index}
                  className="chair"
                  style={{
                    transform: `translate(${item.x}px, ${item.y}px) rotate(${item.rotation || 0}deg)`,
                    position: 'absolute',
                    transition: 'transform 0.1s ease-out',
                  }}
                >
                  Chair {index + 1} (x: {item.x}, y: {item.y}, rotation: {item.rotation}°)
                </div>
              ) : null
            )}
          </div>
        </>
      )}
    </div>
  );
};

export default Recon;
