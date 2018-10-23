import numpy as np
import matplotlib.pyplot as plt
from testCases import *
# import sklearn
# import sklearn.datasets
# import sklearn.linear_model
import time
from planar_utils import plot_decision_boundary, sigmoid, load_planar_dataset, load_extra_datasets

'''
提前适应深层神经网络，增加可移植性
参考：https://blog.csdn.net/u013733326/article/details/79702148
'''

'''
m = 400
n0 2 input
n1 4 hidden
n2 1 output
W1 (4, 2)
W2 (1, 4)
'''

X, Y = load_planar_dataset()

# plt.scatter(X[0, :], X[1, :], c=np.squeeze(Y), s=40, cmap=plt.cm.Spectral)
# plt.show()

# print(X.shape, Y.shape)

# 基本完工，参照原来的浅层神经网络直接做了深层的，可以直接改参数变成深层神经网络
# 激活函数这部分弄了个装饰器，但是，就简化了两行代码和一个默认参数，暂时这样吧
# 各种参数都放在下面了，想用直接改就好
seed = 1017
layer = 4
num_iterations = 500000
learning_rate = 0.05
g = ('None', 'ReLU', 'tanh', 'sigmoid')
n = (X.shape[0], 50, 10, Y.shape[0])
m = Y.shape[1]

def activation(func):
    def fun(Z, derivative = False):
        shape = Z.shape
        g = func(Z, derivative)
        assert g.shape == shape
        return g
    return fun

def logistic(Y, Y_, derivative = False):
    assert Y.shape == Y_.shape
    shape = Y.shape
    Y_ = np.where(Y_<=0, 10**-10, Y_) # 防止小于0出错
    if not derivative:
        l = np.multiply(np.log(Y_), Y) + np.multiply((1 - Y), np.log(1 - Y_))
    else:
        l = - np.true_divide(Y, Y_) + np.true_divide((1-Y), (1-Y_))
    assert l.shape == shape
    return l

@activation
def ReLU(Z, derivative):
    if not derivative:
        g = np.where(Z>0, Z, 0)
    else:
        g = np.where(Z>0, 1, 0)
    return g

@activation
def Leaky_ReLU(Z, derivative):
    if not derivative:
        g = np.where(Z>0, Z, 0.01*Z)
    else:
        g = np.where(Z>0, 1, 0.01)
    return g

@activation
def sigmoid(Z, derivative):
    if not derivative:
        g = 1 / (1 + np.exp(-Z))
    else:
        g = np.exp(Z) / (1 + np.exp(Z))**2
    return g

@activation
def tanh(Z, derivative):
    if not derivative:
        g = np.tanh(Z)
    else:
        g = 4 / (np.exp(Z) + np.exp(-Z))**2
    return g

def initialize_parameters(n):
    np.random.seed(seed)
    W = [None for i in range(layer)]
    b = [None for i in range(layer)]
    for i in range(1, layer):
        W_i = np.random.randn(n[i], n[i-1]) * 0.01
        b_i = np.zeros(shape=(n[i], 1))
        assert W_i.shape == (n[i], n[i-1])
        assert b_i.shape == (n[i], 1)
        W[i] = W_i
        b[i] = b_i
    parameters ={
        'W': W,
        'b': b,
        'g': tuple(map(eval, g)),
        }
    return parameters

def forward_propagation(X, parameters, datasets = True):
    W = parameters['W']
    b = parameters['b']
    g = parameters['g']
    A = [None for i in range(layer)]
    Z = [None for i in range(layer)]
    A[0] = X
    
    for i in range(1, layer):
        Z_i = np.dot(W[i], A[i-1]) + b[i]
        A_i = g[i](Z_i)
        if datasets:
            assert A_i.shape == (n[i], m)
        #else:
        #    assert A_i.shape == (n[i], 1)
        A[i] = A_i
        Z[i] = Z_i
    cache = {
        'Z': Z,
        'A': A,
        }
    return (A_i, cache)

def compute_cost(Y_, Y, parameters):
    cost = - np.sum(logistic(Y, Y_)) / m # (n, m) -> (1)
    cost = float(np.squeeze(cost))
    assert(isinstance(cost,float))
    return cost

def backward_propagation(parameters, cache, Y):
    dW = [None for i in range(layer)]
    db = [None for i in range(layer)]
    dA = [None for i in range(layer)]
    dZ = [None for i in range(layer)]

    W = parameters['W']
    b = parameters['b']
    A = cache['A']
    Z = cache['Z']

    g = parameters['g']

    Y_ = A[-1]
    dA[-1] = logistic(Y, Y_, True)


    for i in range(layer-1, 0, -1):
        dZ[i] = dA[i] * g[i](Z[i], True)
        dW[i] = np.dot(dZ[i], A[i-1].T) / m
        assert dW[i].shape == W[i].shape
        db[i] = np.sum(dZ[i], axis=1, keepdims=True) / m
        dA[i-1] = np.dot(W[i].T, dZ[i])
    grads = {
        'dW': dW,
        'db': db,
        }
    return grads

def update_parameters(parameters, grads, learning_rate=1.2):
    W = parameters['W']
    b = parameters['b']
    dW = grads['dW']
    db = grads['db']
    for i in range(1, layer):
        W[i] -= learning_rate * dW[i]
        b[i] -= learning_rate * db[i]
    return parameters

def predict(parameters, X):
    Y_ , cache = forward_propagation(X, parameters, False)
    predictions = np.round(Y_)

    return predictions

parameters = initialize_parameters(n)

start = time.time()
for i in range(num_iterations):
    Y_, cache = forward_propagation(X, parameters)
    cost = compute_cost(Y_, Y, parameters)
    grads = backward_propagation(parameters, cache, Y)
    update_parameters(parameters, grads, learning_rate)

    if (i+1) % 1000 == 0:
        print('第{}次循环，成本为：{}'.format(i+1, cost))

end = time.time()
predictions = predict(parameters, X)
print ('准确率: {}%，耗时{:.2f}s' .format(float((np.dot(Y, predictions.T) + np.dot(1 - Y, 1 - predictions.T)) / float(Y.size) * 100), end - start))

input('Successful')
