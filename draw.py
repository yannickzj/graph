
import numpy as np
from matplotlib import pyplot as plt
from matplotlib.pylab import *
from matplotlib.backends.backend_agg import FigureCanvasAgg as FigureCanvas
import matplotlib.patches as mpatches

def retrieveVertex(vertexDic, str):
    line = str.split()
    name = line[0]
    type = int(line[1])
    x = int(line[2])
    y = int(line[3])
    vertexDic[name] = [type, x, y]


def retrieveEdge(edgeDic, str):
    line = str.split()
    name = line[0]
    v1 = line[1]
    v2 = line[2]
    direction = int(line[3])
    length = int(line[5])
    speed = int(line[4])
    type = int(line[6])
    edgeDic[name] = [v1, v2, direction, length, speed, type]


def retrievePath(pathDic, str):
    line = str.split()
    num = len(line)
    name = line[0]
    pathDic[name] = []

    for i in range(1, num):
        pathDic[name].append(line[i])



def drawEdge(ax, label, v1, x1, y1, v2, x2, y2, dir, length, speed, paths1, paths2, connectionstyle, factor, pathColor1, pathColor2):

    if (dir == 0):
        style = '<->'
    elif (dir == 1):
        style = '<-'
    else:
        style = '->'

    if (label in paths1):
        color = pathColor1
    elif (label in paths2):
        color = pathColor2
    else:
        color = 'k'

    el = mpatches.Ellipse((x1, y1), len(v1)*factor/4, factor/3, angle=0, alpha=0.0)
    ax.add_artist(el)
    an1 = ax.annotate(v1, xy=(x1, y1), xycoords="data",
                        va="center", ha="center",
                        bbox=dict(boxstyle="round", fc="w"))
    an2 = ax.annotate(v2, xy=(0.5, 0.5), xycoords=an1,
                        xytext=(x2, y2), textcoords='data',
                        bbox=dict(boxstyle="round", fc="w"),
                        va="center", ha="center",
                        arrowprops=dict(arrowstyle=style, #linestyle="dashed",
                                        color=color,
                                        shrinkA=15, shrinkB=0,
                                        patchA=None,
                                        patchB=el,
                                        connectionstyle=connectionstyle,
                                        ),
                        )
    x3 = x1/2.0+x2/2.0
    y3 = y1/2.0+y2/2.0
    an3 = ax.annotate(str(length)+'/'+str(speed), xy=(x3, y3), xycoords="data",
                      va="center", ha="center", color='b')

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



################
####  main  ####
################


if __name__ == '__main__':

    fileName = 'test2.txt'
    fp = open(fileName, 'r')
    data = fp.readlines()
    fp.close()

    vertexDic = {}
    edgeDic = {}
    pathDic = {}

    num = len(data)
    i = 0

    while (i<num):
        line = data[i]
        if ('#vertex' in line):
            i += 1
            line = data[i]
            while ('#' not in line):
                if (line.strip() != ''):
                    retrieveVertex(vertexDic, line)
                i += 1
                line = data[i]


        if ('#edge' in line):
            i += 1
            line = data[i]
            while ('#' not in line):
                if (line.strip() != ''):
                    retrieveEdge(edgeDic, line)
                i += 1
                line = data[i]

        if ('#path' in line):
            i += 1
            line = data[i]
            while ('#' not in line):
                if (line.strip() != ''):
                    retrievePath(pathDic, line)
                i += 1
                line = data[i]

        i += 1



    # drawing parameters
    figureSize = (15, 10)
    drawingDpi = 300

    ax1Position = [0.05, 0.05, 0.9, 0.9]
    minX1 = 0
    maxX1 = 160
    minY1 = 0
    maxY1 = 100
    tickXNum1 = 17
    tickYNum1 = 11
    factor = 10


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


    for edge in edgeDic.keys():
        v1 = edgeDic[edge][0]
        v2 = edgeDic[edge][1]
        x1 = vertexDic[v1][1] * factor
        y1 = vertexDic[v1][2] * factor
        x2 = vertexDic[v2][1] * factor
        y2 = vertexDic[v2][2] * factor
        dir = edgeDic[edge][2]
        length = edgeDic[edge][3]
        speed = edgeDic[edge][4]
        paths1 = pathDic['path1_fastest']
        color1 = 'r'
        paths2 = pathDic['path1_shortest']
        color2 = 'g'

        drawEdge(ax1, edge, v1, x1, y1, v2, x2, y2, dir, length, speed, paths1, paths2, "arc3,rad=-0.12", factor, color1, color2)



    plt.show()