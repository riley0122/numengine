from tkinter import *
from tkinter import filedialog, ttk, simpledialog, messagebox
import tkinter as tk
from ttkthemes import ThemedTk
import os
import platform
import subprocess
import shutil
from sprite import open_sprite_editor

console_out_text = ""
error_out_text = ""

def set_project_directory(dir=""):
    global current_project, console_out_text
    if dir=="":
        folder_selected = filedialog.askdirectory()
    else:
        folder_selected = dir

    if folder_selected:
        current_project = folder_selected
        console_out_text += f"Project directory set to {current_project}"
        update_console_output()
        print(f"Project directory set to {current_project}")
        project_title_var.set(f"Current Project: {os.path.basename(current_project)}")

def open_in_editor():
    if current_project:
        root.config(cursor="watch")
        root.update()
        file_to_open = os.path.join(current_project, "src", "game")
        try:
            x = subprocess.run(["code", file_to_open], capture_output=True, text=True)
        except Exception as e:
            print(f"Error opening code! {e}")
        root.config(cursor="")
        root.update()
    else:
        print(f"game directory does not exist!")

def show_in_folder(dir=""):
    if dir == "": dir = current_project
    if current_project:
        if platform.system() == "Windows":
            os.startfile(dir)
        elif platform.system() == "Darwin":
            x = subprocess.run(["open", dir])
        else:
            x = subprocess.run(["xdg-open", dir])

def build():
    global console_out_text, error_out_text
    if current_project:
        console_out.delete(1.0, END)
        root.config(cursor="watch")
        root.update()
        os.chdir(current_project)
        x = subprocess.run(["make", "clean"], capture_output=True, text=True)
        console_out_text += x.stdout
        error_out_text += x.stderr
        update_console_output()
        x = subprocess.run(["make"], capture_output=True, text=True)
        console_out_text += x.stdout
        error_out_text += x.stderr
        update_console_output()
        root.config(cursor="")
        root.update()
        show_in_folder(os.path.join(current_project, "target"))
    
def build_and_run():
    global console_out_text, error_out_text
    if current_project:
        console_out.delete(1.0, END)
        root.config(cursor="watch")
        root.update()
        os.chdir(current_project)
        x = subprocess.run(["make", "clean"], capture_output=True, text=True)
        console_out_text += x.stdout
        error_out_text += x.stderr
        update_console_output()
        x = subprocess.run(["make", "run"], capture_output=True, text=True)
        console_out_text += x.stdout
        error_out_text += x.stderr
        update_console_output()
        root.config(cursor="")
        root.update()

def update_console_output():
    console_out.config(state=NORMAL)
    global console_out_text, error_out_text
    console_out.delete(1.0, END)
    console_out.insert(END, f"Console Output:\n{console_out_text}\n")
    if error_out_text:
        console_out.insert(END, f"Errors:\n{error_out_text}\n")

    console_out_text = ""
    error_out_text = ""
    console_out.config(state=DISABLED)
    
def create_project():
    global current_project
    folder_selected = filedialog.askdirectory()
    if folder_selected:
        if len(os.listdir(folder_selected)) == 0:
            current_project = folder_selected
        else:
            name = simpledialog.askstring("Name", "What is the name of the project", parent=root)
            current_project = os.path.join(folder_selected, name)
            if os.path.exists(current_project) and not os.path.isfile(current_project):
                messagebox.showerror("error", f"There is already a folder named {name}")
                return
            
        project_dir = os.path.join(os.path.abspath(os.path.join(os.path.dirname(__file__), "..")), "projectSource")
        shutil.copytree(project_dir, current_project)
        set_project_directory(current_project)

root = ThemedTk(theme="breeze")
root.title("numengine")
root.minsize(200, 200)
root.maxsize(500, 800)
root.geometry("500x600+50+50")

set_dir_button = ttk.Button(root, text="Open project", command=set_project_directory)
set_dir_button.pack(padx=10, pady=10)

create_project_button = ttk.Button(root, text="Create new project", command=create_project)
create_project_button.pack(padx=10, pady=5)

current_project = os.getcwd()
project_title_var = StringVar(value=f"Current Project: {os.path.basename(current_project)}")

project_title_label = ttk.Label(root, textvariable=project_title_var, font=("Arial", 16))
project_title_label.pack(pady=20)

open_editor_button = ttk.Button(root, text="Open in vscode", command=open_in_editor)
open_editor_button.pack(pady=10)

show_folder_button = ttk.Button(root, text="Show in Folder", command=show_in_folder)
show_folder_button.pack(pady=10)

build_button = ttk.Button(root, text="Build project", command=build)
build_button.pack(pady=10)

run_on_calc_button = ttk.Button(root, text="Run project on calculator", command=build_and_run)
run_on_calc_button.pack(pady=10)

console_out = Text(root, height=10, width=50)
console_out.pack()
console_out.config(state=DISABLED)

sprite_editor_button = ttk.Button(root, text="Open sprite editor", command=lambda:open_sprite_editor(root))
sprite_editor_button.pack(pady=10)

root.mainloop()
