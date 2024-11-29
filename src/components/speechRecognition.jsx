import React, { useState, useEffect } from "react";

const SpeechRecognition = ({ navigate }) => {
    const [operations, setOperations] = useState([
      "Включить свет",
      "Выключить свет",
      "Запустить музыку",
    ]);
    const [newOperation, setNewOperation] = useState("");
    const [notification, setNotification] = useState("");
    const [language, setLanguage] = useState("en-US");
  
    useEffect(() => {
        let recognition;
      
        const handleSpeechRecognition = () => {
          const SpeechRecognition =
            window.SpeechRecognition || window.webkitSpeechRecognition;
      
          if (!SpeechRecognition) {
            console.error("SpeechRecognition не поддерживается в этом браузере.");
            setNotification("Распознавание речи недоступно.");
            return;
          }
      
          recognition = new SpeechRecognition();
          recognition.lang = language;
          recognition.interimResults = false;
      
          recognition.onresult = (event) => {
            const spokenText = event.results[0][0].transcript.toLowerCase();
            const matchedOperation = operations.find((op) => op.toLowerCase() === spokenText);
            if (matchedOperation) {
              setNotification(`Операция "${matchedOperation}" выполнена!`);
            } else {
              setNotification(`Операция не распознана: "${spokenText}"`);
            }
          };
      
          recognition.onerror = (event) => {
            console.error("Ошибка распознавания речи:", event.error);
            setNotification("Ошибка распознавания речи.");
          };
      
          recognition.onend = () => {
            recognition.start();
          };
      
          recognition.start();
        };
      
        handleSpeechRecognition();
      
        return () => {
          if (recognition) {
            recognition.onend = null;
            recognition.stop();
          }
        };
      }, [operations, language]);
      
  
    const addOperation = () => {
      if (newOperation.trim()) {
        setOperations([...operations, newOperation]);
        setNewOperation("");
      }
    };
  
    const removeOperation = (index) => {
      setOperations(operations.filter((_, i) => i !== index));
    };
  
    return (
      <div className="container">
        <h1 className="header">Рапознавание речи</h1>
  
        <h2>Список операций:</h2>
        <ul className="operationsList">
          {operations.map((operation, index) => (
            <li key={index} className="operationItem">
              {operation}
              <button
                className="deleteButton"
                onClick={() => removeOperation(index)}
              >
                Удалить
              </button>
            </li>
          ))}
        </ul>
  
        <div className="addOperation">
          <input
            type="text"
            value={newOperation}
            onChange={(e) => setNewOperation(e.target.value)}
            placeholder="Новая операция..."
            className="textInput"
          />
          <button onClick={addOperation} className="addButton">
            Добавить
          </button>
        </div>
  
        <h2>Распознавание речи:</h2>
        <p className="notification">{notification || "Ожидание команды..."}</p>
  
        <h2>Настройки языка:</h2>
        <select
          value={language}
          onChange={(e) => setLanguage(e.target.value)}
          className="select"
        >
          <option value="en-US">Английский (США)</option>
          <option value="ru-RU">Русский</option>
        </select>
  
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

export default SpeechRecognition;