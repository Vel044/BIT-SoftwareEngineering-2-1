from turtle import *
from random import *
from pathfinding import GameGraph, pathfinding


def square(x, y, size, sq_color):
    """绘制小正方形, 代表一格"""
    penup()
    goto(x, y)
    color(sq_color)
    pendown()

    begin_fill()
    for i in range(4):
        forward(size)
        left(90)
    end_fill()


def frame():
    """绘制边框"""
    for i in range(-210, 200, 10):
        square(i, -200, 10, 'gray')
        square(i, 200, 10, 'gray')
    for i in range(-200, 200, 10):
        square(-210, i, 10, 'gray')
        square(190, i, 10, 'gray')


def change(direction):
    """改变蛇的运动方向"""
    global aim_x, aim_y
    x, y = direction
    if x != -aim_x or y != -aim_y:     
        aim_x = x
        aim_y = y


def inside(head_x, head_y):
    """判断蛇是否在边框内"""
    if -210 < head_x < 190 and -200 < head_y < 200:
        return True
    else:
        return False


all_food = []                  # 所有食物的位置
for x in range(-200, 190, 10):
    for y in range(-190, 200, 10):
        all_food.append((x, y))


def new_food():
    """随机生成食物位置"""
    food = all_food.copy()
    for i in snake:            # 去掉蛇所在的位置
        food.remove(i)
    new_food_x, new_food_y = food.pop(randint(0, len(food) - 1))
    return new_food_x, new_food_y


snake = [(0, 0)]               # 蛇的起始位置
food_x, food_y = new_food()    # 食物的起始位置
aim_x, aim_y = 0, 0            # 蛇的起始方向


def move():
    global food_x, food_y

    change(pathfinding(game_graph))
    head_move_x = snake[-1][0] + aim_x
    head_move_y = snake[-1][1] + aim_y

    # 判断是否撞到边框或者撞到自己
    if not inside(head_move_x, head_move_y) or [head_move_x, head_move_y] in snake:
        square(head_move_x, head_move_y, 10, 'red')
        update()
        print('得分: ', len(snake))
        return
    
    snake.append((head_move_x, head_move_y))

    # 判断是否吃到食物以及是否胜利
    if head_move_x == food_x and head_move_y == food_y:
        if len(snake) == len(all_food):
            print('YOU WIN!')
            return
        else:
            food_x, food_y = new_food()
            # 更新game_graph中的食物和蛇的位置
            game_graph.set_food((food_x, food_y))
            game_graph.set_snake(snake)
    else:
        snake.pop(0)
        game_graph.set_snake(snake)

    clear()

    # 绘制边框, 蛇和食物
    frame()
    for body in snake:
        square(body[0], body[1], 10, 'black')
    square(food_x, food_y, 10, 'green')
    update()
    # 100ms后重新调用move，相当于一个内循环，直至return
    ontimer(move)


setup(420, 420)
title('贪吃蛇')
hideturtle()
tracer(False)
game_graph = GameGraph(snake.copy(), (food_x, food_y), {'xmin': -200, 'xmax': 180, 'ymin': -190, 'ymax': 190})
move()
done()
