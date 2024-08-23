import React, { useState } from 'react';

const BoxForm = ({ onSave }) => {
  const [box, setBox] = useState({ x: 0, y: 0, width: 100, height: 100, rotation: 0 });

  const handleChange = (e) => {
    const { name, value } = e.target;
    setBox({ ...box, [name]: value });
  };

  const handleSubmit = (e) => {
    e.preventDefault();
    onSave(box);
  };

  return (
    <form onSubmit={handleSubmit}>
      <input type="number" name="x" value={box.x} onChange={handleChange} placeholder="X position" />
      <input type="number" name="y" value={box.y} onChange={handleChange} placeholder="Y position" />
      <input type="number" name="width" value={box.width} onChange={handleChange} placeholder="Width" />
      <input type="number" name="height" value={box.height} onChange={handleChange} placeholder="Height" />
      <input type="number" name="rotation" value={box.rotation} onChange={handleChange} placeholder="Rotation" />
      <button type="submit">Add Box</button>
    </form>
  );
};

export default BoxForm;
