import React, { useState } from 'react';
import { Link } from 'react-router-dom';
import Draggable from 'react-draggable'; // Import Draggable component
import './Overview.css'; // Import CSS for styling

const Overview = () => {
  // Initialize positions and rotations for 9 squares
  const initialItems = Array.from({ length: 9 }, (_, index) => ({
    id: index + 1,
    x: (index % 3) * 120, // Initial X position
    y: Math.floor(index / 3) * 120, // Initial Y position
    rotation: 0
  }));

  const [items, setItems] = useState(initialItems);

  const handleDrag = (e, data, id) => {
    setItems(prevItems =>
      prevItems.map(item =>
        item.id === id
          ? { ...item, x: data.x, y: data.y }
          : item
      )
    );
  };

  const handleRotate = (id) => {
    setItems(prevItems =>
      prevItems.map(item => {
        if (item.id === id) {
          const newRotation = (item.rotation + 45) % 360; // Rotate 45 degrees and limit to 360 degrees
          return { ...item, rotation: newRotation };
        }
        return item;
      })
    );
  };

  return (
    <div className="overview-container">
      <nav>
        <ul>
          <li>
            <Link to="/">Home</Link> {/* Link to home */}
          </li>
        </ul>
      </nav>
      <div className="grid-container">
        {items.map(({ id, x, y, rotation }) => (
          <Draggable
            key={id}
            position={{ x, y }}
            onDrag={(e, data) => handleDrag(e, data, id)}
            onStop={(e, data) => handleDrag(e, data, id)} // Update position after drag stop
          >
            <div
              className="draggable-wrapper"
              style={{
                transform: `rotate(${rotation}deg)`, // Apply rotation
                transformOrigin: 'center center', // Ensure rotation is around center
                position: 'relative',
                width: '100px',
                height: '100px'
              }}
            >
              <div className="square">
                {id}
                <button
                  className="rotate-button"
                  onClick={() => handleRotate(id)} // Rotate 45 degrees on click
                >
                  Rotate
                </button>
              </div>
            </div>
          </Draggable>
        ))}
      </div>
      <div className="coordinates">
        {items.map(({ id, x, y, rotation }) => (
          <p key={id}>Box #{id} pos: x: {x}px - y: {y}px - rotation: {rotation}°</p>
        ))}
      </div>
    </div>
  );
};

export default Overview;
