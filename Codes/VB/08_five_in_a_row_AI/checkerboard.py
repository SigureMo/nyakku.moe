import numpy as np

class CheckerBoard():

    def __init__(self, shape = (19, 19)):
        self.shape = shape
        self.matrix = np.zeros(shape, dtype=np.uint8)

    def put(self, position, value):
        self.matrix[position[0], position[1]] = value

    def get(self, position):
        return self.matrix[position[0], position[1]]

    def get_status(self, position):
        winner = 0
        value = self.get(position)
        same_num = 0

        for i in range(-4, 5):
            if 0 <= position[0] + i < self.shape[0]:
                if self.get((position[0] + i, position[1])) == value:
                    same_num += 1
                    if same_num >= 5:
                        winner = value
                else:
                    same_num = 0
        same_num = 0

        for i in range(-4, 5):
            if 0 <= position[1] + i < self.shape[1]:
                if self.get((position[0], position[1] + i)) == value:
                    same_num += 1
                    if same_num >= 5:
                        winner = value
                else:
                    same_num = 0
        same_num = 0

        for i in range(-4, 5):
            if 0 <= position[0] + i < self.shape[0] and 0 <= position[1] + i < self.shape[1]:
                if self.get((position[0] + i, position[1] + i)) == value:
                    same_num += 1
                    if same_num >= 5:
                        winner = value
                else:
                    same_num = 0
        same_num = 0

        for i in range(-4, 5):
            if 0 <= position[0] + i < self.shape[0] and 0 <= position[1] - i < self.shape[1]:
                if self.get((position[0] + i, position[1] - i)) == value:
                    same_num += 1
                    if same_num >= 5:
                        winner = value
                else:
                    same_num = 0
        same_num = 0

        for i in range(self.shape[0]):
            for j in range(self.shape[1]):
                if self.get((i, j)) != 0:
                    full = False
                    break
            else:
                continue
            break
        else:
            full = True

        if winner:
            return winner
        elif full:
            return 3
        else:
            return 0

    def clear(self):
        for i in range(self.shape[0]):
            for j in range(self.shape[1]):
                self.put((i, j), 0)

cb = CheckerBoard()
cb.put((0,4), 1)
print(cb.get_status((0, 4)))
cb.put((1,3), 1)
print(cb.get_status((1, 3)))
cb.put((2,2), 1)
print(cb.get_status((2, 2)))
cb.put((3,1), 1)
print(cb.get_status((3, 1)))
cb.put((4,0), 1)
print(cb.get_status((4, 0)))
print(cb.matrix)


