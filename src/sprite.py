from tkinter import *
import tkinter as tk
from tkinter import ttk, filedialog
from PIL import Image, ImageTk

SCREEN_HEIGHT = 240
SCREEN_WIDTH = 320

def generate_sprite():
    sprite_image = filedialog.askopenfilename(filetypes=[("PNG image files", ".png")])

    if sprite_image:
        img = Image.open(sprite_image)

        original_w, original_h = img.size

        aspect_ratio = original_w / original_h

        if original_w > SCREEN_WIDTH or original_h > SCREEN_HEIGHT:
            w_ratio = SCREEN_WIDTH / original_w
            h_ratio = SCREEN_HEIGHT / original_h
            scale = min(w_ratio, h_ratio)

            new_w = int(original_w * scale)
            new_h = int(original_h * scale)
        else:
            new_w, new_h = original_w, original_h

        resized_img = img.resize((new_w, new_h), Image.ANTIALIAS)
        
        # TODO: convert to .hpp file

def open_sprite_editor(root):
    new_window = tk.Toplevel(root)

    new_window.title("Sprite editor")
    new_window.geometry("200x200")

    title = ttk.Label(new_window, text="Sprite editor", font=("Arial", 16))
    title.pack(pady=20)

    generate_button = ttk.Button(new_window, text="Generate sprite", command=generate_sprite)
    generate_button.pack(pady=10)
