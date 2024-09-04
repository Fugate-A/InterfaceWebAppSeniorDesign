import React, { useState } from 'react';
import LayoutDetailsModal from './LayoutDetailsModal'; // Import the modal component

const LayoutCard = ({ layout }) => {
  const [showDetails, setShowDetails] = useState(false);

  const handleShowDetails = () => {
    setShowDetails(true);
  };

  const handleCloseDetails = () => {
    setShowDetails(false);
  };

  return (
    <div className="layout-card">
      <h2>{layout.name || 'Untitled Layout'}</h2> {/* Display layout name or a default message */}
      <p>ID: {layout._id}</p> {/* Display layout ID */}
      <button onClick={handleShowDetails}>View Details</button> {/* Button to show details */}

      {showDetails && (
        <LayoutDetailsModal layout={layout} onClose={handleCloseDetails} />
      )}
    </div>
  );
};

export default LayoutCard;
