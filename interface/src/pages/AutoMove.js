import React, { useEffect, useState } from "react";
import "./AutoMove.css"; // Add styles for visualization

const AutoMove = () => {
  const [positions, setPositions] = useState([]);
  const [loading, setLoading] = useState(true);
  const [errorMessage, setErrorMessage] = useState("");
  const [successMessage, setSuccessMessage] = useState("");
  const [targetPosition, setTargetPosition] = useState(null);
  const [tagPosition, setTagPosition] = useState(null);

  const demoRoomWidthMeters = parseFloat(process.env.REACT_APP_DRW) || 3;
  const scaleFactor = 200;
  const areaWidthPx = demoRoomWidthMeters * scaleFactor;
  const areaHeightPx = demoRoomWidthMeters * scaleFactor;

  // Scaling constants for motor commands
  const MOTOR_STEPS_PER_ROTATION = 1625;
  const MOTOR_STEPS_PER_METER = 655;

  const fetchPositions = async () => {
    setLoading(true);
    try {
      const response = await fetch(
        `${process.env.REACT_APP_API_URL}/api/current-chair-positions`
      );
      if (!response.ok) {
        throw new Error("Failed to fetch positions");
      }
      const data = await response.json();
      setPositions(data.positions || []);
      calculateTagPosition(data.positions);
      setLoading(false);
    } catch (error) {
      setErrorMessage("Failed to load positions. Please try again later.");
      setLoading(false);
    }
  };

  useEffect(() => {
    fetchPositions();
    const interval = setInterval(fetchPositions, 1000);
    return () => clearInterval(interval);
  }, []);

  const calculateTagPosition = (positions) => {
    const anchor1 = positions.find((p) => p.anchorId === "Anchor1");
    const anchor2 = positions.find((p) => p.anchorId === "Anchor2");

    if (anchor1 && anchor2) {
      const range1 = parseFloat(anchor1.range);
      const range2 = parseFloat(anchor2.range);

      // Fixed anchor positions
      const x1 = 0,
        y1 = 0; // Anchor 1 (top-left)
      const x2 = demoRoomWidthMeters,
        y2 = 0; // Anchor 2 (top-right)

      // Trilateration formulas
      const d = x2 - x1; // Distance between two anchors (3 meters)
      const ex = (range1 ** 2 - range2 ** 2 + d ** 2) / (2 * d);
      const ey = Math.sqrt(Math.max(0, range1 ** 2 - ex ** 2));

      setTagPosition({ x: ex, y: ey });
    } else {
      setTagPosition(null);
    }
  };

  const handleMapClick = (event) => {
    const rect = event.target.getBoundingClientRect();
    const x = (event.clientX - rect.left) / scaleFactor;
    const y = (event.clientY - rect.top) / scaleFactor;
    setTargetPosition({ x, y });
    setSuccessMessage(`Target position set: X: ${x.toFixed(2)}m, Y: ${y.toFixed(2)}m`);
    setErrorMessage("");
  };

  const calculateSteps = async () => {
    if (!tagPosition || !targetPosition) {
      setErrorMessage("Both tag position and target position are required.");
      return;
    }
  
    // Calculate deltas in meters
    const deltaX = targetPosition.x - tagPosition.x;
    const deltaY = targetPosition.y - tagPosition.y;
  
    // Convert deltas to motor steps and apply scaling
    const motorStepsX = Math.round(deltaX * MOTOR_STEPS_PER_METER);
    const motorStepsY = Math.round(deltaY * MOTOR_STEPS_PER_METER);
  
    console.log(`Deltas (meters): X=${deltaX.toFixed(2)}, Y=${deltaY.toFixed(2)}`);
    console.log(`Motor Steps (pre-scaled): X=${motorStepsX}, Y=${motorStepsY}`);
  
    // Scale motor steps for actual movement
    const scaledMotorStepsX = deltaX * 655;
    const scaledMotorStepsY = deltaY * 655;
  
    console.log(`Motor Steps (scaled): X=${scaledMotorStepsX}, Y=${scaledMotorStepsY}`);
  
    // Ensure motor step values are properly scaled
    if (scaledMotorStepsX === 0 && scaledMotorStepsY === 0) {
      setErrorMessage("Calculated motor steps are too small to move.");
      console.error("Motor steps are zero after scaling. Skipping movement.");
      return;
    }
  
    // Send movement command to backend
    try {
      const response = await fetch(`${process.env.REACT_APP_API_URL}/api/calculate-path`, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({
          targetPosition: targetPosition,
          currentPositions: [{ x: tagPosition.x, y: tagPosition.y }], // Include Chair 1 position
          motorSteps: { x: scaledMotorStepsX * 655 , y: scaledMotorStepsY * 655 }, // Send properly scaled motor steps
        }),
      });
  
      if (response.ok) {
        const data = await response.json();
        console.log("Movement initiated:", data);
        setSuccessMessage(
          `Movement initiated successfully. Scaled Motor Steps: X=${scaledMotorStepsX}, Y=${scaledMotorStepsY}`
        );
      } else {
        const errorData = await response.json();
        console.error("Error initiating movement:", errorData);
        setErrorMessage(errorData.error || "Failed to initiate movement.");
      }
    } catch (error) {
      console.error("Error sending movement request:", error);
      setErrorMessage("Error communicating with the backend.");
    }
  };
  
  return (
    <div className="auto-move-container">
      <h1>Auto Move</h1>
      {successMessage && <p className="success">{successMessage}</p>}
      {errorMessage && <p className="error">{errorMessage}</p>}
      <div
        className="map-area"
        onClick={handleMapClick}
        style={{
          width: `${areaWidthPx}px`,
          height: `${areaHeightPx}px`,
          margin: "0 auto",
          position: "relative",
          border: "2px solid black",
          backgroundSize: `${areaWidthPx / 4}px ${areaHeightPx / 4}px`,
          backgroundImage:
            "linear-gradient(to right, gray 1px, transparent 1px), linear-gradient(to bottom, gray 1px, transparent 1px)",
        }}
      >
        <div
          className="anchor-dot"
          style={{ left: "0px", top: "0px", backgroundColor: "blue" }}
          title="Anchor 1 (Top-Left)"
        >
          A1
        </div>
        <div
          className="anchor-dot"
          style={{
            left: `${areaWidthPx - 20}px`,
            top: "0px",
            backgroundColor: "red",
          }}
          title="Anchor 2 (Top-Right)"
        >
          A2
        </div>
        {tagPosition && (
          <div
            className="tag-dot"
            style={{
              left: `${tagPosition.x * scaleFactor}px`,
              top: `${tagPosition.y * scaleFactor}px`,
              backgroundColor: "green",
            }}
            title={`Tag: X: ${tagPosition.x.toFixed(2)}m, Y: ${tagPosition.y.toFixed(2)}m`}
          ></div>
        )}
        {targetPosition && (
          <div
            className="target-dot"
            style={{
              left: `${targetPosition.x * scaleFactor}px`,
              top: `${targetPosition.y * scaleFactor}px`,
              backgroundColor: "orange",
            }}
            title={`Target: X: ${targetPosition.x.toFixed(
              2
            )}m, Y: ${targetPosition.y.toFixed(2)}m`}
          ></div>
        )}
      </div>
      <button onClick={calculateSteps}>Send Command</button>
    </div>
  );
};

export default AutoMove;
