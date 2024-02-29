import React, { useRef, useState } from "react";
import "./App.css";

function App() {
    const svgRef = useRef<SVGSVGElement | null>(null);

    

    const clearSvg = () => {
        const svg = svgRef.current;
        if (svg) {
            svg.innerHTML = "";
        }
    };

    const createSegment = (event: React.MouseEvent<SVGSVGElement, MouseEvent>): void => {
      const svg = event.currentTarget;
      const pt = svg.createSVGPoint();
      pt.x = event.clientX;
      pt.y = event.clientY;
      const screenCTM = svg.getScreenCTM();
  
      if (screenCTM && screenCTM.inverse) {
        const inverseCTM = screenCTM.inverse();
  
        if (inverseCTM) {
          const cursorPt = pt.matrixTransform(inverseCTM);
  
          const point: Point = {
            x: Math.floor(cursorPt.x / cellSize),
            y: Math.floor(cursorPt.y / cellSize),
            opacity: 1,
            color: { r: 102, g: 0, b: 51 },
          };
  
          if (segmentEnds.length === 2) {
            handleReset();
            setSegmentEnds([point]);
          } else {
            setSegmentEnds((prevSegmentEnds) => [...prevSegmentEnds, point]);
          }
        }
      }
    };

    return (
        <div className="App">
            <div className="MainArea">
                <h1>Interpolation and approximation of curves</h1>
                <svg id="svg" ref={svgRef} className="Svg"></svg>
            </div>
            <div className="Menu">
                <div className="algorithm-container">
                    <p className="algorithm-label">Algorithm:</p>
                    <select id="curveType">
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
