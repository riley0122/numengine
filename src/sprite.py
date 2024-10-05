from tkinter import *
import tkinter as tk
from tkinter import ttk, filedialog, simpledialog
from PIL import Image
import numpy as np
import os

SCREEN_HEIGHT = 240
SCREEN_WIDTH = 320

current_project = ""

def generate_sprite():
    global current_directory
    sprite_image = filedialog.askopenfilename(filetypes=[("PNG image files", ".png")])
    sprite_name = simpledialog.askstring("Name", "What is this sprite called?")

    if sprite_image and sprite_name and current_project:
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

        resized_img = img.resize((new_w, new_h), Image.Resampling.LANCZOS)

        resized_img = resized_img.convert("RGB")
        pixel_data = np.array(resized_img)

        hpp_content = "#pragma once\n\n"
        hpp_content += '#include "numengine/sprite.hpp"\n\n'
        hpp_content += "using namespace numengine;\n\n"

        hpp_content += "sprite_image_data_block image_data[] = {\n"

        visited = np.zeros((new_h, new_w), dtype=bool)

        def find_colour_block(x, y):
            """Find the largest block of continous colour from a point"""
            r, g, b = pixel_data[y, x]
            colour = (r << 16) | (g << 8) | b

            width = 0
            height = 0

            for i in range(x, new_w):
                if visited[y, i]:
                    break
                r2, g2, b2 = pixel_data[y, i]
                if (r2 << 16 | g2 << 8 | b2) != colour:
                    break
                width += 1

            for j in range(y, new_h):
                for i in range(x, x + width):
                    if visited[j, i]:
                        return width, height
                    r2, g2, b2 = pixel_data[j, i]
                    if (r2 << 16 | g2 << 8 | b2) != colour:
                        return width, height
                height += 1
        
            return width, height

        for y in range(new_h):
            for x in range(new_w):
                if not visited[y, x]:
                    block_w, block_h = find_colour_block(x, y)
                    r, g, b = pixel_data[y, x]
                    hex_colour = (r << 16) | (g << 8) | b

                    hpp_content += f"\t{'{'} {x}, {y}, {block_w}, {block_h}, EADK::Color({hex(hex_colour)}) {'}'},"

                    for j in range(y, y + block_h):
                        for i in range(x, x + block_w):
                            visited[j, i] = True
        
        hpp_content += "};\n\n"

        hpp_content += f"sprite {sprite_name}(std::vector<sprite_image_data_block>(std::begin(image_data), std::end(image_data)));\n"

        sprite_path = os.path.join(current_project, "src", "game", "sprites")
        if not os.path.exists(sprite_path):
            os.makedirs(sprite_path)
        
        with open(os.path.join(sprite_path, f"{sprite_name}.hpp"), "w+") as f:
            f.write(hpp_content)

def open_sprite_editor(root, current):
    global current_project
    new_window = tk.Toplevel(root)

    new_window.title("Sprite editor")
    new_window.geometry("200x200")

    title = ttk.Label(new_window, text="Sprite editor", font=("Arial", 16))
    title.pack(pady=20)

    current_project = current

    generate_button = ttk.Button(new_window, text="Generate sprite", command=generate_sprite)
    generate_button.pack(pady=10)
