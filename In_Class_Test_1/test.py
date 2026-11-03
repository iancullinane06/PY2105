import matplotlib.pyplot as plt

def function(x) :
    y = (x**3) - (3*x**2) + 3
    return y


def plot_function() :
    x_values = [x * 0.01 for x in range(-501, 501)]
    y_values = [function(x) for x in x_values]
    plt.plot(x_values, y_values)
    plt.title("Problem 4) polynomial")
    plt.ylabel("Y")
    plt.xlabel("x")
    plt.show()


if __name__ == "__main__" :
    plot_function()