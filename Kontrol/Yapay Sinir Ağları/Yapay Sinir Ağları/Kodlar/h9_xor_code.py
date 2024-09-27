import numpy as np
import matplotlib.pyplot as plt

class NeuralNetwork:
    def __init__(self, inputNodes, hiddenNodes, outputNodes, learningRate):

        self.inodes = inputNodes
        self.hnodes = hiddenNodes
        self.onodes = outputNodes

        self.akj = np.random.uniform(size = self.inodes*self.hnodes, low=-1, high=1).reshape(self.hnodes, self.inodes)
        self.ajm = np.random.uniform(size = self.onodes*self.hnodes, low=-1, high=1).reshape(self.hnodes, self.onodes)

        self.bj = np.random.uniform(size = self.hnodes, low=-1, high=1).reshape(self.hnodes, 1)
        self.bm = np.random.uniform(size = self.onodes, low=-1, high=1).reshape(self.onodes, 1)

        self.lr = learningRate
        self.error_list = np.array([])
        self.error_sum = 0
        self.count = 0
    
    def activation_func(self, x):
        return 1 / (1 + np.exp(-x))

    def print_weight(self):
        print("akj=", self.akj)
        print("ajm=", self.ajm)
        print("bj=", self.bj)
        print("bm=", self.bm)
    
    def ileri_dogru(self, input_list):
        Ç_k = np.array(input_list, ndmin=2).T

        Net_j = np.dot(self.akj, Ç_k) + self.bj
        Ç_j = self.activation_func(Net_j)

        Net_m = np.dot(np.transpose(Ç_j), self.ajm) + self.bm
        Ç_m = self.activation_func(Net_m)

        return Ç_m
    
    def egitim(self, input_list, target_list):
        Ç_k = np.array(input_list, ndmin=2).T
        B_ç = np.array(target_list, ndmin=1)

        Net_j = np.dot(self.akj, Ç_k) + self.bj
        Ç_j = self.activation_func(Net_j)

        Net_m = np.dot(np.transpose(Ç_j), self.ajm) + self.bm
        Ç_m = self.activation_func(Net_m)       

        E_m = B_ç - Ç_m

        self.error_sum += np.abs(E_m)

        delta_m = Ç_m * (1 - Ç_m) * E_m
        hidden_error = np.dot(self.ajm, delta_m)
        delta_Ajm = np.dot(Ç_j, self.lr * delta_m)

        self.ajm += delta_Ajm

        delta_Bm = self.lr * delta_m
        self.bm += delta_Bm
        
        delta_j = Ç_j * (1 - Ç_j) * hidden_error
        delta_Akj = np.dot(self.lr * delta_j, np.transpose(Ç_k))

        self.akj += delta_Akj

        delta_Bj = self.lr * delta_j
        self.bj += delta_Bj

        self.count += 1

        if (self.count > 3):
            self.error_sum = self.error_sum / 4
            self.error_list = np.append(self.error_list, self.error_sum)
            self.count = 0
            self.error_sum = 0     
        pass
    
    def plot_error(self):        
        plt.figure()
        plt.xlabel("İterasyon")
        plt.ylabel("Hatanın Değişimi")
        plt.grid(True)        
        plt.plot(self.error_list,label="Error", color='C0', lw=3)      
        plt.legend()
        plt.show()


# sinir ağının başlangıç parametreleri
input_node = 2
hidden_node = 2
output_node = 1

learning_rate = 0.8
input_val = np.array([[0.0,  0.0], [0.0, 1.0], [1.0, 0.0], [1.0, 1.0]])
out_val = np.array([[0.0], [1.0], [1.0], [0.0]])

n = NeuralNetwork(input_node, hidden_node, output_node, learning_rate)

# ileri doğru hesaplama
print(n.ileri_dogru(input_val))
n.print_weight()

#eğitimin başlatılması
epochs = 15000
t = 0

for e in range(epochs):
    for x in input_val:
        Ç_k = x
        target = out_val[t]
        n.egitim(Ç_k, target)

        t += 1

        if t > len(out_val)-1:
            t = 0

# eğitilmiş katsayıların test edilmesi
print(n.ileri_dogru(input_val))
n.print_weight()
n.plot_error()