import React, { useState } from "react";
import { useNavigate } from "react-router-dom";
import api from "../api/api";
import "./ParseText.css";

const ParseText = () => {
    const navigate = useNavigate();
    const [sentence, setSentence] = useState("");
    const [wordData, setWordData] = useState([]);

    const handleInputChange = (e) => {
        const { value } = e.target;
        setSentence(value);
    };

    const handleParseText = async () => {
        try {
            const response = await api.get(`word/corpus/search/${sentence}`);
            const data = response.data;
            const words = Object.keys(data).map((word) => ({
                word: word,
                additional_information: data[word].additional_information,
                frequency: data[word].frequency
            }));
            setWordData(words);
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
            <input
                className="input-field"
                name="words"
                value={sentence}
                onChange={handleInputChange}
                placeholder="Введите предложение"
            />
            <button className="generate-button" onClick={handleParseText}>
                Разобрать
            </button>
            {wordData.length > 0 && (
                <table className="word-table">
                    <thead>
                        <tr>
                            <th>Слово</th>
                            <th>Частота</th>
                            <th>Часть речи</th>
                        </tr>
                    </thead>
                    <tbody>
                        {wordData.map((word, index) => (
                            <tr key={index}>
                                <td>{word.word}</td>
                                <td>{word.frequency}</td>
                                <td>{word.additional_information}</td>
                            </tr>
                        ))}
                    </tbody>
                </table>
            )}
        </div>
    );
};

export default ParseText;