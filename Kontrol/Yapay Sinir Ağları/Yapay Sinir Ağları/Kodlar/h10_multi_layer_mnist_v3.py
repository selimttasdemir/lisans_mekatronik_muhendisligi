# tis code is develop of v3 
import math
import matplotlib.pyplot as plt
import numpy as np
from sklearn.metrics import confusion_matrix
import csv

# neural network class definition
class neuralNetwork:   

    # initialise the neural network
    def __init__(self, inputNodes, hiddenNodes, outputNodes, learningRate):
        # set number of nodes in each input, hidden, output layer
        self.inodes = inputNodes
        self.hnodes = hiddenNodes
        self.onodes = outputNodes
               
        self.akj = np.random.uniform(size=self.inodes * self.hnodes, low=-1, high=1).reshape(self.hnodes, self.inodes)
        self.ajm = np.random.uniform(size=self.hnodes * self.onodes, low=-1, high=1).reshape(self.hnodes,self.onodes)        

        self.bj = np.random.uniform(size=self.hnodes, low=-1, high=1).reshape(self.hnodes, 1)
        self.bm = np.random.uniform(size=self.onodes, low=-1, high=1).reshape(self.onodes, 1)
        
        # learning rate 
        self.lr = learningRate

        self.actual_list = np.array([])
        self.predict_list = np.array([])

    # activation function is sigmoid
    def activation_func(self, x):
        return 1 / (1 + np.exp(-x))

    # train the NN
    def train(self, input_list, target_list):
        # convert input list to 2d array
        inputs = np.array(input_list, ndmin=2).T
        B_ç = np.array(target_list, ndmin=2).T

        # calculate signals into hidden layer
        Net_j = np.dot(self.akj, inputs) + self.bj
        Ç_j = self.activation_func(Net_j)

        # calculate signals into output layer
        Net_m = np.transpose(np.dot(np.transpose(Ç_j),self.ajm)) + self.bm
        Ç_m = self.activation_func(Net_m)

        ### backpropagation ###
        E_m = B_ç - Ç_m

        delta_m = Ç_m * (1 - Ç_m) * E_m
        hidden_error = np.dot(self.ajm, delta_m)

        delta_Ajm = np.dot(Ç_j, self.lr * np.transpose(delta_m))  
        self.ajm += delta_Ajm

        delta_Bm = self.lr * delta_m
        self.bm += delta_Bm

        delta_j = Ç_j * (1 - Ç_j) * hidden_error 

        delta_Akj = np.dot(self.lr * delta_j, np.transpose(inputs))
        self.akj += delta_Akj

        delta_Bj = self.lr * delta_j
        self.bj += delta_Bj

    def query(self, input_list):
        # convert input list to 2d array
        inputs = np.array(input_list, ndmin=2).T

        # calculate signals into hidden layer
        Net_j = np.dot(self.akj, inputs) + self.bj
        Ç_j = self.activation_func(Net_j)

        # calculate signals into output layer
        Net_m = np.transpose(np.dot(np.transpose(Ç_j),self.ajm)) + self.bm
        Ç_m = self.activation_func(Net_m)

        return Ç_m

    def print_weight(self):
        print("akj:", self.akj)
        print("ajm:", self.ajm)
        print("bj:", self.bj)
        print("bm:", self.bm)


# initialise NN parameters
input_nodes = 784
hidden_nodes = 198
output_nodes = 10

learning_rate = 0.184

# create instance of NN
n = neuralNetwork(input_nodes, hidden_nodes, output_nodes, learning_rate)

# load the mnist training data CSV file into a list
training_data_file = open("data/mnist_train_100.csv", 'r')
training_data_list = training_data_file.readlines()
training_data_file.close()

# train the neural network
# epochs is the number of times the training data set is used for training
epochs = 100

for e in range(epochs):
    # go through all records in the training data set
    for record in training_data_list:
        # split the record by the ',' commas
        all_values = record.split(',')
        # scale and shift the inputs
        inputs = (np.asfarray(all_values[1:]) / 255.0 * 0.99) + 0.01
        # create the target output values (all 0.01, except the desired label which is 0.99)
        B_ç = np.zeros(output_nodes) + 0.01
        # all_values[0] is the target label for this record
        B_ç[int(all_values[0])] = 0.99
        n.train(inputs, B_ç)
        


# test NN
test_data_file = open("data/mnist_test_10_v2.csv", 'r')
test_data_list = test_data_file.readlines()
test_data_file.close()
count = 0

for record in test_data_list:
    #split the record by the ',' commas
    all_values = record.split(',')
    # scale and shift the inputs
    inputs = (np.asfarray(all_values[1:]) / 255.0 * 0.99) + 0.01
    # create the target output values (all 0.01, except the desired label which is 0.99)
    B_ç = np.zeros(output_nodes) + 0.01
    # all_values[0] is the target label for this record
    B_ç[int(all_values[0])] = 0.99
    result = n.query(inputs)
    n.predict_list = np.append(n.predict_list, np.argmax(result))
    n.actual_list = np.append(n.actual_list, int(all_values[0]))

    print("Cikti: %d, Beklenen: %d " % (np.argmax(result), int(all_values[0])))

    if np.argmax(result) == int(all_values[0]):
        count += 1    
    

print("Basari: %f" % (count / len(test_data_list)))


# created by ChatGPT
def plot_confusion_matrix(y_true, y_pred, classes,
                          normalize=False,
                          title=None,
                          cmap=plt.cm.Blues):
    """
    This function prints and plots the confusion matrix.
    Normalization can be applied by setting `normalize=True`.
    """
    if not title:
        if normalize:
            title = 'Normalized confusion matrix'
        else:
            title = 'Confusion matrix, without normalization'

    # Compute confusion matrix
    cm = confusion_matrix(y_true, y_pred)
    # Only use the labels that appear in the data
    if normalize:
        cm = cm.astype('float') / cm.sum(axis=1)[:, np.newaxis]
        print("Normalized confusion matrix")
    else:
        print('Confusion matrix, without normalization')

    print(cm)

    fig, ax = plt.subplots()
    im = ax.imshow(cm, interpolation='nearest', cmap=cmap)
    ax.figure.colorbar(im, ax=ax)
    # We want to show all ticks...
    ax.set(xticks=np.arange(cm.shape[1]),
           yticks=np.arange(cm.shape[0]),
           # ... and label them with the respective list entries
           xticklabels=classes, yticklabels=classes,
           title=title,
           ylabel='True label',
           xlabel='Predicted label')

    # Rotate the tick labels and set their alignment.
    plt.setp(ax.get_xticklabels(), rotation=45, ha="right",
             rotation_mode="anchor")

    # Loop over data dimensions and create text annotations.
    fmt = '.2f' if normalize else 'd'
    thresh = cm.max() / 2.
    for i in range(cm.shape[0]):
        for j in range(cm.shape[1]):
            ax.text(j, i, format(cm[i, j], fmt),
                    ha="center", va="center",
                    color="white" if cm[i, j] > thresh else "black")
    fig.tight_layout()
    return fig, ax

# Example usage
y_true = n.actual_list
y_pred = n.predict_list

plot_confusion_matrix(y_true, y_pred, classes=[0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
plt.show()
    

# CSV dosyası oluşturun ve verileri yazın
with open('weight_bias_value.csv', 'w', newline='') as f:
    # Verileri sırayla dosyaya yazın
    writer = csv.writer(f)
    writer.writerow(['akj:'])
    np.savetxt(f, n.akj, delimiter=',')
    writer.writerow(['ajm:'])
    np.savetxt(f, n.ajm, delimiter=',')
    writer.writerow(['bj:'])
    np.savetxt(f, n.bj, delimiter=',')
    writer.writerow(['bm:'])
    np.savetxt(f, n.bm, delimiter=',')

#take the data from a record, rearrange it into a 28*28 array and plot it as an image
# all_values = test_data_list[0].split(',')
# image_array = np.asfarray(all_values[1:]).reshape((28,28))
# plt.imshow(image_array, cmap='Greys', interpolation='None')
# plt.show()