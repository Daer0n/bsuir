import React, { useState } from "react";
import "./App.css";

function App() {
    const [selectedAlgorithm, setSelectedAlgorithm] = useState<string>("");
    const handleAlgorithmChange = (
        event: React.ChangeEvent<HTMLSelectElement>
    ) => {
        const selectedValue = event.target.value;
        setSelectedAlgorithm(selectedValue);
    };
    return (
        <div className="wrapper">
            <div className="mainArea">
                <h1>Segment Algorithms</h1>
                <svg className="svg"></svg>
                <div className="menu">
                    <div className="Input">
                        <label>Algorithm: </label>
                        <select
                            value={selectedAlgorithm}
                            onChange={handleAlgorithmChange}
                        >
                            <option value="">Select an algorithm</option>
                            <option value="cube">Cube</option>
                            <option value="sphere">Sphere</option>
                            <option value="prisma">Prisma</option>
                        </select>
                    </div>
                    <div className="buttons">
                        <button className="drag">Drag</button>
                        <button className="reset">Reset</button>
                    </div>
                </div>
            </div>
        </div>
    );
}

export default App;
