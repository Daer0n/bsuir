import React, { useState, useEffect } from "react";

const SpeechSynthesis = ({ navigate }) => {
    const [text, setText] = useState("");
    const [availableVoices, setAvailableVoices] = useState([]);
    const [selectedVoice, setSelectedVoice] = useState(null);
    const [speakingRate, setSpeakingRate] = useState(1.0);
    const [pitch, setPitch] = useState(1.0);
    const [volume, setVolume] = useState(1.0);
  
    useEffect(() => {
      const voices = window.speechSynthesis.getVoices();
      const englishVoices = voices.filter((voice) => voice.lang.startsWith("en"));
      setAvailableVoices(englishVoices);
  
      if (englishVoices.length > 0) {
        setSelectedVoice(englishVoices[0].name);
      }
    }, []);
  
    const playText = () => {
      if (text.trim()) {
        const utterance = new SpeechSynthesisUtterance(text);
        utterance.voice = availableVoices.find((v) => v.name === selectedVoice);
        utterance.rate = speakingRate;
        utterance.pitch = pitch;
        utterance.volume = volume;
        window.speechSynthesis.speak(utterance);
      } else {
        alert("Введите текст для воспроизведения.");
      }
    };
  
    const pasteFromClipboard = async () => {
      try {
        const textFromClipboard = await navigator.clipboard.readText();
        setText(textFromClipboard);
      } catch (err) {
        console.error("Ошибка при чтении из буфера обмена", err);
      }
    };
  
    const getSelectedText = () => {
      const selectedText = window.getSelection().toString();
      if (selectedText) {
        setText(selectedText);
      } else {
        alert("Пожалуйста, выделите текст.");
      }
    };
  
    return (
      <div className="container">
        <h1 className="header">Синтез речи</h1>
  
        <textarea
          value={text}
          onChange={(e) => setText(e.target.value)}
          rows="5"
          placeholder="Введите текст для синтеза..."
          className="textarea"
        ></textarea>
  
        <div className="controls">
          <div className="formGroup">
            <label className="label">Выберите голос:</label>
            <select
              onChange={(e) => setSelectedVoice(e.target.value)}
              className="select"
              value={selectedVoice}
            >
              {availableVoices.map((voice, index) => (
                <option key={index} value={voice.name}>
                  {voice.name} ({voice.lang})
                </option>
              ))}
            </select>
          </div>
  
          <div className="formGroup">
            <label className="label">Темп:</label>
            <input
              type="range"
              min="0.5"
              max="2.0"
              step="0.1"
              value={speakingRate}
              onChange={(e) => setSpeakingRate(parseFloat(e.target.value))}
              className="rangeInput"
            />
          </div>
  
          <div className="formGroup">
            <label className="label">Тон:</label>
            <input
              type="range"
              min="0.0"
              max="2.0"
              step="0.1"
              value={pitch}
              onChange={(e) => setPitch(parseFloat(e.target.value))}
              className="rangeInput"
            />
          </div>
  
          <div className="formGroup">
            <label className="label">Громкость:</label>
            <input
              type="range"
              min="0.0"
              max="1.0"
              step="0.1"
              value={volume}
              onChange={(e) => setVolume(parseFloat(e.target.value))}
              className="rangeInput"
            />
          </div>
        </div>
  
        <div className="buttonsContainer">
          <button
            onClick={pasteFromClipboard}
            className="button"
          >
            Вставить из буфера обмена
          </button>
  
          <button
            onClick={getSelectedText}
            className="button"
          >
            Вставить выделенный текст
          </button>
        </div>
  
        <button
          onClick={playText}
          className="playButton"
        >
          Воспроизвести
        </button>
  
        <div className="navigation">
          <button onClick={() => navigate("pageOne")} className="navButton">
            Синтез речи
          </button>
          <button onClick={() => navigate("pageTwo")} className="navButton">
            Рапознавание речи
          </button>
        </div>
      </div>
    );
  };

export default SpeechSynthesis;