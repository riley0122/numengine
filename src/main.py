from tkinter import *
from tkinter import filedialog, ttk
from ttkthemes import ThemedTk
import os
import platform
import subprocess

def set_project_directory():
    global current_project
    folder_selected = filedialog.askdirectory()
    if folder_selected:
        current_project = folder_selected
        print(f"Project directory set to {current_project}")
        project_title_var.set(f"Current Project: {os.path.basename(current_project)}")

def open_in_editor():
    if current_project:
        root.config(cursor="watch")
        root.update()
        file_to_open = os.path.join(current_project, "src", "game")
        try:
            subprocess.run(["code", file_to_open])
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
            subprocess.run(["open", dir])
        else:
            subprocess.run(["xdg-open", dir])

def build():
    if current_project:
        root.config(cursor="watch")
        root.update()
        os.chdir(current_project)
        subprocess.run(["make", "clean"])
        subprocess.run(["make"])
        root.config(cursor="")
        root.update()
        show_in_folder(os.path.join(current_project, "target"))
    
def build_and_run():
    if current_project:
        root.config(cursor="watch")
        root.update()
        os.chdir(current_project)
        subprocess.run(["make", "clean"])
        subprocess.run(["make", "run"])
        root.config(cursor="")
        root.update()


root = ThemedTk(theme="breeze")
root.title("numengine")
root.minsize(200, 200)
root.maxsize(500, 800)
root.geometry("500x600+50+50")

set_dir_button = ttk.Button(root, text="Open project", command=set_project_directory)
set_dir_button.pack(pady=20)

current_project = ""
project_title_var = StringVar(value="Current Project: None")

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

root.mainloop()
