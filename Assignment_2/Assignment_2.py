import math
import matplotlib.pyplot as plt

def function(x) :
    return 300*x / (1 + math.exp(x))

def plot_function():
    x_values = [x * 0.01 for x in range(0, 1000)]
    y_values = [function(x) for x in x_values]
    plt.plot(x_values, y_values)
    plt.xlabel('x')
    plt.ylabel('function(x)')
    plt.title('Plot of function(x)')
    plt.show()
    
def integrate_function_trapezoidal(a, b, n):
    dx = (b - a) / n
    total = 0
    for i in range(n):
        total += (function(a + i * dx) + function(a + (i + 1) * dx)) / 2 * dx
    return total

if __name__ == "__main__":
    plot_function()
    a = 0.0
    b = 10.0
    n = range(2, 65)
    integral_results = [] 
    for num_intervals in n:
        integral = integrate_function_trapezoidal(a, b, num_intervals)
        integral_results.append(integral)
    
    # Plot the integral results
    plt.plot(n, integral_results, marker='o')
    plt.xlabel('Number of intervals')
    plt.ylabel('Integral value')
    plt.axhline(y=integrate_function_trapezoidal(a, b, 1000), color='r', linestyle='--')
    plt.title('Integral of function using trapezoidal rule')
    plt.show()
    
    # Plot the fit of hte errors usign a logarithm
    errors = [abs(integral - integrate_function_trapezoidal(a, b, 1000)) for integral in integral_results]
    plt.plot(n, errors, marker='o')
    plt.xlabel('Number of intervals')
    plt.ylabel('Absolute error')
    plt.yscale('log')
    plt.title('Error of trapezoidal integration')
    plt.show()
