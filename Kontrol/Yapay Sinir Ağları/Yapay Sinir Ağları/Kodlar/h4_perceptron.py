import math
import matplotlib.pyplot as plt
import numpy as np

class perceptron:
    def __init__(self, inputNodes, outputNodes, learningRate):
        self.inodes = inputNodes        
        self.onodes = outputNodes
        self.lr = learningRate    
        self.wio = np.random.uniform(size=self.inodes * self.onodes, low=0, high=1).reshape(self.inodes, self.onodes)
        
    def activation_func(self, x):
        x[x <= 1] = 0
        x[x > 1] = 1        
        return x

     # quaery the NN
    def query(self, input_list):
        # convert input list to 2d array
        inputs = np.array(input_list, ndmin=2).T

        # calculate signals into input layer
        final_inputs = np.dot(np.transpose(inputs),self.wio) 
        final_outputs = self.activation_func(final_inputs)
        return final_outputs
    
    # train the NN
    def train(self, input_list, target_list):        
       
        inputs = np.array(input_list, ndmin=2).T
        target = np.array(target_list, ndmin=2)

        # calculate signals into input layer
        final_inputs = np.dot(np.transpose(inputs),self.wio) 
        final_outputs = self.activation_func(final_inputs)

        # error is the (target - actual)
        output_errors = target - final_outputs

        if output_errors != 0:
            
            if output_errors > 0:
                # update the weights for the links between the hidden and output layer
                self.wio += self.lr * inputs
            else:
                # update the weights for the links between the hidden and output layer
                self.wio -= self.lr * inputs

    def print_weight(self):
        return print("Wio: ", self.wio)
             
input_nodes = 2
output_nodes = 1
learning_rate = 0.1

inp_val = np.array([[1, 1],[-1, 0],[-1, 2]])
out_val = np.array([[0],[1],[1]])

# create instance of NN
n = perceptron(input_nodes, output_nodes, learning_rate)

print(n.query(inp_val))
n.print_weight()

# train the neural network
# epochs is the number of times the training data set is used for training
epochs = 50
t = 0

for e in range(epochs):
    for x in inp_val:
        inputs = x
        target = out_val[t]
        n.train(inputs, target)
        
        t += 1
        if t > len(out_val)-1:
            t=0
    
#print(n.query([0.0, 0.0]))
print("--------------------------")
print(n.query(inp_val))
n.print_weight()