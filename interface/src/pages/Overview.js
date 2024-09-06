import React, { useState, useCallback, useEffect } from 'react';
import { Link } from 'react-router-dom';
import Moveable from 'react-moveable';
import '../components/Overview.css';

const Overview = () => {
  const [items, setItems] = useState([]);
  const [layouts, setLayouts] = useState([]);
  const [selectedLayoutId, setSelectedLayoutId] = useState(null);
  const [isReconfiguring, setIsReconfiguring] = useState(false);
  const [isLayoutSelectionOpen, setIsLayoutSelectionOpen] = useState(false);
  const [initialLayoutLoaded, setInitialLayoutLoaded] = useState(false);

  const apiUrl = process.env.REACT_APP_API_URL;

  // Fetch available layouts from the server
  const fetchLayouts = useCallback(() => {
    if (!apiUrl) {
      console.error("API URL is undefined. Please check your environment variables.");
      return;
    }

    fetch(`${apiUrl}/api/load-layouts`)
      .then((response) => response.json())
      .then((data) => {
        const loadedLayouts = data.layouts || [];
        setLayouts(loadedLayouts);

        if (loadedLayouts.length > 0) {
          // Load the first layout initially
          const defaultLayoutId = loadedLayouts[0]._id;
          setSelectedLayoutId(defaultLayoutId);
          fetchLayoutConfiguration(defaultLayoutId);
        }
      })
      .catch((error) => console.error('Error loading layouts:', error));
  }, [apiUrl]);

  // Fetch configuration for a selected layout
  const fetchLayoutConfiguration = useCallback((layoutId) => {
    if (!apiUrl) {
      console.error("API URL is undefined. Please check your environment variables.");
      return;
    }

    fetch(`${apiUrl}/api/load-configuration/${layoutId}`)
      .then((response) => response.json())
      .then((data) => {
        setItems(data.items);
        setInitialLayoutLoaded(true);
      })
      .catch((error) => console.error('Error loading layout configuration:', error));
  }, [apiUrl]);

  useEffect(() => {
    fetchLayouts();
  }, [fetchLayouts]);

  // Handle layout selection change
  const handleLayoutSelection = (e) => {
    setSelectedLayoutId(e.target.value);
  };

  // Handle the "Enter" button to confirm layout selection
  const handleConfirmSelection = () => {
    if (selectedLayoutId) {
      fetchLayoutConfiguration(selectedLayoutId); // Load the selected layout
      setIsLayoutSelectionOpen(false); // Close the layout selection modal
      setIsReconfiguring(false); // Exit reconfiguring mode
    }
  };

  // Handle the "Reconfigure" button to show layout selection
  const handleReconfigure = () => {
    setIsReconfiguring(true);
    setIsLayoutSelectionOpen(true);
  };

  // Handle the "Save Configuration" button
  const handleSaveConfiguration = () => {
    if (!apiUrl) {
      console.error("API URL is undefined. Please check your environment variables.");
      return;
    }

    const configuration = { items };
    console.log('Saving configuration:', configuration);

    fetch(`${apiUrl}/api/save-configuration`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify(configuration),
    })
      .then((response) => response.json())
      .then((data) => {
        console.log('Configuration saved successfully:', data);
      })
      .catch((error) => console.error('Error saving configuration:', error));
  };

  return (
    <div className="overview-container">
      <nav>
        <ul>
          <li>
            <Link to="/">Home</Link>
          </li>
        </ul>
      </nav>

      {/* Initial layout selection modal */}
      {isLayoutSelectionOpen && (
        <div className="modal">
          <div className="modal-content">
            <h2>Select a Layout</h2>
            <select onChange={handleLayoutSelection} value={selectedLayoutId || ''}>
              <option value="" disabled>Select a layout</option>
              {layouts.map((layout) => (
                <option key={layout._id} value={layout._id}>
                  {layout.layoutName}
                </option>
              ))}
            </select>
            <button onClick={handleConfirmSelection}>Enter</button>
          </div>
        </div>
      )}

      {/* Display layout if not reconfiguring */}
      {!isLayoutSelectionOpen && (
        <div className="boundary">
          <h1>Current Layout</h1>
          <div className="grid-container">
            {items.map(({ id, x, y, width, height, rotation }) => (
              <div
                key={id}
                className={`box-container box-${id}`}
                style={{
                  position: 'absolute',
                  left: `${x - width / 2}px`,
                  top: `${y - height / 2}px`,
                  width: `${width}px`,
                  height: `${height}px`,
                  transform: `rotate(${rotation}deg)`,
                  transformOrigin: 'center center',
                  backgroundColor: 'lightgray',
                  border: '1px solid #333',
                  display: 'flex',
                  alignItems: 'center',
                  justifyContent: 'center',
                  cursor: 'grab',
                  boxSizing: 'border-box',
                }}
              >
                <Moveable
                  target={`.box-${id}`}
                  draggable={true}
                  rotatable={true}
                  throttleDrag={0}
                  throttleRotate={0}
                  onDrag={({ target, left, top }) => {
                    setItems(prevItems => prevItems.map(
                      item => item.id === id ? { ...item, x: left, y: top } : item
                    ));
                  }}
                  onRotate={({ target, beforeRotate, afterRotate }) => {
                    setItems(prevItems => prevItems.map(
                      item => item.id === id ? { ...item, rotation: afterRotate % 360 } : item
                    ));
                  }}
                  edge={false}
                  keepRatio={false}
                />
                <div className="box">Box #{id}</div>
              </div>
            ))}
          </div>
        </div>
      )}

      <div className="coordinates">
        {items.map(({ id, x, y, rotation }) => (
          <div key={id} className="position-line">
            <p>
              Box #{id} pos: x: {x}px - y: {y}px - rotation: {rotation}°
            </p>
          </div>
        ))}
      </div>

      {!isLayoutSelectionOpen && (
        <div>
          <button onClick={handleReconfigure}>Reconfigure</button>
          <button onClick={handleSaveConfiguration}>Save Configuration</button>
        </div>
      )}
    </div>
  );
};

export default Overview;
