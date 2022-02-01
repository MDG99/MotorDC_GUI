#Este es un código de ejemplo para dibujar un rectángulo e
# incluir controles dentro de este

import tkinter as tk

root = tk.Tk()
root.geometry('170x130')

# Outside the Rectangle
lbl = tk.Label(root, text='Test:')
e = tk.Entry(root)

lbl.grid(row=0, column=0)
e.grid(row=0, column=1, columnspan=2)

# The Rectangle
rectangle = tk.Frame(root, highlightthickness=2, highlightbackground='black')
rectangle.grid(row=1, column=0, columnspan=3, ipadx=40, ipady=20)

# Inside the Rectangle
b1 = tk.Button(rectangle, text='1')
b2 = tk.Button(rectangle, text='2')
b3 = tk.Button(rectangle, text='3')

b1.grid(row=0, column=0)
b2.grid(row=0, column=1)
b3.grid(row=0, column=2)

root.mainloop()
