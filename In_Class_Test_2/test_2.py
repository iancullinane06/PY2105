import matplotlib.pyplot as plt
import numpy as np

def function(x) :
    return np.log(x + np.exp(x-1)) - np.sin(2*x)

def plot_functions(f, a, b):
    x = np.linspace(a, b, 1000)
    y = [f(i) for i in x]
    plt.plot(x, y, label='f(x)')
    plt.axhline(0, color='black', linewidth=0.5)
    plt.title("function plot")
    plt.legend()
    plt.savefig("function_plot.png")
    plt.show()
    
if __name__ == "__main__" :
    plot_functions(function, 0, 5)
