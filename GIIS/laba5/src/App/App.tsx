import React, { useState, useRef } from "react";
import "./App.css";

function App() {
    const [points, setPoints] = useState<{ x: number; y: number }[]>([]);
    const svgRef = useRef<SVGSVGElement | null>(null);

    const handleAlgorithmChange = (
        event: React.ChangeEvent<HTMLSelectElement>
    ) => {
        const selectedValue = event.target.value;

        switch (selectedValue) {
            case "convexity":
                checkConvexity();
                break;
            case "graham":
                computeConvexHullGraham();
                break;
            case "jarvis":
                computeConvexHullJarvis();
                break;
            default:
                break;
        }
    };

    const clearSvg = () => {
        const svg = svgRef.current;
        if (svg) {
            svg.innerHTML = "";
        }
    };

    const addPoint = (event: React.MouseEvent<SVGSVGElement, MouseEvent>) => {
        const rect = (event.target as SVGSVGElement).getBoundingClientRect();
        const x = event.clientX - rect.left;
        const y = event.clientY - rect.top;
        const newPoints = [...points, { x, y }];
        setPoints(newPoints);
        drawPoint(x, y);
        drawPolygon();
    };

    const checkConvexity = () => {
        if (points.length < 3) {
            alert("Minimum number of points to test convexity: 3");
            return;
        }

        const orientation = getOrientation(points[0], points[1], points[2]);
        const isClockwise = orientation < 0;

        for (let i = 1; i < points.length; i++) {
            const p1 = points[i];
            const p2 = points[(i + 1) % points.length];
            const p3 = points[(i + 2) % points.length];

            const currentOrientation = getOrientation(p1, p2, p3);
            if (
                (currentOrientation < 0 && !isClockwise) ||
                (currentOrientation > 0 && isClockwise)
            ) {
                alert("The polygon is not convex");
                return;
            }
        }

        alert("The polygon is convex");
    };

    const getOrientation = (
        p1: { x: number; y: number },
        p2: { x: number; y: number },
        p3: { x: number; y: number }
    ) => {
        const val =
            (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y);
        if (val === 0) {
            return 0;
        } else if (val > 0) {
            return 1;
        } else {
            return -1;
        }
    };

    const drawPoint = (x: number, y: number) => {
        const svg = svgRef.current;
        if (svg) {
            const point = document.createElementNS(
                "http://www.w3.org/2000/svg",
                "circle"
            );
            point.setAttribute("cx", x.toString());
            point.setAttribute("cy", y.toString());
            point.setAttribute("r", "3");
            point.setAttribute("fill", "black");
            svg.appendChild(point);
        }
    };

    const drawLine = (
        x1: number,
        y1: number,
        x2: number,
        y2: number,
        color: string = "black"
    ) => {
        const svg = svgRef.current;
        if (svg) {
            const line = document.createElementNS(
                "http://www.w3.org/2000/svg",
                "line"
            );
            line.setAttribute("x1", x1.toString());
            line.setAttribute("y1", y1.toString());
            line.setAttribute("x2", x2.toString());
            line.setAttribute("y2", y2.toString());
            line.setAttribute("stroke", color);
            svg.appendChild(line);
        }
    };

    const drawPolygon = () => {
        const svg = svgRef.current;
        if (svg) {
            svg.innerHTML = "";
            for (let i = 0; i < points.length; i++) {
                const point = points[i];
                drawPoint(point.x, point.y);
                if (i > 0) {
                    const prevPoint = points[i - 1];
                    drawLine(
                        prevPoint.x,
                        prevPoint.y,
                        point.x,
                        point.y,
                        "black"
                    );
                }
            }
            if (points.length > 2) {
                const firstPoint = points[0];
                const lastPoint = points[points.length - 1];
                drawLine(
                    lastPoint.x,
                    lastPoint.y,
                    firstPoint.x,
                    firstPoint.y,
                    "black"
                );
            }
        }
    };

    function calculateNormals() {
        if (points.length < 3) {
            alert("Minimum number of points to test convexity: 3");
            return;
        }

        const svg = svgRef.current;
        drawPolygon();

        for (let i = 0; i < points.length; i++) {
            const currPoint = points[i];
            const prevPoint = points[i === 0 ? points.length - 1 : i - 1];
            const nextPoint = points[(i + 1) % points.length];

            const normalX: number = nextPoint.y - currPoint.y;
            const normalY: number = currPoint.x - nextPoint.x;

            const normalLength: number = Math.sqrt(
                normalX * normalX + normalY * normalY
            );
            const normalizedNormalX: number = normalX / normalLength;
            const normalizedNormalY: number = normalY / normalLength;

            const normalStartX: number = currPoint.x + normalizedNormalX * 100;
            const normalStartY: number = currPoint.y + normalizedNormalY * 100;

            const normalEndX: number = currPoint.x - normalizedNormalX * 100;
            const normalEndY: number = currPoint.y - normalizedNormalY * 100;

            drawLine(normalStartX, normalStartY, normalEndX, normalEndY, "red");
        }
    }

    const computeConvexHullGraham = () => {
        if (points.length < 3) {
            alert("Minimum number of points to test convexity: 3");
            return;
        }

        const sortedPoints = points.slice().sort((a, b) => {
            if (a.y !== b.y) {
                return a.y - b.y;
            }
            return a.x - b.x;
        });

        const getOrientation = (
            p: { x: number; y: number },
            q: { x: number; y: number },
            r: { x: number; y: number }
        ) => {
            const val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
            if (val === 0) {
                return 0;
            } else if (val > 0) {
                return 1;
            } else {
                return -1;
            }
        };

        const hullPoints = [sortedPoints[0], sortedPoints[1]];
        for (let i = 2; i < sortedPoints.length; i++) {
            while (
                hullPoints.length > 1 &&
                getOrientation(
                    hullPoints[hullPoints.length - 2],
                    hullPoints[hullPoints.length - 1],
                    sortedPoints[i]
                ) !== -1
            ) {
                hullPoints.pop();
            }
            hullPoints.push(sortedPoints[i]);
        }

        drawPolygon();

        for (let i = 0; i < hullPoints.length; i++) {
            const startPoint = hullPoints[i];
            const endPoint = hullPoints[(i + 1) % hullPoints.length];
            drawLine(
                startPoint.x,
                startPoint.y,
                endPoint.x,
                endPoint.y,
                "blue"
            );
        }
    };

    const computeConvexHullJarvis = () => {
        if (points.length < 3) {
            alert("Minimum number of points to test convexity: 3");
            return;
        }

        const getOrientation = (
            p: { x: number; y: number },
            q: { x: number; y: number },
            r: { x: number; y: number }
        ) => {
            const val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
            if (val === 0) {
                return 0;
            } else if (val > 0) {
                return 1;
            } else {
                return -1;
            }
        };

        const leftmostPoint = points.reduce((leftmost, point) =>
            point.x < leftmost.x ? point : leftmost
        );

        const hullPoints = [];
        let p = leftmostPoint;
        let q;

        do {
            hullPoints.push(p);
            q = points[0];
            for (let i = 1; i < points.length; i++) {
                if (q === p || getOrientation(p, q, points[i]) === -1) {
                    q = points[i];
                }
            }
            p = q;
        } while (p !== leftmostPoint);

        drawPolygon();

        for (let i = 0; i < hullPoints.length; i++) {
            const startPoint = hullPoints[i];
            const endPoint = hullPoints[(i + 1) % hullPoints.length];
            drawLine(
                startPoint.x,
                startPoint.y,
                endPoint.x,
                endPoint.y,
                "blue"
            );
        }
    };

    return (
        <div className="App">
            <div className="MainArea">
                <h1>Landfill</h1>
                <svg
                    id="svg"
                    className="Svg"
                    ref={svgRef}
                    onClick={addPoint}
                ></svg>
            </div>
            <div className="Menu">
                <div className="algorithm-container">
                    <p className="algorithm-label">Algorithm:</p>
                    <select id="curveType" onChange={handleAlgorithmChange}>
                        <option value="">Select an algorithm</option>
                        <option value="convexity">check convexity</option>
                        <option value="graham">convex Graham shell</option>
                        <option value="jarvis">convex Jarvis shell</option>
                    </select>
                </div>
                <button onClick={calculateNormals}>Normalize</button>
                <button onClick={clearSvg}>Clear</button>
            </div>
        </div>
    );
}

export default App;
