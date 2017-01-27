"""
Simple demo of a horizontal bar chart.
"""
import matplotlib.pyplot as plt
plt.rcdefaults()
import matplotlib.pyplot as plt


def updateF1(val):
    values = [int(val),4,5,4,3,4,5,6,1,2,3]
    ax.clear()
    ax.bar(x_pos, values, align = "center")

plt.rcdefaults()
fig, ax = plt.subplots()

# Example data
outputs = ("UP 1", "UP 2", "UP 3", "UP 4", "ZV 5", "UP 6", "UP 7", "UP 8", "Brenner", "UP 10", "ZV 10")
values = [3,4,5,4,3,4,5,6,1,2,3]

x_pos = range(len(outputs))
ax.bar(x_pos, values, align = "center")
ax.set_xticks(x_pos)
ax.set_xticklabels(outputs)

ax.set_ylabel('Digital Out')
ax.set_title('Heizung Eggerding')

axF1 = plt.axes([0.15, 0.1, 0.65, 0.03])

F1 = plt.Slider(axF1, 'F1', 0.0, 120.0, valinit=50)
F1.on_changed(updateF1)

plt.show()
