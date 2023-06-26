import pygame
import numpy as np
import math
from pygame.locals import *

class Vertex:
    def __init__(self, position=None, uv=None):
        self.position = position if position is not None else np.array([1, 1, 1])
        self.uv = uv if uv is not None else np.array([1, 1])

    def set_position(self, position) :
        self.position = position
        
    def set_uv(self, uv) :
        self.uv = uv
