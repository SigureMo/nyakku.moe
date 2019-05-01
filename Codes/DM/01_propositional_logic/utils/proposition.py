import numpy as np

class ValueError(Exception):
    pass

class Proposition():
    def __init__(self):
        self.__value = None
        self.metas = []

    def get_value(self):
        if self.__value is None:
            raise ValueError
        return self.__value

    def set_value(self, value):
        self.__value = value

class MetaProposition(Proposition):
    """ 原子命题类 """
    def __init__(self, name, value = None):
        super().__init__()
        self.name = name
        self.metas = [self]
        if value is not None:
            self.set_value(value)

class CompoundProposition(Proposition):
    """ 复合命题类 """
    def __init__(self, statement, *propositions):
        super().__init__()
        self.statement = statement
        self.propositions = propositions
        for p in propositions:
            self.metas.extend(p.metas)
        self.metas = list(set(self.metas))

    def get_value(self):
        return self.statement(*self.propositions)

    def set_value(self, value):
        raise ValueError

    def get_axis(self):
        """ 获取所有情况的索引值 """
        axis = [[]]
        for _ in range(len(self.metas)):
            tmp_axis = []
            for item in axis:
                item0 = list(item)
                item1 = list(item)
                item0.append(0)
                item1.append(1)
                tmp_axis.append(item0)
                tmp_axis.append(item1)
            del axis
            axis = list(tmp_axis)
            del tmp_axis
        axis.reverse()
        return axis

    def truth_table(self):
        """ 生成真值表 """
        axis = self.get_axis()
        table = np.zeros([2 for _ in range(len(self.metas))], dtype=np.bool_)
        for item in axis:
            for i in range(len(item)):
                self.metas[i].set_value(bool(item[i]))
            table_item = table
            for i in range(len(item)-1):
                table_item = table_item[item[i]]
            table_item[item[-1]] = self.get_value()
        return table

    def print_table(self):
        """ 打印真值表 """
        axis = self.get_axis()
        table = self.truth_table()
        for meta in self.metas:
            print('%s\t' % meta.name, end = "")
        print('truth')
        for item in axis:
            for value in item:
                print('%s\t' % bool(value), end = "")
            table_item = table
            for i in range(len(item)):
                table_item = table_item[item[i]]
            print(table_item)

    def equal_to(self, q):
        """ 判断两个命题逻辑（其内的复合语句）是否等价 """
        p = self
        axis = self.get_axis()
        if set(p.metas) != set(q.metas):
            return False
        metas = p.metas
        for item in axis:
            for i in range(len(item)):
                metas[i].set_value(bool(item[i]))
            if p.get_value() != q.get_value():
                return False
        return True

