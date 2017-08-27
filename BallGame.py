from tkinter import *
import random
import time
from tkinter import messagebox


class Ball:
    def __init__(self, canvas, paddle, color):
        self.canvas = canvas
        self.paddle = paddle
        self.id = canvas.create_oval(10, 10, 25, 25, fill=color)
        self.canvas.move(self.id, 245, 100)
        starts = [-1.5, -1, -0.5, 0.5, 1, 1.5]
        random.shuffle(starts)
        self.x = starts[0]
        self.y = -1.5
        self.canvas_height = self.canvas.winfo_height()
        self.canvas_width = self.canvas.winfo_width()
        self.hit_bottom = False

    def hit_paddle(self, pos):
        paddle_pos = self.canvas.coords(self.paddle.id)
        if pos[2] >= paddle_pos[0] and pos[0] <= paddle_pos[2]:
            if pos[3] >= paddle_pos[1] and pos[3] <= paddle_pos[3]:
                return True
        return False

    def draw(self, k):
        self.canvas.move(self.id, self.x * k, self.y * k)
        pos = self.canvas.coords(self.id)
        if pos[1] <= 0:
            self.y = -self.y
        if pos[3] >= self.canvas_height:
            self.hit_bottom = True
        if pos[0] <= 0:
            self.x = -self.x
        if pos[2] >= self.canvas_width:
            self.x = -self.x
        if self.hit_paddle(pos):
            self.y = -self.y


class Paddle:
    def __init__(self, canvas, color):
        self.canvas = canvas
        self.id = canvas.create_rectangle(0, 0, 100, 10, fill=color)
        self.canvas.move(self.id, 200, 300)
        self.x = 0
        self.canvas_width = self.canvas.winfo_width()
        self.canvas.bind_all('<KeyPress-Left>', self.turn_left)
        self.canvas.bind_all('<KeyPress-Right>', self.turn_right)

    def draw(self):
        pos = self.canvas.coords(self.id)
        if pos[0] <= 0:
            self.x = max(self.x, 0)
        elif pos[2] >= self.canvas_width:
            self.x = min(self.x, 0)
        self.canvas.move(self.id, self.x, 0)

    def turn_left(self, evt):
        self.x = -2

    def turn_right(self, evt):
        self.x = 2


tk = Tk()
tk.title("PaddleGame")
tk.resizable(0, 0)
tk.wm_attributes("-topmost", 1)
canvas = Canvas(tk, width=500, height=400, bd=0, highlightthickness=0)
canvas.pack()
tk.update()

paddle = Paddle(canvas, 'red')
ball = Ball(canvas, paddle, 'red')

t1 = time.time()

while 1:
    t2 = time.time()
    k = 1 + (t2 - t1) / 10
    if not ball.hit_bottom:
        ball.draw(k)
        paddle.draw()
    else:
        # canvas.create_text(250, 150, text='You Suck!\n%.2f seconds' % (t2 - t1))
        break
    tk.update_idletasks()
    tk.update()
    time.sleep(0.01)

tk.quit()
messagebox._show(title="StickmanGame", message='You Suck!\n%.2f seconds' % (t2 - t1))
