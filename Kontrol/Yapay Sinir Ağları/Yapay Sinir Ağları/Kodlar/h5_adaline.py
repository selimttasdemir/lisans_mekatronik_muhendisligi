import numpy as np
import matplotlib.pyplot as plt

class perceptron:
    def __init__(self, input_nodes, output_nodes,lR):
        self.inodes = input_nodes
        self.onodes = output_nodes
        self.lRate = lR             
        self.wi0 = np.random.uniform(size=self.inodes * self.onodes, low=0, high=1).reshape(self.inodes,self.onodes)
        self.bio = np.random.uniform(size=self.onodes, low=0, high=1).reshape(self.onodes,self.onodes)
        
    def activation_func(self,x):
        x [x <= 1] = 0
        x [x > 1] = 1        
        return x
    
    def query(self, input_list):
        input = np.array(input_list, ndmin=2).T
        final_input = np.dot(np.transpose(input), self.wi0) + self.bio
        final_output = self.activation_func(final_input)
        return final_output
    
    def train(self, input_list, output_list):
        input = np.array(input_list, ndmin=2).T
        target = np.array(output_list, ndmin=2)

        final_input = np.dot(np.transpose(input), self.wi0) + self.bio
        final_output = self.activation_func(final_input)

        output_error = target - final_output
       
        self.wi0 += self.lRate * output_error * input
        self.bio += self.lRate * output_error 
            

    def print_weight(self):
        return print("wio:",self.wi0, "bio:", self.bio)
    
    def plot_error(self):        
        plt.figure()
        plt.xlabel("Epochs")
        plt.ylabel("Fonksiyon Çıktıları")
        plt.grid(True)        
        plt.plot(self.error_list,label="Error", color='C0', lw=3)      
        plt.legend()
        plt.show()

input_nodes = 2
output_nodes = 1
learningRate = 0.1

inp_val = np.array([[1,1],[-1,0],[-1,2]])
out_val = np.array([[0],[1],[1]])

n = perceptron(input_nodes, output_nodes, learningRate)
print(n.query(inp_val))
n.print_weight()

epochs = 50
t = 0

for e in range(epochs):
    for x in inp_val:
        input = x
        target = out_val[t]
        n.train(input,target)

        t += 1
        if t > len(out_val)-1:
            t=0

print(n.query(inp_val))
n.print_weight()