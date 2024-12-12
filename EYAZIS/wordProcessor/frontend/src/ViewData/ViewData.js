import React, { useState, useEffect } from "react";
import { useNavigate } from "react-router-dom";
import api from "../api/api";
import "./ViewData.css";

const ViewData = () => {
    const navigate = useNavigate();
    const [fileContent, setFileContent] = useState("");
    const [showSearchInput, setShowSearchInput] = useState(false);
    const [showFilterInput, setShowFilterInput] = useState(false);
    const [searchValue, setSearchValue] = useState("");
    const [searchWord, setSearchWord] = useState("");
    const [selectedFilter, setSelectedFilter] = useState("");
    const [filterResults, setFilterResults] = useState("");

    const handleTextareaChange = (event) => {
        setFileContent(event.target.value);
    };

    const handleSearchClick = () => {
        setShowSearchInput(!showSearchInput);
        setShowFilterInput(false);
    };

    const handleFilterClick = () => {
        setShowFilterInput(!showFilterInput);
        setShowSearchInput(false);
    };

    const handleSearchWordFromBase = async () => {
        console.log(searchValue);
        const response = await api.get(`/word/base/search/${searchValue}`);
        const searchResults = response.data;

        if (searchResults.length > 0) {
            const searchWords = JSON.stringify(searchResults);
            setSearchWord(searchWords);
        } else {
            setSearchWord("");
        }

        console.log(response.data);
    };

    const handleFilterByPartOfSpeech = async () => {
        const response = await api.get(
            `/word/part_of_speech/filter/${searchValue}`
        );
        const filterResults = JSON.stringify(response.data);
        setFilterResults(filterResults);
    };

    const handleFilterByGender = async () => {
        const response = await api.get(
            `/word/gender/filter/gender/${searchValue}`
        );
        const filterResults = JSON.stringify(response.data);
        setFilterResults(filterResults);
    };

    const handleFilterByCase = async () => {
        const response = await api.get(`/word/case/filter/case/${searchValue}`);
        const filterResults = JSON.stringify(response.data);
        setFilterResults(filterResults);
    };

    const handleSearchInputChange = (event) => {
        setSearchValue(event.target.value);
    };

    const handleFilterInputChange = (event) => {
        setSelectedFilter(event.target.value);
        setSearchValue("");
    };

    useEffect(() => {
        const fetchData = async () => {
            try {
                const response = await api.get("/word/view/data");
                setFileContent(response.data);
            } catch (error) {
                console.error(error);
            }
        };

        fetchData();
    }, []);

    return (
        <div className="view-data-page">
            <button
                className="close-button"
                onClick={() => {
                    navigate("/");
                }}
            >
                &times;
            </button>
            <div className="view-form">
                <textarea value={fileContent} onChange={handleTextareaChange} />
            </div>
            <div className="button-container">
                <button className="filter-button" onClick={handleFilterClick}>
                    Фильтрация по данным
                </button>
                <button className="search-button" onClick={handleSearchClick}>
                    Поиск по данным
                </button>
            </div>
            {showSearchInput && (
                <div className="search-input-container">
                    <input
                        type="text"
                        placeholder="Введите основу слова"
                        value={searchValue}
                        onChange={handleSearchInputChange}
                    />
                    <button onClick={handleSearchWordFromBase}>Поиск</button>
                    <p>Найденное слово:</p>
                    <textarea value={searchWord}></textarea>
                </div>
            )}
            {showFilterInput && (
                <div className="search-input-container">
                    <select
                        name="filter"
                        value={selectedFilter}
                        onChange={handleFilterInputChange}
                    >
                        <option value="">Выберите фильтрацию</option>
                        <option value="части речи">По части речи</option>
                        <option value="рода">По роду</option>
                        <option value="падежа">По падежу</option>
                    </select>
                    {selectedFilter === "части речи" && (
                        <select
                            name="partOfSpeech"
                            value={searchValue}
                            onChange={handleSearchInputChange}
                        >
                            <option value="">Выберите часть речи</option>
                            <option value="существительное">
                                Существительное
                            </option>
                            <option value="прилагательное">
                                Прилагательное
                            </option>
                            <option value="глагол">Глагол</option>
                            <option value="причастие">Причастие</option>
                            <option value="деепричастие">Деепричастие</option>
                            <option value="числительное">Числительное</option>
                            <option value="наречие">Наречие</option>
                            <option value="предлог">Предлог</option>
                            <option value="союз">Союз</option>
                            <option value="частица">Частица</option>
                            <option value="междометие">Междометие</option>
                        </select>
                    )}
                    {selectedFilter === "рода" && (
                        <select
                            name="gender"
                            value={searchValue}
                            onChange={handleSearchInputChange}
                        >
                            <option value="">Выберите род</option>
                            <option value="мужской">Мужской</option>
                            <option value="женский">Женский</option>
                            <option value="средний">Средний</option>
                        </select>
                    )}
                    {selectedFilter === "падежа" && (
                        <select
                            name="case"
                            value={searchValue}
                            onChange={handleSearchInputChange}
                        >
                            <option value="">Выберите падеж</option>
                            <option value="именительный">Именительный</option>
                            <option value="родительный">Родительный</option>
                            <option value="дательный">Дательный</option>
                            <option value="винительный">Винительный</option>
                            <option value="творительный">Творительный</option>
                            <option value="предложный">Предложный</option>
                        </select>
                    )}
                    <button
                        onClick={() => {
                            if (selectedFilter === "части речи") {
                                handleFilterByPartOfSpeech();
                            } else if (selectedFilter === "рода") {
                                handleFilterByGender();
                            } else if (selectedFilter === "падежа") {
                                handleFilterByCase();
                            }
                        }}
                    >
                        Фильтр
                    </button>
                    <textarea value={filterResults}></textarea>
                </div>
            )}
        </div>
    );
};

export default ViewData;
