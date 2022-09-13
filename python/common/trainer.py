import numpy as np
from dataset import spiral
import matplotlib.pyplot as plt

class Trainer:
    def __init__(self, model, optimizer) -> None:
        self.model = model
        self.optimizer = optimizer
        self.loss_list = []

    def fit(self, x, t, max_epoch, batch_size, eval_interval, max_grad=None):

        model = self.model
        optimizer = self.optimizer

        # 学习用的变量
        data_size = len(x)
        max_iters = data_size // batch_size
        total_loss = 0
        loss_count = 0
        loss_list = []

        for epoch in range(max_epoch):
        # 打乱数据
            idx = np.random.permutation(data_size)
            x = x[idx]
            t = t[idx]
            for iters in range(max_iters):
                batch_x = x[iters*batch_size:(iters+1)*batch_size]
                batch_t = t[iters*batch_size:(iters+1)*batch_size]

                # 计算梯度，更新参数
                loss = model.forward(batch_x, batch_t)
                model.backward()
                optimizer.update(model.params, model.grads)
                total_loss += loss
                loss_count += 1

                # 定期输出学习过程
                if (iters+1) % eval_interval == 0:
                    avg_loss = total_loss / loss_count
                    print('| epoch %d | iter %d / %d | loss %.2f'
                    % (epoch + 1, iters + 1, max_iters, avg_loss))
                    loss_list.append(avg_loss)
                    total_loss, loss_count = 0, 0
        self.loss_list = loss_list


    def plot_loss(self):
        loss_list = self.loss_list

        # 绘制学习结果
        plt.plot(np.arange(len(loss_list)), loss_list, label='train')
        plt.xlabel('iterations (x10)')
        plt.ylabel('loss')
        plt.show()
