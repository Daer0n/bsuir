import React from "react";
import { useNavigate } from "react-router-dom";
import "./MainPage.css";

const MainPage = () => {
    const navigate = useNavigate();

    return (
        <div>
            <div className="nav-bar">
                <div className="buttons-left">
                    <button onClick={() => {navigate('/generate/word')}}>Сгенерировать слово</button>
                    <button>Чтение с файла</button>
                </div>
                <div className="button-right">
                    <button onClick={() => {navigate('/help')}}>Помощь</button>
                </div>
            </div>
        </div>
    );
};

export default MainPage;
