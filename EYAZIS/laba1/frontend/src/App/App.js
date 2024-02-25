import "./App.css";
import React from "react";
import { BrowserRouter, Route, Routes } from "react-router-dom";

import HelpPage from "../Help/Help";
import MainPage from "../MainPage/MainPage";
import WordGenerate from "../WordGenerate/WordGenerate";

function App() {
    return (
        <div className="app">
            <div className="app-field">
                <BrowserRouter>
                    <Routes>
                        <Route path="/" element={<MainPage />} />
                        <Route path="/help" element={<HelpPage />} />
                        <Route path="/generate/word" element={<WordGenerate />} />
                    </Routes>
                </BrowserRouter>
            </div>
        </div>
    );
}

export default App;
