import React from "react";
import { useNavigate } from "react-router-dom";
import "./Help.css";

const HelpPage = () => {
    const navigate = useNavigate();

    return (
        <div className="help-page">
            <button
                className="close-button"
                onClick={() => {
                    navigate("/");
                }}
            >
                &times;
            </button>
            <p className="section-title">
                Программа работает следующим образом:
            </p>
            <ol>
                <li>
                    <p className="step-title">Шаг 1: Открытие файла</p>
                    <ul>
                        <li>Нажмите кнопку "Открыть файл".</li>
                        <li>Выберите файл с расширением .doc или .docx.</li>
                        <li>
                            Содержимое файла будет отображено в окне программы.
                        </li>
                    </ul>
                </li>
                <li>
                    <p className="step-title">Шаг 2: Генерация слова</p>
                    <ul>
                        <li>Введите основу слова в поле "Основа слова".</li>
                        <li>Введите род слова в поле "Род".</li>
                        <li>Введите падеж слова в поле "Падеж".</li>
                        <li>Введите число слова в поле "Число".</li>
                        <li>Нажмите кнопку "Сгенерировать слово".</li>
                        <li>
                            Сгенерированная форма слова будет отображена в окне
                            программы.
                        </li>
                    </ul>
                </li>
            </ol>
        </div>
    );
};

export default HelpPage;
