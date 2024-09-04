import React from 'react';
import Moveable from 'react-moveable';
import './Overview.css'; // Reuse the same CSS as the CreateLayoutPage

const LayoutDetailsModal = ({ layout, onClose }) => {
  const boxes = layout.items || []; // Get the boxes from the layout data

  return (
    <div className="modal-overlay">
      <div className="modal-content">
        <button onClick={onClose}>Close</button> {/* Close button */}
        <h2>{layout.name || 'Layout Details'}</h2>

        <div className="overview-container" style={{ overflow: 'auto' }}>
  <div
    className="boundary"
    style={{
      width: '1200px', // Increase width to make the boundary larger
      height: '800px', // Increase height to make the boundary larger
      border: '2px solid black', // Retain the black boundary
      position: 'relative',
      margin: 'auto',
    }}
  >
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
            boxSizing: 'border-box',
                  }}
                >
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
              </div>
            ))}
          </div>
        </div>
      </div>
    </div>
  );
};

export default LayoutDetailsModal;
