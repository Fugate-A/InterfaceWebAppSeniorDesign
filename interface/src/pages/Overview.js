import React, { useEffect, useState } from 'react';
import './Overview.css'; 
import io from 'socket.io-client'; // Import Socket.IO client

// Initialize WebSocket connection to the WebSocket server (use your WebSocket port, likely 8081)
const socket = io(`${process.env.REACT_APP_SOCKET_URL || 'http://localhost:8081'}`); 

const Overview = () => {
  const [layouts, setLayouts] = useState([]);
  const [selectedLayout, setSelectedLayout] = useState(null); 
  const [errorMessage, setErrorMessage] = useState('');

  useEffect(() => {
    fetchLayouts();

    // WebSocket event listeners
    socket.on('message', (message) => {
      console.log('Message from server:', message);
    });

    socket.on('esp-message', (message) => {
      console.log('Message from ESP32:', message);
      // Handle ESP32 messages if needed
    });

    // Clean up the socket connection when the component unmounts
    return () => {
      socket.off('message');
      socket.off('esp-message');
    };
  }, []);

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
        setSelectedLayout(layout);
        setErrorMessage('');
      } catch (error) {
        console.error('Error loading layout details:', error);
        setErrorMessage('Failed to load layout details. Please try again later.');
      }
    }
  };

  // Function to send a command to the ESP32
  const sendCommandToESP = (command) => {
    console.log('Sending command to ESP32:', command);
    socket.emit('message', command); // Send the command to the WebSocket server
  };

  return (
    <div>
      <h1>Layout Overview</h1>

      {/* Display error message if any */}
      {errorMessage && <p style={{ color: 'red' }}>{errorMessage}</p>}

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

          {/* Button to send command to ESP32 */}
          <button onClick={() => sendCommandToESP('MOVE_CHAIRS')}>Send Command to ESP32</button>
        </div>
      )}
    </div>
  );
};

export default Overview;
