import React, { useState } from "react";
import { useNavigate } from "react-router-dom";
import api from "../api/api";
import "./GetContext.css";

const GetContext = () => {
    const navigate = useNavigate();
    const [formData, setFormData] = useState({
        word: "",
        length: "",
        count: "",
    });
    const [responseText, setResponseText] = useState("");

    const handleChange = (e) => {
        setFormData({
            ...formData,
            [e.target.name]: e.target.value,
        });
    };

    const handleGetContext = async (e) => {
        e.preventDefault();
        const response = await api.post(`/word/search/context`, formData);
        console.log(response.data);
        setResponseText(response.data);
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
            <form onSubmit={handleGetContext}>
                <label>
                    Слово:
                    <input
                        type="text"
                        name="word"
                        value={formData.word}
                        onChange={handleChange}
                    />
                </label>
                <label>
                    Длина:
                    <input
                        type="text"
                        name="length"
                        value={formData.length}
                        onChange={handleChange}
                    />
                </label>
                <label>
                    Количество:
                    <input
                        type="text"
                        name="count"
                        value={formData.count}
                        onChange={handleChange}
                    />
                </label>
                <button type="submit">Отправить</button>
            </form>
            {responseText && (
                <label className="response-label">{responseText}</label>
            )}
        </div>
    );
};

export default GetContext;
