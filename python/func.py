from distutils.log import error
from turtle import forward
import numpy as np

def softmax(x):
    if x.ndim == 1:
        x = x - np.max(x)
        x /= np.sum(np.exp(x))
    if x.ndim == 2:
        x = x - np.max(x, axis=1, keepdims=True)
        x = np.exp(x)
        x /= np.sum(x, axis=1, keepdims=True)
        
        return x

def cross_entropy_error(y, t):
    # 不传入批次数据也可以处理
    # 相当于加了0轴
    if y.ndim == 1:
        y.reshape(1, y.size)
        t.reshape(1, t.size)

    if t.size == y.size:
        t = np.argmax(t, axis=1)
    
    batch_size = y.shape[0]
    return -np.sum(np.log(y[np.arange(batch_size),t] + 1e-7)) / batch_size

class sigmoid:
    def __init__(self) -> None:
        self.params, self.grads = [], []
        self.out = None

    def forward(self, x):
        out = 1/(1 + np.exp(-x))
        self.out = out
        return out
    
    def backward(self, dout):
        dx = dout * self.out*(1 - self.out)
        return dx

class Affine:
    def __init__(self, W, b) -> None:
        self.params = [W, b]
        self.grads = [np.zeros_like(W), np.zeros_like(b)]
        self.x = None
    
    def forward(self, x):
        # b.shape = (k, )
        W, b = self.params
        out = np.dot(x, W) + b
        self.x = x
        return out

    def backward(self, dout):
        W, b = self.params
        dx = np.dot(dout, W.T)
        dW = np.dot(self.x.T, dout)
        db = np.sum(dout, axis=0)

        self.grads[0][...] = dW
        self.grads[1][...] = db
        return dx

class SoftmaxWithLoss:
    def __init__(self) -> None:
        self.params, self.grads= [], []
        self.y = None
        self.t = None

    def forward(self, x, t):
        self.y = softmax(x)
        self.t = t

        if self.y.size == self.t.size:
            self.t = np.argmax(self.t, axis=1, keepdims=True)

        loss = cross_entropy_error(self.y, self.t)

        return loss
    
    def backward(self, dout=1):
        # 除以批大小，传递给前面的层的是单个数据的误差。
        batch_size = self.t.shape[0]

        dx = self.y.copy()
        dx[np.arange(batch_size), self.t] -= 1
        dx *= dout
        dx = dx / batch_size

        return dx

class TwoLayerNet:
    def __init__(self, input_size, hidden_size, output_size) -> None:
        I, H, O  = input_size, hidden_size, output_size
        # 初始化权重和偏置
        W1 = np.random.randn(I, H)
        b1 = np.zeros(H)
        W2 = np.random.randn(H, O)
        b2 = np.zeros(O)

        self.layers = [Affine(W1, b1), sigmoid(), Affine(W2, b2)]
        self.loss_layer = SoftmaxWithLoss()

        self.params, self.grads  = [], []
        for layer in self.layers:
            self.params += layer.params
            self.grads += layer.grads
        
    def forward(self, x, t):
        score = self.predict(x)
        loss = self.loss_layer.forward(score, t)

        return loss
    
    def backward(self, dout=1):
        dout = self.loss_layer.backward(dout)
        for layer in reversed(self.layers):
            dout = layer.backward(dout)
        
        return dout
    
    def predict(self, x):
        for layer in self.layers:
            x = layer.forward(x)
        return x
        





