import React from 'react';
import { Link } from 'react-router-dom';

const LayoutCard = ({ layout }) => {
  return (
    <div className="layout-card">
      <h2>{layout.name || 'Untitled Layout'}</h2> {/* Display layout name or a default message */}
      <p>ID: {layout._id}</p> {/* Display layout ID */}
      {/* Optionally display other details or a preview */}
      <Link to={`/layouts/${layout._id}`}>View Details</Link> {/* Link to a detail page */}
    </div>
  );
};

export default LayoutCard;
