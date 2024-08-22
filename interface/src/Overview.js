import React, { useState, useCallback, useEffect } from 'react';
import { Link } from 'react-router-dom';
import Moveable from 'react-moveable';
import './Overview.css';

// Collision blocking
const isOverlapping = (boxA, boxB) => {
  return !(
    boxA.x + boxA.width <= boxB.x ||
    boxA.x >= boxB.x + boxB.width ||
    boxA.y + boxA.height <= boxB.y ||
    boxA.y >= boxB.y + boxB.height
  );
};

// Utility function to get the bounding box of a rotated element
const getBoundingBox = (x, y, width, height, rotation) => {
  const radians = (rotation * Math.PI) / 180;
  const cos = Math.cos(radians);
  const sin = Math.sin(radians);

  const newWidth = Math.abs(width * cos) + Math.abs(height * sin);
  const newHeight = Math.abs(width * sin) + Math.abs(height * cos);

  return {
    x: x - newWidth / 2,
    y: y - newHeight / 2,
    width: newWidth,
    height: newHeight,
  };
};

const Overview = () => {
  const [items, setItems] = useState(
    Array.from({ length: 9 }, (_, index) => ({
      id: index + 1,
      x: (index % 3) * 120 + 60, // Center X position
      y: Math.floor(index / 3) * 120 + 60, // Center Y position
      width: 100,
      height: 100,
      rotation: 0,
    }))
  );

  const apiUrl = process.env.REACT_APP_API_URL; // Use the environment variable

  // Fetch configuration from server
  useEffect(() => {
    fetch(`${apiUrl}/api/load-configuration`)
      .then((response) => response.json())
      .then((data) => {
        setItems(data.items);
      })
      .catch((error) => console.error('Error loading configuration:', error));
  }, [apiUrl]);

  const handleDrag = useCallback((id, { left, top }) => {
    setItems((prevItems) => {
      const newItems = prevItems.map((item) =>
        item.id === id
          ? {
              ...item,
              x: left + item.width / 2,
              y: top + item.height / 2,
            }
          : item
      );

      // Check for overlaps and adjust positions if necessary
      for (let i = 0; i < newItems.length; i++) {
        for (let j = i + 1; j < newItems.length; j++) {
          if (
            isOverlapping(
              getBoundingBox(
                newItems[i].x,
                newItems[i].y,
                newItems[i].width,
                newItems[i].height,
                newItems[i].rotation
              ),
              getBoundingBox(
                newItems[j].x,
                newItems[j].y,
                newItems[j].width,
                newItems[j].height,
                newItems[j].rotation
              )
            )
          ) {
            // Simple response: return the items to the previous state if there's overlap
            return prevItems;
          }
        }
      }

      return newItems;
    });
  }, []);

  const handleRotate = useCallback((id, { rotate }) => {
    setItems((prevItems) =>
      prevItems.map((item) =>
        item.id === id
          ? {
              ...item,
              rotation: rotate % 360,
            }
          : item
      )
    );
  }, []);

  const handleRotationInputChange = (id, value) => {
    const angle = parseFloat(value) || 0;
    setItems((prevItems) =>
      prevItems.map((item) =>
        item.id === id
          ? {
              ...item,
              rotation: angle % 360,
            }
          : item
      )
    );
  };

  const handleSaveConfiguration = () => {
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
      <div className="boundary">
        <div className="grid-container">
          {items.map(({ id, x, y, width, height, rotation }) => (
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
        {items.map(({ id, x, y, rotation }) => (
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
      <button onClick={handleSaveConfiguration}>Save Configuration</button>
    </div>
  );
};

export default Overview;
