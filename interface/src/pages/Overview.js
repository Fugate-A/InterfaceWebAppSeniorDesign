import React, { useEffect, useState } from 'react';
import './Overview.css'; // Make sure you have some basic styles for the chairs

const Overview = () => {
  const [layouts, setLayouts] = useState([]);
  const [selectedLayout, setSelectedLayout] = useState(null); // Will hold the selected layout's details
  const [errorMessage, setErrorMessage] = useState('');
  const [successMessage, setSuccessMessage] = useState(''); // To show success messages

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
        console.log("Selected Layout Data:", layout); // Log layout data to check the structure
        setSelectedLayout(layout); // Set the selected layout data
        setErrorMessage(''); // Clear any previous error message
      } catch (error) {
        console.error('Error loading layout details:', error);
        setErrorMessage('Failed to load layout details. Please try again later.');
      }
    }
  };

  // Function to handle "Move Forward" button click
  const handleMoveForward = async () => {
    try {
      const response = await fetch(`${process.env.REACT_APP_API_URL}/api/send-command`, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({   "command": "moveForward"
        }), // Send layout ID in the request
      });

      if (response.ok) {
        setSuccessMessage('Move forward command sent successfully.');
      } else {
        throw new Error('Failed to send move forward command');
      }
    } catch (error) {
      console.error('Error sending move forward command:', error);
      setErrorMessage('Failed to send move forward command. Please try again.');
    }
  };

  return (
    <div>
      <h1>Layout Overview</h1>

      {/* Display error message if any */}
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

      {/* Display the selected layout and render the chairs */}
      {selectedLayout && (
        <div>
          <h2>{selectedLayout.layoutName || 'Untitled Layout'}</h2>
          <p>Layout ID: {selectedLayout._id}</p>

          {/* Move Forward button */}
          <button onClick={handleMoveForward}>Move Forward</button>

          {/* Render the chair elements */}
          <div className="layout-container">
            {Array.isArray(selectedLayout.items) && selectedLayout.items.length > 0 ? (
              selectedLayout.items.map((item, index) => (
                <div
                  key={index}
                  className="chair"
                  style={{
                    transform: `translate(${item.x}px, ${item.y}px) rotate(${item.rotation}deg)`,
                    position: 'absolute', // Important for positioning the chairs
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
