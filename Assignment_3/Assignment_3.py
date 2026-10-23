import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from pathlib import Path

output_dir = Path(__file__).parent / "output"
bisection_path = output_dir / "output_bisection.dat"
secant_path = output_dir / "output_secant.dat"
newton_raphson_path = output_dir / "output_newton_raphson.dat"
simpsons_path = output_dir / "output_simpsons.dat"
fit_path = output_dir / "data1.dat"

columns = ["Iteration", "Root", "Error"]
data_bisection = pd.read_csv(bisection_path, sep=r"\s+", names=columns, header=0)
data_secant = pd.read_csv(secant_path, sep=r"\s+", names=columns, header=0)
data_newton_raphson = pd.read_csv(newton_raphson_path, sep=r"\s+", names=columns, header=0)
data_simpsons = pd.read_csv(simpsons_path, sep=r"\s+", names=["n", "Integral"], header=0)
data_fit = pd.read_csv(fit_path, sep=r"\s+", names=["x", "y"], header=0)

def f(x):
    return x**3 - 6*(x**2) - x + 10

def f_prime_centrally(f, x):
    h = 1e-6
    return (f(x + h) - f(x - h)) / (2 * h)

def f3(x):
    return -x**4 + 7*x**3 - 5*x**2 + 15

def plot_functions(f, a, b, title):
    x = np.linspace(a, b, 1000)
    y = [f(i) for i in x]
    plt.plot(x, y, label='f(x)')
    y_prime = [f_prime_centrally(f, i) for i in x]
    plt.axhline(0, color='black', linewidth=0.5)
    plt.plot(x, y_prime, label="f'(x)")
    plt.title(title)
    plt.legend()
    plt.show()


def plot_relative_errors(datasets):
    for data, method_name in datasets:
        errors = np.abs(data["Error"].to_numpy(dtype=float))
        plt.plot(data["Iteration"], errors / errors[0], marker="o", label=method_name)
    plt.title(r"Relative error $|\epsilon_n/\epsilon_0|$ vs iteration")
    plt.xlabel("Iteration n")
    plt.ylabel(r"$|\epsilon_n/\epsilon_0|$")
    plt.yscale("log")
    plt.grid(True, which="both", alpha=0.3)
    plt.legend()
    plt.show()

def plot_simpsons_relative_error(data):
    # plot the relative error of the Simpson's 1/3 rule integration
    data = data.copy()
    data = data.iloc[1:]
    absolute_integral = 461.2447702781641397
    data["Relative Error"] = abs(data["Integral"]-absolute_integral) / absolute_integral
    plt.plot(data["n"], data["Relative Error"], marker="o")
    plt.title("Integral of f3 using Simpson's 1/3 rule")
    plt.xlabel("n")
    plt.xscale("log")
    plt.ylabel("Relative Error")
    plt.yscale("log")
    plt.grid(True, which="both", alpha=0.3)
    plt.show()

def plot_least_squares_fit(data, slope, intercept):
    x = data["x"].to_numpy(dtype=float)
    y = data["y"].to_numpy(dtype=float)
    plt.scatter(x, y, label="Data points")
    plt.plot(x, slope * x + intercept, color="red", label=f"Fit: y = {slope}x + {intercept}")
    plt.title("Least Squares Fit")
    plt.xlabel("x")
    plt.ylabel("y")
    plt.legend()
    plt.show()

if __name__ == "__main__":
    plot_relative_errors([
        (data_bisection, "Bisection"),
        (data_secant, "Secant"),
        (data_newton_raphson, "Newton-Raphson"),
    ])
    plot_functions(f, -0.2, 6.2, "Function f and its derivative")
    data = [data_bisection, data_secant, data_newton_raphson]
    data_names = ["Bisection", "Secant", "Newton-Raphson"]
    plot_functions(f3, -2.2, 7.2, "Function f3 and its derivative")
    plot_simpsons_relative_error(data_simpsons)
    plot_least_squares_fit(data_fit, slope=0.0202415, intercept=0.514102)
