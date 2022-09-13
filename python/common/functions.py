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