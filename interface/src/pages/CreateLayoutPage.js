import React, { useState, useCallback } from 'react';
import Moveable from 'react-moveable';
import './CreateLayoutPage.css';

const CreateLayoutPage = () => {
  const [boxes, setBoxes] = useState([]);
  const [name, setName] = useState('');
  const [confirmationMessage, setConfirmationMessage] = useState('');

  const apiUrl = process.env.REACT_APP_API_URL; // Use the environment variable

  const handleAddBox = () => {
    setBoxes([
      ...boxes,
      {
        id: boxes.length + 1,
        x: 100, // Default x position
        y: 100, // Default y position
        width: 100,
        height: 100,
        rotation: 0,
      },
    ]);
  };

  const handleDrag = useCallback((id, { left, top }) => {
    setBoxes((prevBoxes) =>
      prevBoxes.map((box) =>
        box.id === id
          ? {
              ...box,
              x: left + box.width / 2,
              y: top + box.height / 2,
            }
          : box
      )
    );
  }, []);

  const handleRotate = useCallback((id, { rotate }) => {
    setBoxes((prevBoxes) =>
      prevBoxes.map((box) =>
        box.id === id
          ? {
              ...box,
              rotation: rotate % 360,
            }
          : box
      )
    );
  }, []);

  const handleRotationInputChange = (id, value) => {
    const angle = parseFloat(value) || 0;
    setBoxes((prevBoxes) =>
      prevBoxes.map((box) =>
        box.id === id
          ? {
              ...box,
              rotation: angle % 360,
            }
          : box
      )
    );
  };

  const handleSaveLayout = () => {
    if (!apiUrl) {
      console.error('API URL is undefined. Please check your environment variables.');
      return;
    }

    if (!name.trim()) {
      console.error('Layout name is required.');
      return;
    }

    const configuration = { layoutName: name, items: boxes }; // Include layoutName and items
    console.log('Saving configuration:', configuration);

    fetch(`${apiUrl}/api/save-configuration`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify(configuration), // Send layoutName and items
    })
      .then((response) => {
        if (!response.ok) {
          throw new Error(`HTTP error! status: ${response.status}`);
        }
        return response.json();
      })
      .then((data) => {
        console.log('Configuration saved successfully:', data);
        setConfirmationMessage('Layout saved successfully!');
        setTimeout(() => setConfirmationMessage(''), 3000); // Hide message after 3 seconds
      })
      .catch((error) => {
        console.error('Error saving configuration:', error);
        setConfirmationMessage('Failed to save layout.');
        setTimeout(() => setConfirmationMessage(''), 3000);
      });
  };

  return (
    <div className="create-layout-container">
      <h1>Create New Layout</h1>
      <input
        type="text"
        value={name}
        onChange={(e) => setName(e.target.value)}
        placeholder="Layout Name"
      />
      <div className="layout-boundary-section">
        <div className="boundary">
          <div className="grid-container">
            {boxes.map(({ id, x, y, width, height, rotation }) => (
              <div
                key={id}
                className={`box-container box-${id}`}
                style={{
                  position: 'absolute',
                  left: x - width / 2,
                  top: y - height / 2,
                  width: `${width}px`,
                  height: `${height}px`,
                  transform: `rotate(${rotation}deg)`,
                  transformOrigin: 'center center',
                }}
              >
                <Moveable
                  target={`.box-${id}`}
                  draggable={true}
                  rotatable={true}
                  throttleDrag={0}
                  throttleRotate={0}
                  onDrag={({ left, top }) => handleDrag(id, { left, top })}
                  onRotate={({ rotate }) => handleRotate(id, { rotate })}
                />
                <div className="box">Box #{id}</div>
              </div>
            ))}
          </div>
        </div>
        <div className="layout-controls">
          <div className="layout-stats">
            <h2>{name || 'Untitled Layout'}</h2>
            <ul>
              {boxes.map(({ id, x, y, rotation }) => (
                <li key={id}>
                  Box #{id}: x={x}px, y={y}px, rotation=
                  <input
                    type="number"
                    value={rotation}
                    onChange={(e) => handleRotationInputChange(id, e.target.value)}
                    step="5"
                    min="0"
                    max="360"
                  />
                  °
                </li>
              ))}
            </ul>
          </div>
          <div className="button-row">
            <button onClick={handleAddBox}>Add Box</button>
            <button onClick={handleSaveLayout}>Save Layout</button>
            {confirmationMessage && <p className="confirmation-message">{confirmationMessage}</p>}
          </div>
        </div>
      </div>
    </div>
  );
};

export default CreateLayoutPage;
