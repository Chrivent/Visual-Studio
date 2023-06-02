import pygame
import numpy as np

pygame.init()

screenWidth = 1280
screenHeight = 720

BACKGROUND_COLR = (217,217,217)

screen = pygame.display.set_mode((screenWidth, screenHeight))

pygame.display.set_caption("Graphics Programming")

running = True

def convetScreenCoordTuple(arg):
    x, y = arg
    screen_x = screenWidth / 2 + x
    screen_y = screenHeight / 2 + y
    
    return (int(screen_x), int(screen_y))
    
def bresenham(surface, x1, y1, x2, y2, color):

    if x1 > x2:
        x1, x2 = x2, x1
        y1, y2 = y2, y1

    x = x1
    y = y1
    dx = abs(x2 - x1)
    dy = abs(y2 - y1)

    P = -2 * dy + dx
    
    if dx > dy:
        for x in range(x1, x2):
            surface.set_at(convetScreenCoordTuple((x,y)),color)

            if P >= 0:
                P += -2 * dy
            else:
                y += -1 if y1 > y2 else 1
                P += -2 * dy + 2 * dx
    else:
        for y in range(y1, y2, -1 if y1 > y2 else 1):
            surface.set_at(convetScreenCoordTuple((x,y)),color)

            if P >= 0:
                P += -2 * dx
            else:
                x += -1 if x1 > x2 else 1
                P += -2 * dx + 2 * dy

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
            
    screen.fill(BACKGROUND_COLR)

    LINE_COLOR = (128,128,128)

    pygame.draw.line(screen, LINE_COLOR, (screenWidth / 2, 0), (screenWidth / 2, screenHeight), 3)
    pygame.draw.line(screen, LINE_COLOR, (0, screenHeight / 2), (screenWidth, screenHeight / 2), 3)

    for x in range(0, screenWidth, 10):
        pygame.draw.line(screen, LINE_COLOR , (x, 0), (x, screenHeight), 1)

    for y in range(0, screenWidth, 10):
        pygame.draw.line(screen, LINE_COLOR , (0, y), (screenWidth, y), 1)

    bresenham(screen, 30, 10, 180, 120, (255,0,0))
    bresenham(screen, 10, 30, 120, 180, (255,0,0))
    bresenham(screen, -30, 10, -180, 120, (255,0,0))
    bresenham(screen, -10, 30, -120, 180, (255,0,0))
    bresenham(screen, 30, -10, 180, -120, (255,0,0))
    bresenham(screen, 10, -30, 120, -180, (255,0,0))
    bresenham(screen, -30, -10, -180, -120, (255,0,0))
    bresenham(screen, -10, -30, -120, -180, (255,0,0))

    pygame.display.flip()
    
pygame.quit()