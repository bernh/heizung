import os

import matplotlib.pyplot as plt
plt.rcdefaults()
import matplotlib.pyplot as plt

# local C extension
from _python_interface import ffi, lib


@ffi.def_extern()
def temperatur_messung(ptc_id):
    return 10 * ptc_id



class Diagram:

    def __init__(self):
        self.values = [3,4,5,4,3,4,5,6,1,2,3]
        self.outputs = ("UP 1", "UP 2", "UP 3", "UP 4", "ZV 5", "UP 6", "UP 7", "UP 8", "Brenner", "UP 10", "ZV 10")
        self.fig, self.ax = plt.subplots()

        x_pos = range(len(self.outputs))
        self.ax.bar(x_pos, self.values, align = "center")
        self.ax.set_xticks(x_pos)
        self.ax.set_xticklabels(self.outputs)

        self.ax.set_ylabel('Digital Out')
        self.ax.set_title('Heizung Eggerding')

        axF1 = plt.axes([0.15, 0.1, 0.65, 0.03])
        F1 = plt.Slider(axF1, 'F1', 0.0, 120.0, valinit=50)
        F1.on_changed(self.updateFactory(3))

        plt.show()

    def updateFactory(self, sensor_index):
        def update(value):
            self.values[sensor_index] = value
            self.ax.clear()
            x_pos = range(len(self.outputs))
            self.ax.bar(x_pos, self.values, align = "center")
        return update


def main():
    lib.setup()
    lib.loop()
    temps = Diagram()


if __name__ == "__main__":
    main()
