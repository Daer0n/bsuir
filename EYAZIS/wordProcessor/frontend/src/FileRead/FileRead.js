import React, { useState } from "react";
import { useNavigate } from "react-router-dom";
import api from "../api/api";
import "./FileRead.css";

const FileRead = () => {
    const navigate = useNavigate();
    const [selectedFile, setSelectedFile] = useState(null);
    const [fileContent, setFileContent] = useState("");

    const handleFileChange = (event) => {
        setSelectedFile(event.target.files[0]);
    };

    const handleTextareaChange = (event) => {
        setFileContent(event.target.value);
    };

    const handleFileRead = async () => {
        try {
            const formData = new FormData();
            formData.append("file", selectedFile);
            const response = await api.post("/word/parsing/sentence", formData);
            const formattedString = JSON.stringify(response.data, null, 2);
            setFileContent(formattedString);
        } catch (e) {
            console.log(e);
        }
    };

    const handleFileSave = async () => {
        try {
            setFileContent('')
            const formData = new FormData();
            formData.append("file", selectedFile);
            const response = await api.post("word/save", formData);
            console.log(response);
        } catch (e) {
            console.log(e);
        }
    };

    return (
        <div className="file-read-page">
            <button
                className="close-button"
                onClick={() => {
                    navigate("/");
                }}
            >
                &times;
            </button>
            <div className="file-form">
                <input
                    type="file"
                    accept=".doc, .docx"
                    onChange={handleFileChange}
                />
                <button className="read-data" onClick={handleFileRead}>
                    Прочитать данные
                </button>
                <div className="area-field">
                    <textarea
                        className="data"
                        value={fileContent}
                        onChange={handleTextareaChange}
                    ></textarea>
                </div>
                <button className="save-data" onClick={handleFileSave}>
                    Сохранить
                </button>
            </div>
        </div>
    );
};

export default FileRead;
