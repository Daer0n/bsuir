import tkinter as tk
from tkinter import filedialog, messagebox, scrolledtext
from my import main


class ReferencerApp(tk.Tk):
    def __init__(self):
        super().__init__()

        self.title('Automatic Referencer')
        self.geometry('700x500')

        self.file_link = ''
        self.create_widgets()

    def create_widgets(self):
        # Frame for menu with border
        menu_frame = tk.Frame(self, bd=2, relief=tk.SUNKEN, bg="lightgrey")  # Adding border
        menu_frame.pack(side=tk.LEFT, fill=tk.Y, padx=10, pady=10)

        title_label = tk.Label(menu_frame, text="Menu", font=("Arial", 16), bg="lightgrey")
        title_label.pack(pady=10)

        self.upload_button = tk.Button(menu_frame, text="Upload Text Document", command=self.upload_document, width=20, height=2)
        self.upload_button.pack(pady=10)

        self.save_button = tk.Button(menu_frame, text="Save Summary", command=self.save_summary, state="disabled", width=20, height=2)
        self.save_button.pack(pady=10)

        self.print_button = tk.Button(menu_frame, text="Print Summary", command=self.print_summary, state="disabled", width=20, height=2)
        self.print_button.pack(pady=10)

        self.help_button = tk.Button(menu_frame, text="Help", command=self.display_help, width=20, height=2)
        self.help_button.pack(pady=10)

        # Frame for results
        result_frame = tk.Frame(self)
        result_frame.pack(side=tk.RIGHT, fill=tk.BOTH, expand=True, padx=10, pady=10)

        self.result_label = tk.Label(result_frame, text="Result will be shown here...", wraplength=800, justify=tk.LEFT)
        self.result_label.pack(pady=10, padx=20)

        self.link_label = tk.Label(result_frame, text="", fg="blue", cursor="hand2", font=("Arial", 12, "underline"))
        self.link_label.pack(pady=10)
        self.link_label.bind("<Button-1>", self.open_link)

    def upload_document(self):
        file_path = filedialog.askopenfilename(title="Select A Text File", filetypes=(("Text files", "*.txt"), ("All files", "*.*")))
        if file_path:
            with open(file_path, 'r') as file:
                self.file_link = file.readline().strip()
                self.link_label["text"] = self.file_link

            self.data = main(file_path.split("/")[-1])  # Assuming main() returns a list
            self.summary = "This is the summary that your text processing function returns"
            self.result_label["text"] = self.summary
            self.save_button["state"] = "normal"
            self.print_button["state"] = "normal"
        else:
            messagebox.showwarning("Warning", "Please select a text file.")

    def save_summary(self):
        save_path = filedialog.asksaveasfilename(defaultextension=".txt")
        if save_path:
            with open(save_path, 'w', encoding="utf-8") as f:
                f.write('Classic Referat\n')
                f.write(self.data[0] + '\n\n')
                f.write('Key Words\n')
                f.write(self.data[1] + '\n\n')
            messagebox.showinfo("Saved", f"Summary saved to {save_path}")

    def print_summary(self):
        print_window = tk.Toplevel(self)
        print_window.title("Printed Summary")
        text_area = scrolledtext.ScrolledText(print_window, wrap=tk.WORD, width=100, height=30)
        text_area.pack(padx=10, pady=10)

        # Display formatted data
        text_area.insert(tk.INSERT, 'Classic Referat\n')
        text_area.insert(tk.INSERT, self.data[0] + '\n\n')
        text_area.insert(tk.INSERT, 'Key Words\n')
        text_area.insert(tk.INSERT, self.data[1] + '\n\n')
        print(self.data[1])

    def display_help(self):
        messagebox.showinfo("Help",
                            "1. Click 'Upload Text Document' to upload a document.\n"
                            "2. Click 'Save Summary' to save the generated summary.\n"
                            "3. Click 'Print Summary' to print the summary.")

    def open_link(self, event):
        import webbrowser
        webbrowser.open(self.file_link)


if __name__ == "__main__":
    app = ReferencerApp()
    app.mainloop()