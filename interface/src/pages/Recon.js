import React, { useEffect, useState } from 'react';
import './Recon.css'; // Ensure that you have basic styles for the recon page

const Recon = () => {
  const [layouts, setLayouts] = useState([]);
  const [selectedLayout, setSelectedLayout] = useState(null); // current layout
  const [desiredLayout, setDesiredLayout] = useState(null); // State for desired layout
  const [movementData, setMovementData] = useState(null); // To store movement data from the API
  const [currentPositions, setCurrentPositions] = useState([]); // Positions for animation
  const [loading, setLoading] = useState(true);
  const [errorMessage, setErrorMessage] = useState('');
  const [atFinalLayout, setAtFinalLayout] = useState(false); // Track when chairs reach the final layout
  const [reconFinished, setReconFinished] = useState(false); // Track when reconfiguration is finished

  // Function to fetch layouts
  const fetchLayouts = async () => {
    setLoading(true);
    try {
      const response = await fetch(`${process.env.REACT_APP_API_URL}/api/load-layouts`);
      if (!response.ok) {
        throw new Error('Failed to fetch layouts');
      }
      const data = await response.json();
      setLayouts(data.layouts);
      setLoading(false);
    } catch (error) {
      console.error('Error fetching layouts:', error);
      setErrorMessage('Failed to load layouts. Please try again later.');
      setLoading(false);
    }
  };

  // Load layouts on component mount
  useEffect(() => {
    fetchLayouts();
  }, []);

  // Handle selecting a layout
  const handleLayoutSelection = (event) => {
    const layoutId = event.target.value;
    if (layoutId) {
      const layout = layouts.find((layout) => layout._id === layoutId);
      setSelectedLayout(layout); 
      setCurrentPositions(layout.items || []); // Initialize current positions, handle undefined items
    } else {
      setSelectedLayout(null);
      setCurrentPositions([]); // Clear positions if no layout is selected
    }
  };

  // Handle selecting a desired layout
  const handleDesiredLayoutSelection = (event) => {
    const layoutId = event.target.value;
    if (layoutId) {
      const layout = layouts.find((layout) => layout._id === layoutId);
      setDesiredLayout(layout);
    } else {
      setDesiredLayout(null);
    }
  };

  // Function to handle reconfiguration and fetch movement data
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
          layout1Items: selectedLayout.items || [],
          layout2Items: desiredLayout.items || [],
          obstacles: [] // Add obstacles if any (currently none)
        }),
      });

      if (!moveResponse.ok) {
        throw new Error('Failed to move to the desired layout');
      }

      const result = await moveResponse.json();

      if (result.movements) {
        setMovementData(result.movements); // Store movement paths
        animateChairs(result.movements); // Start animating the chairs
      } else {
        console.error('No movement data returned from the server.');
        alert('Error: No movement data returned.');
      }

    } catch (error) {
      console.error('Error during reconfiguration:', error);
      alert('Failed to reconfigure layout. Please try again.');
    }
  };

  // Function to animate the chairs based on movement path
  const animateChairs = (movements) => {
    if (!movements || !Array.isArray(movements)) {
      console.error('No valid movement data provided.');
      return;
    }

    movements.forEach((movement, index) => {
      let step = 0;
      const interval = setInterval(() => {
        if (step < movement.movementPath.length) {
          setCurrentPositions((prevPositions) => {
            const updatedPositions = [...prevPositions];
            const newPosition = movement.movementPath[step] || {}; // Handle undefined steps
            updatedPositions[index] = constrainToViewport(newPosition); // Constrain to viewport
            console.log(`Chair ${index + 1} position:`, updatedPositions[index]); // Log chair positions
            return updatedPositions;
          });
          step++;
        } else {
          clearInterval(interval); // Stop when movement is complete
          checkIfAllChairsAtFinalPosition();
        }
      }, 100); // Set the speed of the animation (100ms for each step)
    });
  };

  // Constrain chair position to be within the viewport (adjust based on screen size)
  const constrainToViewport = (position) => {
    const viewportWidth = window.innerWidth;
    const viewportHeight = window.innerHeight;

    return {
      x: Math.min(Math.max(position.x, 0), viewportWidth - 50), // Keep within viewport width, assuming chair size is 50px
      y: Math.min(Math.max(position.y, 0), viewportHeight - 50), // Keep within viewport height, assuming chair size is 50px
      rotation: position.rotation || 0, // Ensure the rotation is respected
    };
  };

  // Function to check if all chairs have reached their final position
  const checkIfAllChairsAtFinalPosition = () => {
    if (currentPositions.every((pos, index) => calculateDistance(pos, desiredLayout.items[index]) < 1 && pos.rotation === desiredLayout.items[index].rotation)) {
      setAtFinalLayout(true); // Mark as at final layout when all chairs have reached their target
      setReconFinished(true); // Mark reconfiguration as finished
      console.log("Reconfiguration complete.");
    }
  };

  // Utility function to calculate the distance between two points
  const calculateDistance = (pos1, pos2) => {
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
        style={{
          backgroundColor: selectedLayout && desiredLayout ? 'red' : '', // Change button color to red when both layouts are selected
        }}
      >
        Reconfigure
      </button>

      {reconFinished && (
        <h3>Recon finished</h3> // Final message when reconfiguration is complete
      )}

      {atFinalLayout && (
        <h3>All chairs have reached {desiredLayout.layoutName}</h3>
      )}

      {/* Show error message if there's any */}
      {errorMessage && <p style={{ color: 'red' }}>{errorMessage}</p>}

      {/* Loading state */}
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

          {/* Display the chairs with animation */}
          <div className="layout-display">
            {currentPositions.length > 0 && currentPositions.map((item, index) => (
              item && item.x !== undefined && item.y !== undefined ? ( // Defensive check for undefined x and y
                <div
                  key={index}
                  className="chair"
                  style={{
                    transform: `translate(${item.x}px, ${item.y}px) rotate(${item.rotation || 0}deg)`,
                    position: 'absolute',
                    transition: 'transform 0.1s ease-out', // Smooth transition for animation
                  }}
                >
                  Chair {index + 1} (x: {item.x}, y: {item.y}, rotation: {item.rotation}°)
                </div>
              ) : null // Skip rendering if item is undefined
            ))}
          </div>
        </>
      )}
    </div>
  );
};

export default Recon;
