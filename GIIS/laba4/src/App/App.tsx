import React, { useEffect, useRef, useState } from "react";
import { Shape } from "../shape";
import "./App.css";
import cubeData from "../inputData/cube.json";
import pyramidData from "../inputData/pyramid.json";

const App: React.FC = () => {
    const canvasRef = useRef<HTMLCanvasElement>(null);
    const [shape, setShape] = useState<Shape | null>(null);
    const [file, setFile] = useState<File | undefined>();

    useEffect(() => {
        const loadShapeFromFile = async () => {
            if (file) {
                try {
                    const fileContents = await file.text();
                    const data = JSON.parse(fileContents);
                    const shape = new Shape(data.points);
                    const centerX = canvasRef.current
                        ? canvasRef.current.width / 2
                        : 0;
                    const centerY = canvasRef.current
                        ? canvasRef.current.height / 2
                        : 0;
                    setShape(shape.move(centerX, "x").move(centerY, "y"));
                } catch (error) {
                    console.error("Error loading shape from file:", error);
                }
            }
        };
        loadShapeFromFile();
    }, [file]);

    useEffect(() => {
        if (!canvasRef.current || !shape) return;

        const ctx = canvasRef.current.getContext("2d");
        if (!ctx) return;

        clearCanvas();

        ctx.beginPath();
        ctx.moveTo(0, canvasRef.current.height / 2);
        ctx.lineTo(canvasRef.current.width, canvasRef.current.height / 2);
        ctx.strokeStyle = "red";
        ctx.stroke();

        ctx.beginPath();
        ctx.moveTo(canvasRef.current.width / 2, 0);
        ctx.lineTo(canvasRef.current.width / 2, canvasRef.current.height);
        ctx.strokeStyle = "green";
        ctx.stroke();

        ctx.beginPath();
        ctx.moveTo(0, 0);
        ctx.lineTo(canvasRef.current.width, canvasRef.current.height);
        ctx.strokeStyle = "blue";
        ctx.stroke();

        ctx.beginPath();
        shape.points.forEach((point, index) => {
            if (index === 0) {
                ctx.moveTo(point.x, point.y);
            } else {
                ctx.lineTo(point.x, point.y);
            }
        });
        ctx.closePath();
        ctx.strokeStyle = "white";
        ctx.stroke();
    }, [shape]);

    useEffect(() => {
        const handleKeyDown = (event: KeyboardEvent) => {
            if (!shape) return;
            switch (event.key) {
                case "w":
                    setShape(shape.move(-5, "y"));
                    break;
                case "s":
                    setShape(shape.move(5, "y"));
                    break;
                case "a":
                    setShape(shape.move(-5, "x"));
                    break;
                case "d":
                    setShape(shape.move(5, "x"));
                    break;
                case "e":
                    setShape(shape.move(5, "z"));
                    break;
                case "q":
                    setShape(shape.move(-5, "z"));
                    break;
                case "z":
                    setShape(shape.rotateX());
                    break;
                case "x":
                    setShape(shape.rotateY());
                    break;
                case "c":
                    setShape(shape.rotateZ());
                    break;
                case "+":
                    setShape(shape.scale(1.1));
                    break;
                case "-":
                    setShape(shape.scale(0.9));
                    break;
                default:
                    break;
            }
        };

        document.addEventListener("keydown", handleKeyDown);

        return () => {
            document.removeEventListener("keydown", handleKeyDown);
        };
    }, [shape]);

    const openCubeFile = () => {
        setFile(new File([JSON.stringify(cubeData)], "cube.json"));
    };

    const openPyramidFile = () => {
        setFile(new File([JSON.stringify(pyramidData)], "pyramid.json"));
    };

    const clearCanvas = () => {
        if (!canvasRef.current || !shape) return;

        const ctx = canvasRef.current.getContext("2d");
        if (!ctx) return;

        ctx.clearRect(0, 0, canvasRef.current.width, canvasRef.current.height);
    };

    return (
        <div className="Wrapper">
            <h1>3d Redactor</h1>
            <canvas
                className="Canvas"
                ref={canvasRef}
                width={700}
                height={500}
            />
            <div className="Menu">
                <div className="Buttons">
                    <button className="Cube" onClick={openCubeFile}>
                        Cube
                    </button>
                    <button onClick={openPyramidFile}>Pyramid</button>
                </div>
                <button className="Reset" onClick={clearCanvas}>
                    Clear
                </button>
            </div>
        </div>
    );
};

export default App;
