import os
import time
import argparse

import matplotlib.pyplot as plt

# local C extension
from _python_interface import ffi, lib

temperatures = [50] * 12


@ffi.def_extern()
def temperatur_messung(ptc_id):
    return int(temperatures[ptc_id])


class Diagram:

    def __init__(self, lib):
        self.values = [0,1,0,1,0,1,0,1,0,1,0]
        self.outputs = ("UP 1", "UP 2", "UP 3", "UP 4", "ZV 5", "UP 6", "UP 7", "UP 8", "Brenner", "UP 10", "ZV 10")
        self.fig = plt.figure()
        self.ax = self.fig.add_subplot(411)
        self.fs = []
        self.lib = lib

        self.draw()

        for t in range(12):
            axF = plt.axes([0.15, 0.05 + (t * 0.05), 0.65, 0.03])
            f = plt.Slider(axF, 'F{}'.format(t+1), 0.0, 120.0, valinit=50)
            f.on_changed(self.update_factory(t))
            self.fs.append(f)  # prevent f from being garbage collected (really? WTF?)
        plt.show()

    def draw(self):
        x_pos = range(len(self.outputs))
        self.ax.bar(x_pos, self.values, align = "center")
        self.ax.set_xticks(x_pos)
        self.ax.set_xticklabels(self.outputs)
        self.ax.set_ylabel('Digital Out')
        self.ax.set_title('Heizung Eggerding')

    def update_factory(self, sensor_index):
        def update(value):
            global temperatures
            temperatures[sensor_index] = value
            self.lib.loop()
            digital_outs = self.lib.get_outputs()
            for i in range(11):
                self.values[i] = digital_outs[i]
            self.ax.clear()
            self.draw()
        return update


def main():

    parser = argparse.ArgumentParser()
    parser.add_argument('-i', '--interactive', action='store_true',
                        help='run matplotlib interactive test environment')

    args = parser.parse_args()

    if args.interactive:
        lib.setup()
        lib.loop()
        Diagram(lib)
    else:
        pass


if __name__ == "__main__":
    main()
