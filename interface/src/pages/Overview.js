import React, { useEffect, useState } from 'react';
import './Overview.css'; // Ensure you have styles for the layout

const Overview = () => {
  const [layouts, setLayouts] = useState([]);
  const [selectedLayout, setSelectedLayout] = useState(null); // Holds the selected layout details
  const [selectedChair, setSelectedChair] = useState(''); // Chair selection
  const [errorMessage, setErrorMessage] = useState('');
  const [successMessage, setSuccessMessage] = useState(''); // For success messages
  const [distance, setDistance] = useState(''); // Distance input

  // Function to fetch all layouts
  const fetchLayouts = async () => {
    try {
      const response = await fetch(`${process.env.REACT_APP_API_URL}/api/load-layouts`);
      if (!response.ok) {
        throw new Error('Failed to fetch layouts');
      }
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
        console.log('Selected Layout Data:', layout);
        setSelectedLayout(layout); // Set selected layout data
        setErrorMessage(''); // Clear any previous error message
      } catch (error) {
        console.error('Error loading layout details:', error);
        setErrorMessage('Failed to load layout details. Please try again later.');
      }
    }
  };

  // Handle selecting a chair
  const handleChairSelection = (event) => {
    setSelectedChair(event.target.value); // Update the selected chair
    setErrorMessage(''); // Clear any previous error messages
  };

  // Generic function to handle motor commands
  const handleMotorCommand = async (command) => {
    try {
      if (!selectedChair) {
        setErrorMessage('Please select a chair.');
        return;
      }

      const value = parseInt(distance) || 0; // Parse the distance input as an integer, default to 0 if empty
      const anchorId = selectedChair.toLowerCase(); // Convert to lowercase to match the backend keys

      if (!['chair1', 'chair2'].includes(anchorId)) {
        throw new Error(`Invalid chair ID: ${selectedChair}`);
      }

      // Send the chair ID (anchorId), command, and value fields to the API
      const response = await fetch(`${process.env.REACT_APP_API_URL}/api/send-command`, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({
          anchorId, // Pass the lowercase anchorId
          command,  // Pass the command
          value,    // Pass the value
        }),
      });

      if (response.ok) {
        setSuccessMessage(`${command} command sent successfully to ${selectedChair}.`);
      } else {
        const errorResponse = await response.json();
        console.error('Error response:', errorResponse);
        setErrorMessage(errorResponse.error || `Failed to send ${command} command.`);
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
  
      {/* Inputs and Buttons side by side */}
      <div className="overview-container">
        <div className="input-container">
          <label htmlFor="layout-select">Choose a layout:</label>
          <select id="layout-select" onChange={handleLayoutSelection}>
            <option value="">--Select a layout--</option>
            {layouts.map((layout) => (
              <option key={layout._id} value={layout._id}>
                {layout.layoutName || 'Untitled Layout'}
              </option>
            ))}
          </select>
  
          <label htmlFor="chair-select">Select Chair:</label>
          <select id="chair-select" onChange={handleChairSelection} value={selectedChair}>
            <option value="">--Select a Chair--</option>
            <option value="chair1">Chair 1 (192.168.4.3)</option>
            <option value="chair2">Chair 2 (192.168.4.4)</option>
          </select>
  
          <label htmlFor="distance-input">Enter Distance/Rotation (1m F-B = 655 : 360dgr = 1625):</label>
          <input
            id="distance-input"
            type="number"
            value={distance}
            onChange={(e) => setDistance(e.target.value)}
            placeholder="Enter value"
          />
        </div>
  
        {/* Motor function buttons */}
        <div className="button-container">
  <div className="button-row">
    <button onClick={() => handleMotorCommand('moveForward')}>Move Forward</button>
    <button onClick={() => handleMotorCommand('moveBackward')}>Move Backward</button>
  </div>
  <div className="button-row">
    <button onClick={() => handleMotorCommand('translateLeft')}>Translate Left</button>
    <button onClick={() => handleMotorCommand('translateRight')}>Translate Right</button>
  </div>
  <div className="button-row">
    <button onClick={() => handleMotorCommand('rotateClockwise')}>Rotate Clockwise</button>
    <button onClick={() => handleMotorCommand('rotateCounterClockwise')}>Rotate Counter-Clockwise</button>
  </div>
  <div className="button-row">
    <button className="emergency" onClick={() => handleMotorCommand('estop')}>EMERGENCY</button>
  </div>
</div>

      </div>
  
      {/* Layout box below */}
      {selectedLayout && (
        <div>
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
