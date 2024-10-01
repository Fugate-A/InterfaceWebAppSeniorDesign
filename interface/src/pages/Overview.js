import React, { useEffect, useState } from 'react';
import LayoutDetailsModal from '../components/LayoutDetailsModal';

const Overview = () => {
  const [layouts, setLayouts] = useState([]);
  const [selectedLayout, setSelectedLayout] = useState(null);
  const [isModalOpen, setIsModalOpen] = useState(false);
  const [errorMessage, setErrorMessage] = useState('');

  // Function to fetch all layouts
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

  // Load layouts on component mount
  useEffect(() => {
    fetchLayouts();
  }, []);

  const handleLayoutSelection = async (event) => {
    const layoutId = event.target.value;
    if (layoutId) {
      try {
        const response = await fetch(`${process.env.REACT_APP_API_URL}/api/load-configuration/${layoutId}`);
        if (!response.ok) {
          throw new Error('Network response was not ok');
        }
        const layout = await response.json();
        setSelectedLayout(layout);
        setIsModalOpen(true);
        setErrorMessage(''); // Clear any previous error message
      } catch (error) {
        console.error('Error loading layout details:', error);
        setErrorMessage('Failed to load layout details. Please try again later.');
      }
    }
  };

  const closeModal = () => {
    setIsModalOpen(false);
    setSelectedLayout(null);
  };

  return (
    <div>
      <h1>Layout Overview</h1>

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

      {isModalOpen && selectedLayout && (
        <LayoutDetailsModal layout={selectedLayout} onClose={closeModal} />
      )}
    </div>
  );
};

export default Overview;
