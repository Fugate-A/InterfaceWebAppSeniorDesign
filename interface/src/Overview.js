import React, { useState } from 'react';
import { Link } from 'react-router-dom';
import Moveable from 'react-moveable';
import './Overview.css';

const Overview = () => {
  const [items, setItems] = useState(
    Array.from({ length: 9 }, (_, index) => ({
      id: index + 1,
      x: (index % 3) * 120 + 60, // Center X position
      y: Math.floor(index / 3) * 120 + 60, // Center Y position
      width: 100,
      height: 100,
      rotation: 0
    }))
  );

  const handleDrag = (id, { left, top }) => {
    setItems(prevItems =>
      prevItems.map(item =>
        item.id === id
          ? {
              ...item,
              x: left + item.width / 2,
              y: top + item.height / 2
            }
          : item
      )
    );
  };

  const handleRotate = (id, { rotate }) => {
    setItems(prevItems =>
      prevItems.map(item =>
        item.id === id
          ? {
              ...item,
              rotation: rotate
            }
          : item
      )
    );
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
              boxSizing: 'border-box'
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
            <div className="box">
              Box #{id}
            </div>
          </div>
        ))}
      </div>
      <div className="coordinates">
        {items.map(({ id, x, y, rotation }) => (
          <div key={id} className="position-line">
            <p>Box #{id} pos: x: {x}px - y: {y}px - rotation: {rotation}°</p>
            <input
              type="number"
              value={rotation}
              onChange={(e) => handleRotate(id, { rotate: Math.round(parseFloat(e.target.value) / 5) * 5 })}
              step="5"
              min="0"
              max="360"
            />
            <span>°</span>
          </div>
        ))}
      </div>
    </div>
  );
};

export default Overview;
