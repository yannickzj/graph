


import numpy as np
from matplotlib import pyplot as plt
from matplotlib.pylab import *
from matplotlib.backends.backend_agg import FigureCanvasAgg as FigureCanvas




def drawEdge(ax, label, connectionstyle):

    x1, y1 = 50, 50
    x2, y2 = 20, 20

    ax.plot([x1, x2], [y1, y2], ".")
    ax.annotate(label,
                xy=(x1, y1), xycoords='data',
                xytext=(x2, y2), textcoords='data',
                bbox=dict(boxstyle="round", fc="w"),
                va="center", ha="center",
                arrowprops=dict(arrowstyle="->", #linestyle="dashed",
                                color="0.5",
                                shrinkA=5, shrinkB=5,
                                patchA=None,
                                patchB=None,
                                connectionstyle=connectionstyle,
                                ),
                )

def drawVertex(ax, label, x1, y1, connectionstyle):


    ax.plot([x1], [y1], ".")
    ax.annotate(label,
                xy=(x1, y1), xycoords='data',
                #xytext=(x2, y2), textcoords='data',
                bbox=dict(boxstyle="round", fc="w"),
                va="center", ha="center",
                arrowprops=dict(arrowstyle="->", #linestyle="dashed",
                                color="0.5",
                                shrinkA=5, shrinkB=5,
                                patchA=None,
                                patchB=None,
                                connectionstyle=connectionstyle,
                                ),
                )




# drawing parameters
figureSize = (15, 10)
drawingDpi = 300

ax1Position = [0.05, 0.05, 0.9, 0.9]
minX1 = 0
maxX1 = 150
minY1 = 0
maxY1 = 100
tickXNum1 = 16
tickYNum1 = 11


# Create a new figure of size 8x6 points, using 80 dots per inch
fig1 = figure(figsize=figureSize)
canvas1 = FigureCanvas(fig1)

# add a new axe
ax1 = fig1.add_axes(ax1Position)

# Set x limits
ax1.set_xlim(minX1, maxX1)

# Set x ticks
ax1.set_xticks(np.linspace(minX1, maxX1, tickXNum1, endpoint=True))

# Set y limits
ax1.set_ylim(minY1, maxY1)

# Set y ticks
ax1.set_yticks(np.linspace(minY1, maxY1, tickYNum1, endpoint=True))

# grid = AxesGrid(fig, 111, (3, 5), label_mode="1", share_all=True)
#
# grid[0].set_autoscale_on(False)


# x1, y1 = 0.3, 0.3
# x2, y2 = 0.7, 0.7

# column = grid.axes_column[0]
#
drawVertex(ax1, "DC", 50, 50, "angle3,angleA=90,angleB=0")
drawEdge(ax1, "cardill", "angle3,angleA=90,angleB=0")
# demo_con_style(ax1, "angle3,angleA=90,angleB=0",
#                label="angle3,\nangleA=90,\nangleB=0")
#
# grid[0].set_xlim(0, 1)
# grid[0].set_ylim(0, 1)
# grid.axes_llc.axis["bottom"].toggle(ticklabels=False)
# grid.axes_llc.axis["left"].toggle(ticklabels=False)
# fig.subplots_adjust(left=0.05, right=0.95, bottom=0.05, top=0.95)



# plt.draw()
plt.show()