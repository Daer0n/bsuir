import React from "react";
import { useNavigate } from "react-router-dom";
import "./MainPage.css";

const MainPage = () => {
    const navigate = useNavigate();

    return (
        <div>
            <div className="nav-bar">
                <div className="buttons-left">
                    <button
                        onClick={() => {
                            navigate("/generate/word");
                        }}
                    >
                        Сгенерировать слово
                    </button>
                    <button
                        onClick={() => {
                            navigate("/file");
                        }}
                    >
                        Чтение с файла
                    </button>
                    <button
                        onClick={() => {
                            navigate("/view/data");
                        }}
                    >
                        Просмотр данных
                    </button>
                    <button
                        onClick={() => {
                            navigate("/parse/text");
                        }}
                    >
                        Разобрать текст
                    </button>
                </div>
                <div className="button-right">
                    <button
                        onClick={() => {
                            navigate("/help");
                        }}
                    >
                        Помощь
                    </button>
                </div>
                
            </div>
        </div>
    );
};

export default MainPage;
