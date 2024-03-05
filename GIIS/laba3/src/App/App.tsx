import React, { useRef, useState } from "react";
import "./App.css";
import Point from "../drawingData";

function App() {
  const [segmentEnds, setSegmentEnds] = useState<Point[]>([]);
  const svgRef = useRef<SVGSVGElement | null>(null);
  const [selectedAlgorithm, setSelectedAlgorithm] = useState<string>("");
  const [color, setColor] = useState<string>("rgba(204, 0, 102, 1)");
  const [cellSize, setCellSize] = useState<number>(1);

  const handleAlgorithmChange = (
    event: React.ChangeEvent<HTMLSelectElement>
  ) => {
    const selectedValue = event.target.value;
    setSelectedAlgorithm(selectedValue);
  };

  const clearSvg = () => {
    const svg = svgRef.current;
    if (svg) {
      svg.innerHTML = "";
    }
  };

  const createSegment = (
    event: React.MouseEvent<SVGSVGElement, MouseEvent>
  ): void => {
    const svg = event.currentTarget;
    const pt = svg.createSVGPoint();
    pt.x = event.clientX - svg.getBoundingClientRect().left;
    pt.y = event.clientY - svg.getBoundingClientRect().top;

    const point: Point = {
      x: Math.floor(pt.x / cellSize),
      y: Math.floor(pt.y / cellSize),
      c: { r: 102, g: 0, b: 51 },
    };

    setSegmentEnds((prevSegmentEnds) => [...prevSegmentEnds, point]);
  };

  return (
    <div className="App">
      <div className="MainArea">
        <h1>Interpolation and approximation of curves</h1>
        <svg
          id="svg"
          ref={svgRef}
          className="Svg"
          onClick={createSegment}
        >
          {segmentEnds.map((point, index) => (
            <circle
              key={index}
              cx={point.x * cellSize}
              cy={point.y * cellSize}
              r={3}
              fill={color}
            />
          ))}
        </svg>
      </div>
      <div className="Menu">
        <div className="algorithm-container">
          <p className="algorithm-label">Algorithm:</p>
          <select
            id="curveType"
            value={selectedAlgorithm}
            onChange={handleAlgorithmChange}
          >
            <option value="">Select an algorithm</option>
            <option value="hermite">Hermite form</option>
            <option value="bezier">Bezier form</option>
            <option value="spline">B-spline</option>
          </select>
        </div>
        <button onClick={clearSvg}>Clear</button>
      </div>
    </div>
  );
}

export default App;