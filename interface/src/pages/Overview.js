import React, { useEffect, useState } from 'react';
import './Overview.css'; // Ensure you have styles for the layout

const Overview = () => {
  const [layouts, setLayouts] = useState([]);
  const [selectedLayout, setSelectedLayout] = useState(null); // Holds the selected layout details
  const [errorMessage, setErrorMessage] = useState('');
  const [successMessage, setSuccessMessage] = useState(''); // For success messages
  const [distance, setDistance] = useState(''); // Distance input

  // Function to fetch all layouts
  const fetchLayouts = async () => {
    try {
      const response = await fetch(`${process.env.REACT_APP_API_URL}/api/load-layouts`);
      const data = await response.json();
      setLayouts(data.layouts);
    } catch (error) {
      console.error('Error fetching layouts:', error);
      setErrorMessage('Failed to load layouts. Please try again later.');
    }
  };

  // Load layouts on component mount
  useEffect(() => {
    fetchLayouts();
  }, []);

  // Handle selecting a layout
  const handleLayoutSelection = async (event) => {
    const layoutId = event.target.value;
    if (layoutId) {
      try {
        const response = await fetch(`${process.env.REACT_APP_API_URL}/api/load-configuration/${layoutId}`);
        if (!response.ok) {
          throw new Error('Network response was not ok');
        }
        const layout = await response.json();
        console.log("Selected Layout Data:", layout);
        setSelectedLayout(layout); // Set selected layout data
        setErrorMessage(''); // Clear any previous error message
      } catch (error) {
        console.error('Error loading layout details:', error);
        setErrorMessage('Failed to load layout details. Please try again later.');
      }
    }
  };

  // Generic function to handle motor commands
  const handleMotorCommand = async (command) => {
    try {
        const module = "motors"; // Specify the module
        const value = parseInt(distance) || 0; // Parse the distance input as an integer, default to 0 if empty

        // Send the module, command, and value fields to the API
        const response = await fetch(`${process.env.REACT_APP_API_URL}/api/send-command`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({
                module,    // Send the module
                command,   // Send the command
                value,     // Send the value
            }),
        });

        if (response.ok) {
            setSuccessMessage(`${command} command sent successfully.`);
        } else {
            const errorResponse = await response.json();
            console.error('Error response:', errorResponse);
            throw new Error(`Failed to send ${command} command`);
        }
    } catch (error) {
        console.error(`Error sending ${command} command:`, error);
        setErrorMessage(`Failed to send ${command} command. Please try again.`);
    }
};

  return (
    <div>
      <h1>Layout Overview</h1>

      {/* Display error or success messages */}
      {errorMessage && <p style={{ color: 'red' }}>{errorMessage}</p>}
      {successMessage && <p style={{ color: 'green' }}>{successMessage}</p>}

      <label htmlFor="layout-select">Choose a layout:</label>
      <select id="layout-select" onChange={handleLayoutSelection}>
        <option value="">--Select a layout--</option>
        {layouts.map((layout) => (
          <option key={layout._id} value={layout._id}>
            {layout.layoutName || 'Untitled Layout'}
          </option>
        ))}
      </select>

      {/* Input box for distance or degree */}
      <div>
        <label htmlFor="distance-input">Enter Distance/Rotation (inches or degrees):</label>
        <input
          id="distance-input"
          type="number"
          value={distance}
          onChange={(e) => setDistance(e.target.value)}
          placeholder="Enter value"
        />
      </div>

      {/* Motor function buttons */}
      <div style={{ marginTop: '10px' }}>
        <button onClick={() => handleMotorCommand('moveForward')}>Move Forward</button>
        <button onClick={() => handleMotorCommand('moveBackward')}>Move Backward</button>
        <button onClick={() => handleMotorCommand('translateLeft')}>Translate Left</button>
        <button onClick={() => handleMotorCommand('translateRight')}>Translate Right</button>
        <button onClick={() => handleMotorCommand('rotateClockwise')}>Rotate Clockwise</button>
        <button onClick={() => handleMotorCommand('rotateCounterClockwise')}>Rotate Counter-Clockwise</button>
        <button onClick={() => handleMotorCommand('estop')}>EMERGENCY</button>
      </div>

      {/* Display the selected layout and render the chairs */}
      {selectedLayout && (
        <div>
          <h2>{selectedLayout.layoutName || 'Untitled Layout'}</h2>
          <p>Layout ID: {selectedLayout._id}</p>

          {/* Render the chair elements */}
          <div className="layout-container">
            {Array.isArray(selectedLayout.items) && selectedLayout.items.length > 0 ? (
              selectedLayout.items.map((item, index) => (
                <div
                  key={index}
                  className="chair"
                  style={{
                    transform: `translate(${item.x}px, ${item.y}px) rotate(${item.rotation}deg)`,
                    position: 'absolute',
                  }}
                >
                  Chair {index + 1}
                </div>
              ))
            ) : (
              <p>No chairs available for this layout.</p>
            )}
          </div>
        </div>
      )}
    </div>
  );
};

export default Overview;
