import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt
import h5py
import os


class NN():
    def __init__(self, X, Y, keep_prob=None, GPU=True):
        self.A = []
        self.A.append(X)
        self.Y = Y
        self.keep_prob = keep_prob
        if not GPU:
            os.environ["CUDA_VISIBLE_DEVICES"]="-1"

    def add_layer(self, out_size, activation_function=lambda x: x):
        assert len(self.A[-1].shape) == 2
        in_size = int(self.A[-1].shape[-1])
        W = tf.Variable(tf.random_normal([in_size, out_size]))
        b = tf.Variable(tf.random_normal([1, out_size]) + 0.1)
        Wx_plus_b = tf.matmul(self.A[-1], W) + b
        if self.keep_prob is not None:
            Wx_plus_b = tf.nn.dropout(Wx_plus_b, self.keep_prob)
        self.A.append(activation_function(Wx_plus_b))
        return self

    def conv2d(self, filter_size, num_filter, stride, padding='SAME', activation_function=lambda x: x):
        assert len(self.A[-1].shape) == 4
        num_input_channels = int(self.A[-1].shape[-1])
        W = tf.Variable(tf.truncated_normal(shape=[filter_size, filter_size, num_input_channels, num_filter], stddev=0.1))
        tf.nn.conv2d(self.A[-1], W, strides=[1,stride,stride,1], padding=padding)
        self.A.append(activation_function(tf.nn.conv2d(self.A[-1], W, strides=[1,stride,stride,1], padding=padding)))
        return self

    def max_pool(self, filter_size, stride, padding='SAME'):
        self.A[-1] = tf.nn.max_pool(self.A[-1], ksize=[1,filter_size,filter_size,1], strides=[1,stride,stride,1], padding=padding)
        return self

    def fully_connected(self, out_size, activation_function=None):
        self.A.append(tf.contrib.layers.fully_connected(self.A[-1], out_size, activation_fn=activation_function))

    def flatten(self):
        self.A[-1] = tf.contrib.layers.flatten(self.A[-1])
        return self

    @property
    def Y_(self):
        Y_ = self.A[-1]
        assert len(Y_.shape) == 2
        assert int(Y_.shape[-1]) == int(self.Y.shape[-1])
        return Y_

    def init(self, sess):
        init = tf.global_variables_initializer()
        sess.run(init)

    def set_train_step(self, optimizer, learning_rate, cost):
        self.optimizer = optimizer
        self.learning_rate = learning_rate
        self.cost = cost
        self.train_step = optimizer(learning_rate).minimize(cost)

    def train(self, sess, data_set, placeholder_vars,
            keep_prob=0.6, num_epochs=100, minibatch_size=64, print_step=50, is_plot=True, accuracy=None):
        X, Y, keep_prob_var = placeholder_vars
        costs = []
        for i in range(num_epochs):
            if minibatch_size:
                cost = 0
                for X_mini_batch, Y_mini_batch in data_set.random_mini_batches():
                    sess.run(self.train_step, feed_dict={X: X_mini_batch, Y: Y_mini_batch, keep_prob_var: keep_prob})
                    temp_cost = sess.run(self.cost, feed_dict={X: X_mini_batch, Y: Y_mini_batch, keep_prob_var: 1})
                    cost += temp_cost / (data_set.train_size // minibatch_size)
            else:
                sess.run(self.train_step, feed_dict={X: data_set.train_set[0], Y: data_set.train_set[1], keep_prob_var: keep_prob})
                cost = sess.run(self.cost, feed_dict={X: data_set.train_set[0], Y: data_set.train_set[1], keep_prob_var: 1})
            costs.append(cost)

            if i % print_step == 0:
                train_accuracy = accuracy.eval({X: data_set.train_set[0], Y: data_set.train_set[1], keep_prob_var: 1})
                dev_accuracy = accuracy.eval({X: data_set.dev_set[0], Y: data_set.dev_set[1], keep_prob_var: 1})
                if data_set.test_size:
                    test_accuracy = accuracy.eval({X: data_set.test_set[0], Y: data_set.test_set[1], keep_prob_var: 1})
                    print('cost {:.5f}, train accuracy {:.5%}, dev accuracy {:.5%}, test accuracy {:.5%}'.format(cost, train_accuracy, dev_accuracy, test_accuracy))
                else:
                    print('cost {:.5f}, train accuracy {:.5%}, dev accuracy {:.5%}'.format(cost, train_accuracy, dev_accuracy))
        if is_plot:
            self.plot_costs(costs)

    def plot_costs(self, costs):
        plt.plot(np.squeeze(costs))
        plt.ylabel('Cost')
        plt.xlabel('iterations (per tens)')
        plt.title('Learning rate = ' + str(self.learning_rate))
        plt.show()

class DataSet():

    def __init__(self, X_shape, Y_shape):
        self.X_shape = tuple(X_shape)
        self.Y_shape = tuple(Y_shape)
        self.m = 0
        self.data_set = None
        self.train_set = None
        self.dev_set = None
        self.test_set = None

    def load_by_h5(self, h5_path):
        h5f = h5py.File(h5_path, 'r')
        self.train_set = (h5f.get('X_train_set')[: ], h5f.get('Y_train_set')[: ])
        self.dev_set = (h5f.get('X_dev_set')[: ], h5f.get('Y_dev_set')[: ])
        self.test_set = (h5f.get('X_test_set')[: ], h5f.get('Y_test_set')[: ])
        h5f.close()

    def add_data_from_h5(self, h5_path):
        h5f = h5py.File(h5_path, 'r')
        self.add_data(h5f['X'], h5f['Y'])
        h5f.close()

    def add_data(self, X, Y):
        assert X[0].shape == self.X_shape
        assert Y[0].shape == self.Y_shape
        assert X.shape[0] == Y.shape[0]
        origin_m = self.m
        block_m = X.shape[0]
        origin_data_set = self.data_set
        self.m += block_m
        self.data_set = (np.zeros(shape=(self.m, *self.X_shape)), np.zeros(shape=(self.m, *self.Y_shape)))
        if origin_data_set is not None:
            self.data_set[0][: origin_m], self.data_set[1][: origin_m] = origin_data_set[0][: ], origin_data_set[1][: ]
        self.data_set[0][origin_m: ], self.data_set[1][origin_m: ] = X[: ], Y[: ]

    def save(self, h5_path):
        h5f = h5py.File(h5_path, 'w')
        if self.train_set:
            h5f['X_train_set'], h5f['Y_train_set'] = self.train_set
        if self.dev_set:
            h5f['X_dev_set'], h5f['Y_dev_set'] = self.dev_set
        if self.test_set:
            h5f['X_test_set'], h5f['Y_test_set'] = self.test_set
        h5f.close()

    def random_divide(self, proportion=(0.95, 0.025)):
        assert sum(proportion) <= 1
        indexes = list(np.random.permutation(self.m))
        # allocate indexes
        train_size = round(proportion[0] * self.m)
        dev_size = round(proportion[1] * self.m)
        test_size = self.m - train_size - dev_size
        self.train_size, self.dev_size, self.test_size = train_size, dev_size, test_size
        train_indexes = indexes[: train_size]
        dev_indexes = indexes[train_size: train_size+dev_size]
        test_indexes = indexes[train_size+dev_size: ]
        # 按照 size 初始化
        self.train_set = (np.zeros(shape=(train_size, *self.X_shape)), np.zeros(shape=(train_size, *self.Y_shape)))
        self.dev_set = (np.zeros(shape=(dev_size, *self.X_shape)), np.zeros(shape=(dev_size, *self.Y_shape)))
        if test_size:
            self.test_set = (np.zeros(shape=(test_size, *self.X_shape)), np.zeros(shape=(test_size, *self.Y_shape)))
        # update data
        self.train_set = self.data_set[0][train_indexes], self.data_set[1][train_indexes]
        self.dev_set = self.data_set[0][dev_indexes], self.data_set[1][dev_indexes]
        if test_size:
            self.test_set = self.data_set[0][test_indexes], self.data_set[1][test_indexes]

    def random_mini_batches(self, mini_batch_size = 64, seed = 0):
        np.random.seed(seed)
        train_size = self.train_size
        permutation = list(np.random.permutation(train_size))
        batch_permutation_indexes = [permutation[i: i + mini_batch_size] for i in range(0, train_size, mini_batch_size)]
        for batch_permutation in batch_permutation_indexes:
            mini_batch_X = self.train_set[0][batch_permutation]
            mini_batch_Y = self.train_set[1][batch_permutation]
            yield mini_batch_X, mini_batch_Y

if __name__ == '__main__':
    ## baidu_image 数据集
    # data_set = DataSet((64, 64, 1), (5, ))
    # data_set.add_data_from_h5('data/baidu_image/猫.h5')
    # data_set.add_data_from_h5('data/baidu_image/狗.h5')
    # data_set.add_data_from_h5('data/baidu_image/牛.h5')
    # data_set.add_data_from_h5('data/baidu_image/羊.h5')
    # data_set.add_data_from_h5('data/baidu_image/鸡.h5')
    # data_set.add_data_from_h5('data/baidu_image/鹅.h5')
    # data_set.random_divide()

    ## [MINST 数据集](https://tensorflow.googlesource.com/tensorflow/+/master/tensorflow/examples/tutorials/mnist/input_data.py)
    # mnist = input_data.read_data_sets("data/MNIST_data/", one_hot=True)
    # data_set = DataSet((28, 28, 1), (10, ))
    # data_set.add_data(np.reshape(mnist.train.images, [-1, 28, 28, 1]), mnist.train.labels)
    # data_set.add_data(np.reshape(mnist.test.images, [-1, 28, 28, 1]), mnist.test.labels)
    # data_set.random_divide()

    ## 吴恩达课后作业，手势识别数据集
    h5f_train = h5py.File('data/datasets/train_signs.h5', "r")
    h5f_test = h5py.File('data/datasets/test_signs.h5', "r")
    data_set = DataSet((64, 64, 3), (6, ))
    X_data = np.array(h5f_train["train_set_x"][:]) / 255
    Y_data = np.array(h5f_train["train_set_y"][:])
    Y_data = Y_data.reshape((1, Y_data.shape[0]))
    Y_data = np.eye(6)[Y_data.reshape(-1)]
    data_set.add_data(X_data, Y_data)
    X_data = np.array(h5f_test["test_set_x"][:]) / 255
    Y_data = np.array(h5f_test["test_set_y"][:])
    Y_data = Y_data.reshape((1, Y_data.shape[0]))
    Y_data = np.eye(6)[Y_data.reshape(-1)]
    data_set.add_data(X_data, Y_data)
    data_set.random_divide(proportion=(0.7, 0.15))
    h5f_train.close()
    h5f_test.close()

    print(data_set.train_size, data_set.dev_size, data_set.test_size)

    # for i in range(data_set.train_size):
    #     # print(data_set.train_set[0][i])
    #     print(data_set.train_set[1][i])
    #     # plt.imshow(np.reshape(data_set.train_set[0][i], (64, 64)), cmap='gray')
    #     plt.imshow(data_set.train_set[0][i])
    #     plt.show()

    X = tf.placeholder(dtype=tf.float32, shape=[None, 64, 64, 3])
    Y = tf.placeholder(dtype=tf.float32, shape=[None, 6])
    keep_prob = tf.placeholder(dtype=tf.float32)

    nn = NN(X, Y, keep_prob)
    nn.conv2d(4, 8, 1, 'SAME', tf.nn.relu).max_pool(8, 8)\
        .conv2d(2, 16, 1, 'SAME', tf.nn.relu).max_pool(4, 4).flatten()\
        .fully_connected(6)
        # .add_layer(6)


    Y_ = nn.Y_

    cost = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits_v2(logits=Y_, labels=Y))
    nn.set_train_step(tf.train.AdamOptimizer, 0.0001, cost)

    with tf.Session() as sess:
        nn.init(sess)

        corrent_prediction = tf.equal(tf.argmax(Y_, 1) , tf.argmax(Y, 1))
        accuracy = tf.reduce_mean(tf.cast(corrent_prediction, tf.float32))

        nn.train(sess, data_set, placeholder_vars=(X, Y, keep_prob), num_epochs=1000, minibatch_size=64, print_step=5, accuracy=accuracy)
