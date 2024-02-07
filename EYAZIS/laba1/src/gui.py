import nltk
import docx
import tkinter as tk
import tkinter.filedialog as fd

from src.realisation import *

nltk.download('punkt')

def generate_bttn(word, input1_entry, input2_entry, input3_entry, input4_entry):
    word.delete(1.0, tk.END)
    base = input1_entry.get()
    gender = input2_entry.get()
    case = input3_entry.get()
    numb = input4_entry.get()
    word.insert(tk.END, generate_word_form(base, gender, case, numb))
    input1_entry.delete(0, tk.END)
    input2_entry.delete(0, tk.END)
    input3_entry.delete(0, tk.END)
    input4_entry.delete(0, tk.END)

def open_file():
    filetypes = (
        ('DOCX', '*.docx'),
        ('DOC', '*.doc')
    )
    filename = fd.askopenfilename(
        title='Open a file',
        initialdir='/',
        filetypes=filetypes
    )
    if filename:
        doc = docx.Document(filename)
        text = '\n'.join([paragraph.text for paragraph in doc.paragraphs])
        text = get_lexems_to_text(get_lexemes(text))
        new_window = tk.Toplevel()
        new_window.title(filename)
        new_window.geometry('400x300')
        text_widget = tk.Text(new_window)
        text_widget.insert('1.0', text)
        text_widget.pack()

def create_window():
    root = tk.Tk()
    root.title('DOC Reader')
    root.geometry('400x300')

    open_frame = tk.Frame(root)
    open_frame.pack(pady=10)

    open_button = tk.Button(open_frame, text='Открыть файл doc или docx', command=open_file)
    open_button.pack()

    input_frame = tk.Frame(root)
    input_frame.pack(pady=10)

    input1_label = tk.Label(input_frame, text='Основа слова:')
    input1_label.grid(row=0, column=0, padx=5, pady=5)
    input1_entry = tk.Entry(input_frame)
    input1_entry.grid(row=0, column=1, padx=5, pady=5)

    input2_label = tk.Label(input_frame, text='Род:')
    input2_label.grid(row=1, column=0, padx=5, pady=5)
    input2_entry = tk.Entry(input_frame)
    input2_entry.grid(row=1, column=1, padx=5, pady=5)

    input3_label = tk.Label(input_frame, text='Падеж:')
    input3_label.grid(row=2, column=0, padx=5, pady=5)
    input3_entry = tk.Entry(input_frame)
    input3_entry.grid(row=2, column=1, padx=5, pady=5)

    input4_label = tk.Label(input_frame, text='Число:')
    input4_label.grid(row=3, column=0, padx=5, pady=5)
    input4_entry = tk.Entry(input_frame)
    input4_entry.grid(row=3, column=1, padx=5, pady=5)

    generate_button = tk.Button(root, text='Генерация слова', command=lambda: generate_bttn(word, input1_entry, input2_entry, input3_entry, input4_entry))
    generate_button.pack(pady=10)

    word = tk.Text(root)
    word.pack()

    root.mainloop()