# 定义方向常量
UP = (0, -1)
DOWN = (0, 1)
LEFT = (-1, 0)
RIGHT = (1, 0)


class GameGraph:
    def __init__(self, snake, food, bounds):
        self.snake = snake
        self.food = food
        self.xmax = bounds['xmax']
        self.xmin = bounds['xmin']
        self.ymax = bounds['ymax']
        self.ymin = bounds['ymin']

    def set_food(self, food):
        self.food = food

    def set_snake(self, snake):
        self.snake = snake


class Node:
    def __init__(self, position, parent=None):
        self.position = position
        self.parent = parent
        self.g = 0  # 沉没成本
        self.h = 0  # 估计成本(曼哈顿距离)
        self.f = 0  # 总成本


def pathfinding_prep(game_graph, start, target):
    open_list = []  # 亟待计算f值的格子
    close_list = []  # 已经完成计算(走过)的格子

    start_node = Node(start)
    target_node = Node(target)

    open_list.append(start_node)

    while open_list:
        current_node = Node(open_list[0])
        current_index = 0

        for index, node in enumerate(open_list):
            if node.f < current_node.f:
                current_node = node
                current_index = index
        open_list.pop(current_index)
        close_list.append(current_node)

        if current_node.position == target_node.position:
            path = []
            while current_node:
                path.append(current_node.parent)
            path = path[::-1]
            direction = (path[1].position[0]-path[0].position[0],
                         path[1].position[1]-path[1].position[1])
            return direction

        neighbours = []
        for direction in [UP, DOWN, LEFT, RIGHT]:
            node_position = (current_node.position[0] + direction[0],
                             current_node.position[1] + direction[1])
            if (node_position[0] > game_graph.xmax or
                    node_position[0] < game_graph.xmin or
                    node_position[1] > game_graph.ymax or
                    node_position[1] < game_graph.ymin or
                    node_position in game_graph.snake):
                continue
            new_node = Node(node_position, current_node)
            neighbours.append(new_node)

        for neighbour in neighbours:
            if neighbour in close_list:
                continue
            neighbour.g = current_node.g + 1
            neighbour.h = (abs(target_node.position[0] - neighbour.position[0])
                           + abs(target_node.position[1] - neighbour.position[1]))
            neighbour.f = neighbour.g + neighbour.h
            if any(neighbour.position == open_node.position and neighbour.g > open_node.g
                   for open_node in open_list
                   ):
                continue
            open_list.append(neighbour)
    return None


def pathfinding(game_graph):
    start1 = game_graph.snake[0]
    target1 = game_graph.food
    start2 = game_graph.food
    target2 = game_graph.snake[-1]
    if pathfinding_prep(game_graph, start1, target1) \
            and pathfinding_prep(game_graph, start2, target2):
        return pathfinding_prep(game_graph, start1, target1)
    else:
        return pathfinding_prep(game_graph, start1, target2)
