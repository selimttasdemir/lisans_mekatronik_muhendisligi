import math
import matplotlib.pyplot as plt
import numpy as np

class neuron:        
    def __init__(self,inputNodes):
        self.inodes = inputNodes

    def activation_func(self, x):        
        return 1 / (1 + np.exp(-x))                

     # query the NN
    def query(self, input_list, weight_list):
        # convert input list to 2d array
        inputs = np.array(input_list, ndmin=2)

        # calculate signals into input layer
        final_inputs = np.dot(weight_list, np.transpose(inp_val)) 
        print("NET3= %f, NET=4 %f" % (final_inputs[0][0], final_inputs[1][0]))
        final_outputs = self.activation_func(final_inputs)
        return final_outputs    
                      
input_nodes = 2

inp_val = np.array([[0, 1]])
weight_val = np.array([[0.5, 0.1],[0.6, 0.9]])

# create instance of NN
n = neuron(input_nodes)

print(n.query(inp_val, weight_val))