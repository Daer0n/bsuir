import React, { useState } from "react";
import SpeechSynthesis from "./components/speechSynthesis";
import SpeechRecognition from "./components/speechRecognition";
import './App.css';

const App = () => {
  const [currentPage, setCurrentPage] = useState("pageOne");

  const navigate = (page) => setCurrentPage(page);

  return (
    <div>
      {currentPage === "pageOne" && <SpeechSynthesis navigate={navigate} />}
      {currentPage === "pageTwo" && <SpeechRecognition navigate={navigate} />}
    </div>
  );
};

export default App;