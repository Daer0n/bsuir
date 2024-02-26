import React, { useRef, useState } from "react";
import "./App.css";

function App() {
    const canvasRef = useRef<SVGSVGElement | null>(null);
    const [centerX, setCenterX] = useState<number | null>(null);
    const [centerY, setCenterY] = useState<number | null>(null);
    const [isDrawing, setIsDrawing] = useState(false);

    const startDrawing = (event: React.MouseEvent<SVGSVGElement>) => {
        setIsDrawing(true);
        const canvas = canvasRef.current;
        if (canvas) {
            const rect = canvas.getBoundingClientRect();
            setCenterX(event.clientX - rect.left);
            setCenterY(event.clientY - rect.top);
        }
    };

    const draw = (event: React.MouseEvent<SVGSVGElement>) => {
        if (!isDrawing) return;
        const canvas = canvasRef.current;
        if (canvas) {
            const curveType = (
                document.getElementById("curveType") as HTMLSelectElement
            ).value;
            const rect = canvas.getBoundingClientRect();
            const a = Math.abs(event.clientX - rect.left - (centerX || 0));
            const b = Math.abs(event.clientY - rect.top - (centerY || 0));
            const step = 1 / Math.max(a, b);

            const svg = document.createElementNS("http://www.w3.org/2000/svg", "svg");
            svg.setAttribute("width", String(canvas.width.baseVal.value));
            svg.setAttribute("height", String(canvas.height.baseVal.value));

            let x: number = 0,
                y: number = 0;

            for (let angle = 0; angle < 2 * Math.PI; angle += step) {
                switch (curveType) {
                    case "circle":
                        x = (centerX || 0) + a * Math.cos(angle);
                        y = (centerY || 0) + a * Math.sin(angle);
                        break;
                    case "ellipse":
                        x = (centerX || 0) + a * Math.cos(angle);
                        y = (centerY || 0) + b * Math.sin(angle);
                        break;
                    case "hyperbola":
                        x = (centerX || 0) + a / Math.cos(angle);
                        y = (centerY || 0) + b * Math.tan(angle);
                        break;
                    case "parabola":
                        x = (centerX || 0) + a * angle;
                        y = (centerY || 0) + b * Math.pow(angle, 2);
                        break;
                    default:
                        break;
                }

                const rect = document.createElementNS("http://www.w3.org/2000/svg", "rect");
                rect.setAttribute("x", String(x));
                rect.setAttribute("y", String(y));
                rect.setAttribute("width", "1");
                rect.setAttribute("height", "1");
                rect.setAttribute("fill", "black");
                svg.appendChild(rect);
            }

            canvas.innerHTML = svg.outerHTML;
        }
    };

    const stopDrawing = () => {
        setIsDrawing(false);
    };

    const clearCanvas = () => {
        const canvas = canvasRef.current;
        if (canvas) {
            canvas.innerHTML = "";
        }
    };

    return (
        <div className="App">
            <div className="MainArea">
                <h1>Second-order line drawing Algorithms</h1>
                <svg
                    id="canvas"
                    ref={canvasRef}
                    onMouseDown={startDrawing}
                    onMouseMove={draw}
                    onMouseUp={stopDrawing}
                    className="Svg"
                ></svg>
            </div>
            <div className="Menu">
                <div className="algorithm-container">
                    <p className="algorithm-label">Algorithm:</p>
                    <select id="curveType">
                        <option value="">Select an algorithm</option>
                        <option value="circle">Circle</option>
                        <option value="ellipse">Ellipse</option>
                        <option value="hyperbola">Hyperbola</option>
                        <option value="parabola">Parabola</option>
                    </select>
                </div>
                <button onClick={clearCanvas}>Clear</button>
            </div>
        </div>
    );
}

export default App;
