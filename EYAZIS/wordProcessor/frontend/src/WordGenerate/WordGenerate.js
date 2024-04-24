import React, { useState } from "react";
import { useNavigate } from "react-router-dom";
import api from "../api/api";
import "./WordGenerate.css";

const WordGenerate = () => {
  const navigate = useNavigate();

  const [formData, setFormData] = useState({
    base: "",
    gender: "",
    case: "",
    number: ""
  });

  const [generatedWord, setGeneratedWord] = useState("");
  const [isGenerated, setIsGenerated] = useState(false);

  const handleInputChange = (e) => {
    const { name, value } = e.target;
    setFormData((prevFormData) => ({
      ...prevFormData,
      [name]: value
    }));
  };

  const handleGenerate = async () => {
    try {
      const response = await api.post("word/generate", formData);
      setGeneratedWord(response.data);
      setIsGenerated(true);
    } catch (error) {
      console.error(error);
    }
  };

  return (
    <div className="word-generate-page">
      <button
        className="close-button"
        onClick={() => {
          navigate("/");
        }}
      >
        &times;
      </button>
      <div className="form">
        <div>
          Основа
          <input
            name="base"
            value={formData.base}
            onChange={handleInputChange}
          />
        </div>
        <div>
          Род
          <select
            name="gender"
            value={formData.gender}
            onChange={handleInputChange}
          >
            <option value="">Выберите род</option>
            <option value="мужской">Мужской</option>
            <option value="женский">Женский</option>
            <option value="средний">Средний</option>
          </select>
        </div>
        <div>
          Падеж
          <select
            name="case"
            value={formData.case}
            onChange={handleInputChange}
          >
            <option value="">Выберите падеж</option>
            <option value="именительный">Именительный</option>
            <option value="родительный">Родительный</option>
            <option value="дательный">Дательный</option>
            <option value="винительный">Винительный</option>
            <option value="творительный">Творительный</option>
            <option value="предложный">Предложный</option>
          </select>
        </div>
        <div>
          Число
          <select
            name="number"
            value={formData.number}
            onChange={handleInputChange}
          >
            <option value="">Выберите число</option>
            <option value="единственное">Единственное</option>
            <option value="множественное">Множественное</option>
          </select>
        </div>
      </div>

      {isGenerated && (
        <div className="generated-word">
          Сгенерированное слово: {generatedWord}
        </div>
      )}

      <button className="generate-button" onClick={handleGenerate}>
        Сгенерировать
      </button>
    </div>
  );
};

export default WordGenerate;