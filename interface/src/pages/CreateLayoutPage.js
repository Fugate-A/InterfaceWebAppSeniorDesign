import React, { useState } from 'react';
import BoxForm from '../components/BoxForm';

const CreateLayoutPage = () => {
  const [boxes, setBoxes] = useState([]);
  const [name, setName] = useState('');

  const handleSaveBox = (box) => {
    setBoxes([...boxes, box]);
  };

  const handleSaveLayout = () => {
    const layout = { name, boxes };
    fetch(`${process.env.REACT_APP_API_URL}/api/save-layout`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(layout),
    })
      .then((response) => response.json())
      .then((data) => console.log('Layout saved:', data))
      .catch((error) => console.error('Error saving layout:', error));
  };

  return (
    <div>
      <h1>Create New Layout</h1>
      <input
        type="text"
        value={name}
        onChange={(e) => setName(e.target.value)}
        placeholder="Layout Name"
      />
      <BoxForm onSave={handleSaveBox} />
      <button onClick={handleSaveLayout}>Save Layout</button>
    </div>
  );
};

export default CreateLayoutPage;
