import matplotlib.pyplot as plt

observations = range(1, 10)
delays = [4, 10, 12, 55, 22, 15, 8, 7, 9]
mean = sum(delays) / len(delays)


plt.plot(observations, delays, marker="o")
plt.title("Professor B's Delays")
plt.axhline(y=mean, color='r', linestyle='--', label=f"Mean = {mean}")
plt.xlabel("Observation")
plt.ylabel("Delay")
plt.grid(True)

plt.savefig("delays.png")
plt.show()