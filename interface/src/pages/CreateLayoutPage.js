import React, { useState, useCallback } from 'react';
import Moveable from 'react-moveable';
import './Overview.css';

const CreateLayoutPage = () => {
  const [boxes, setBoxes] = useState([]);
  const [name, setName] = useState('');

  const apiUrl = process.env.REACT_APP_API_URL; // Use the environment variable

  const handleAddBox = () => {
    setBoxes([...boxes, {
      id: boxes.length + 1,
      x: 100, // Default x position
      y: 100, // Default y position
      width: 100,
      height: 100,
      rotation: 0
    }]);
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
      console.error("API URL is undefined. Please check your environment variables.");
      return;
    }

    const configuration = { items: boxes };  // Wrap boxes in an "items" key to match the API's expected structure
    console.log('Saving configuration:', configuration);

    fetch(`${apiUrl}/api/save-configuration`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify(configuration),
    })
      .then((response) => {
        if (!response.ok) {
          throw new Error(`HTTP error! status: ${response.status}`);
        }
        return response.json();
      })
      .then((data) => {
        console.log('Configuration saved successfully:', data);
      })
      .catch((error) => console.error('Error saving configuration:', error));
  };

  return (
    <div className="overview-container">
      <h1>Create New Layout</h1>
      <input
        type="text"
        value={name}
        onChange={(e) => setName(e.target.value)}
        placeholder="Layout Name"
      />
      <button onClick={handleAddBox}>Add Box</button>
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
                onDrag={({ target, left, top }) => handleDrag(id, { left, top })}
                onRotate={({ target, rotate }) => handleRotate(id, { rotate })}
                edge={false} // Disable resize handles
                keepRatio={false} // Ensure resizing doesn't keep the aspect ratio
              />
              <div className="box">Box #{id}</div>
            </div>
          ))}
        </div>
      </div>
      <div className="coordinates">
        {boxes.map(({ id, x, y, rotation }) => (
          <div key={id} className="position-line">
            <p>
              Box #{id} pos: x: {x}px - y: {y}px - rotation: {rotation}°
            </p>
            <input
              type="number"
              value={rotation}
              onChange={(e) => handleRotationInputChange(id, e.target.value)}
              step="5"
              min="0"
              max="360"
            />
            <span>°</span>
          </div>
        ))}
      </div>
      <button onClick={handleSaveLayout}>Save Layout</button>
    </div>
  );
};

export default CreateLayoutPage;
