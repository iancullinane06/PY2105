import csv
from pathlib import Path

import matplotlib.pyplot as plt


output_directory = Path(__file__).parent / "output"
data_path = output_directory / "pi_convergence.csv"
plot_path = output_directory / "pi_precision.png"

with data_path.open(newline="") as data_file:
    rows = list(csv.DictReader(data_file))

sample_counts = [int(row["samples"]) for row in rows]
relative_errors = [float(row["relative_error_percent"]) for row in rows]
reference_errors = [
    relative_errors[0] * (sample_counts[0] / count) ** 0.5
    for count in sample_counts
]

plt.loglog(sample_counts, relative_errors, marker="o", label="Monte Carlo error")
plt.loglog(sample_counts, reference_errors, linestyle="--", label=r"$N^{-1/2}$ trend")
plt.xlabel("Number of random points, N")
plt.ylabel("Relative error (%)")
plt.title("Monte Carlo precision for the estimate of pi")
plt.grid(True, which="both")
plt.legend()
plt.tight_layout()
plt.savefig(plot_path, dpi=200)
