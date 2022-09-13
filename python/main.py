from common import layers, optimizer, trainer
import numpy as np
from dataset import spiral
import matplotlib.pyplot as plt


# ❶ 设定超参数
max_epoch = 300
batch_size = 30
hidden_size = 15
learning_rate = 0.1

# ❷ 读入数据，生成模型和优化器
x, t = spiral.load_data()
model = layers.TwoLayerNet(input_size=2, hidden_size=hidden_size, output_size=3)
optimizer = optimizer.SGD(lr=learning_rate)
Trainer = trainer.Trainer(model, optimizer)
Trainer.fit(x, t, max_epoch, batch_size, 10)

# Trainer.plot_loss()

