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
        clearSvg();
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
        if (segmentEnds.length >= 2) drawCurve();
    };

    const drawCurve = () => {
        const svg = svgRef.current;

        if (svg && selectedAlgorithm === "hermite") {
            console.log("hermite");
            for (let i = 0; i < segmentEnds.length - 1; i++) {
                const p0 = segmentEnds[i];
                const p1 = segmentEnds[i + 1];
                const t0 = i > 0 ? (p1.x - segmentEnds[i - 1].x) / 2 : 0;
                const t1 =
                    i < segmentEnds.length - 2
                        ? (segmentEnds[i + 2].x - p0.x) / 2
                        : 0;

                let d = "";
                for (let t = 0; t <= 1; t += 0.01) {
                    const h1 = 2 * Math.pow(t, 3) - 3 * Math.pow(t, 2) + 1;
                    const h2 = -2 * Math.pow(t, 3) + 3 * Math.pow(t, 2);
                    const h3 = Math.pow(t, 3) - 2 * Math.pow(t, 2) + t;
                    const h4 = Math.pow(t, 3) - Math.pow(t, 2);

                    const x = h1 * p0.x + h2 * p1.x + h3 * t0 + h4 * t1;
                    const y = h1 * p0.y + h2 * p1.y + h3 * t0 + h4 * t1;

                    if (t === 0) {
                        d += `M ${x} ${y}`;
                    } else {
                        d += ` L ${x} ${y}`;
                    }
                }

                const path = document.createElementNS(
                    "http://www.w3.org/2000/svg",
                    "path"
                );
                path.setAttribute("d", d);
                path.setAttribute("stroke", "blue");
                path.setAttribute("fill", "none");
                svg.appendChild(path);
            }
        } else if (svg && selectedAlgorithm === "bezier") {
            console.log("bezier");
            if (segmentEnds.length >= 4 && (segmentEnds.length - 1) % 3 === 0) {
                for (let i = 0; i < segmentEnds.length - 1; i += 3) {
                    const p0 = segmentEnds[i];
                    const p1 = segmentEnds[i + 1];
                    const p2 = segmentEnds[i + 2];
                    const p3 = segmentEnds[i + 3];

                    const iterations = 10000;
                    let d = "";
                    for (let j = 0; j <= iterations; j++) {
                        const t = j / iterations;

                        const x =
                            Math.pow(1 - t, 3) * p0.x +
                            3 * Math.pow(1 - t, 2) * t * p1.x +
                            3 * (1 - t) * Math.pow(t, 2) * p2.x +
                            Math.pow(t, 3) * p3.x;
                        const y =
                            Math.pow(1 - t, 3) * p0.y +
                            3 * Math.pow(1 - t, 2) * t * p1.y +
                            3 * (1 - t) * Math.pow(t, 2) * p2.y +
                            Math.pow(t, 3) * p3.y;

                        if (t === 0) {
                            d += `M ${x} ${y}`;
                        } else {
                            d += ` L ${x} ${y}`;
                        }
                    }

                    const path = document.createElementNS(
                        "http://www.w3.org/2000/svg",
                        "path"
                    );
                    path.setAttribute("d", d);
                    path.setAttribute("stroke", "blue");
                    path.setAttribute("fill", "none");
                    svg.appendChild(path);
                }
            }
        } else if (svg && selectedAlgorithm === "spline") {
            console.log("spline");
            const splinePoints = [];

            for (let i = 0; i < segmentEnds.length - 1; i++) {
                const p0 = segmentEnds[i];
                const p1 = segmentEnds[i + 1];

                const t0 = i > 0 ? (p1.x - segmentEnds[i - 1].x) / 2 : 0;
                const t1 =
                    i < segmentEnds.length - 2
                        ? (segmentEnds[i + 2].x - p0.x) / 2
                        : 0;

                for (let t = 0; t <= 1; t += 0.01) {
                    const h1 = 2 * Math.pow(t, 3) - 3 * Math.pow(t, 2) + 1;
                    const h2 = -2 * Math.pow(t, 3) + 3 * Math.pow(t, 2);
                    const h3 = Math.pow(t, 3) - 2 * Math.pow(t, 2) + t;
                    const h4 = Math.pow(t, 3) - Math.pow(t, 2);

                    const x = h1 * p0.x + h2 * p1.x + h3 * t0 + h4 * t1;
                    const y = h1 * p0.y + h2 * p1.y + h3 * t0 + h4 * t1;

                    splinePoints.push({ x, y });
                }
            }

            let d = "";
            splinePoints.forEach((point, index) => {
                const command = index === 0 ? "M" : "L";
                d += `${command} ${point.x} ${point.y}`;
            });

            const path = document.createElementNS(
                "http://www.w3.org/2000/svg",
                "path"
            );
            path.setAttribute("d", d);
            path.setAttribute("stroke", "blue");
            path.setAttribute("fill", "none");
            svg.appendChild(path);
        }
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
