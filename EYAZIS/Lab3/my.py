import math
import re
import time

from langdetect import detect
from nltk.corpus import stopwords
from summarizer import Summarizer


def timing_decorator(func):
    def wrapper(*args, **kwargs):
        start_time = time.time()
        result = func(*args, **kwargs)
        end_time = time.time()
        execution_time = end_time - start_time
        print(f"Время выполнения функции '{func.__name__}': {execution_time} секунд")
        print('------------------------------------------------------')
        print(result)
        return result

    return wrapper


def read_article(file_name):
    with open(file_name, "r", encoding='utf-8') as file:
        filedata = file.read()

    filedata = filedata[filedata.find("\n"):]
    article = filedata.split(".")
    sentences = []

    for sentence in article:
        if len(sentence) > 3:
            lang = detect(sentence) 
            if lang == 'fr': 
                sentences.append(
                    [item for item in re.sub("[^a-zA-ZàâçéèêëîïôûùüÿñæœÀÂÇÉÈÊËÎÏÔÛÙÜŸÑÆŒ]", " ", sentence).split(" ") if
                     item != ''])
            else:
                sentences.append([item for item in re.sub("[^a-zA-Z]", " ", sentence).split(" ") if item != ''])

    return sentences


def get_word_freq(word, text):
    word_freq = 0

    for sentence in text:
        word_freq += word_freq_sent(word, sentence)

    return word_freq


def get_max_word_freq(text):
    words_freq = dict()
    max_freq = 0

    for sentence in text:
        for cur_word in sentence:
            if cur_word in words_freq:
                if words_freq[cur_word] > max_freq:
                    max_freq = words_freq[cur_word]
                words_freq[cur_word] += 1
            else:
                words_freq[cur_word] = 1

    return max_freq


def texts_with_word(word, texts):
    text_count = 0

    for text in texts:
        for sentence in text:
            if word in sentence:
                text_count += 1
                break

    return text_count


def word_freq_sent(word, sentence):
    word_freq = 0

    for cur_word in sentence:
        if cur_word == word:
            word_freq += 1

    return word_freq


def word_weight(word, text, texts):
    weigth = 0.5 * (1 + get_word_freq(word, text) / get_max_word_freq(text)) * math.log(
        len(texts) / texts_with_word(word, texts))
    return weigth


def get_score(sentence, text, texts, stopwords):
    score = 0
    for word in sentence:
        if word not in stopwords:
            score += word_freq_sent(word, sentence) * word_weight(word, text, texts)
    return score


def get_pos(sentence: list, text: str):
    return 1 - text.find(' '.join(sentence)) / len(text)


def get_stopwords(lang):
    if lang == 'fr':
        return stopwords.words('french')
    elif lang == 'en':
        return stopwords.words('english')
    else:
        return []


@timing_decorator
def generate_summary(file_name, texts, top_n=5):
    lang = texts[0][0][0]  

    if isinstance(lang, str):
        lang = detect(lang)
    else:
        lang = 'unknown'
    stop_words = get_stopwords(lang)  

    statistic = []
    sentences = read_article(file_name)

    text = ''
    for sentence in sentences:
        text += ' '.join(sentence) + '.'

    for sentence in sentences:
        statistic.append([sentence, get_score(sentence, sentences, texts, stop_words), get_pos(sentence, text)])

    statistic.sort(key=lambda x: x[1], reverse=True)
    most_weight = statistic[:top_n]
    most_weight.sort(key=lambda x: x[2], reverse=True)

    for item in most_weight:
        for it in item:
            print(it, sep=" ")
        print()

    text = ''
    for i in range(len(most_weight)):
        text += ' '.join(most_weight[i][0]) + '\n'

    print("all text with weights:", "*" * 100)
    print(text)

    return text


def main(file_name):
    refs = []
    text_names = [file_name]

    @timing_decorator
    def classic_referat_and_key_words():

        texts = []

        for text_name in text_names:
            texts.append(read_article(text_name))

        result = []
        for summary in text_names:
            result.append(generate_summary(summary, texts))

        print("Реферат в виде списка ключевых слов: ", "*" * 100)

        words = dict()
        stop_words_ru = get_stopwords('en')  
        stop_words_de = get_stopwords('fr') 

        for sentence in texts:
            for item in sentence:
                for term in item:
                    if term.lower() not in words and term.lower() not in stop_words_ru and term.lower() not in stop_words_de and term != '':
                        words[term] = get_word_freq(term, texts[0])

        sorted_words = sorted(words.items(), key=lambda x: x[1], reverse=True)

        r = ""
        for i in range(len(sorted_words)):
            r += str(sorted_words[i])

        result.append(r)

        return result

    @timing_decorator
    def ml_referat():

        with open(text_names[0], encoding='utf-8') as f:
            document = f.read()

        document = document[document.find("\n"):]

        summarizer = Summarizer()
        summary = summarizer.get_summary(document, 'Summary')

        print("Summary")

        print(summary)

        return summary

    refs.extend(classic_referat_and_key_words())

    refs.append(ml_referat())

    return refs


if __name__ == '__main__':
    main("en.txt")
