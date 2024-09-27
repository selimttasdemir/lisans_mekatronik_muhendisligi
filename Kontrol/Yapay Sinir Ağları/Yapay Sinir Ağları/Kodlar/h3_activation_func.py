import math
import matplotlib.pyplot as plt
import numpy as np

def step(x):
    return np.array(x > 0, dtype=np.float32)

def sigmoid(x):
    return 1 / (1 + np.exp(-x))

def relu(x):
    return np.maximum(x,0)

def tanh(x):
    return np.tanh(x)

x = np.arange(-5.0, 5.0, 0.01)

step = step(x)
sigmoid = sigmoid(x)
relu = relu(x)
tanh = tanh(x)

plt.figure()
plt.xlabel("Girdiler")
plt.ylabel("Fonksiyon Çıktıları")
plt.grid(True)
plt.plot(x,step, label="Step", color='C0', lw=3)
plt.plot(x,sigmoid, label="Sigmoid", color='C1', lw=3)
plt.plot(x,relu, label="ReLU", color='C2', lw=3)
plt.plot(x,tanh, label="TanH", color='C3', lw=3)
plt.legend()
plt.show()