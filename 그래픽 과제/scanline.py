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

def scanline(surface, vertices, color):
    vertices.sort(key=lambda v : v[1])

    x1,y1 = vertices[0]
    x2,y2 = vertices[1]
    x3,y3 = vertices[2]

    a12 = 0 if (y2-y1) == 0 else (x2-x1)/(y2-y1)
    a13 = 0 if (y3-y1) == 0 else (x3-x1)/(y3-y1)
    a23 = 0 if (y3-y2) == 0 else (x3-x2)/(y3-y2)

    for y in range(y1,y2):
        tmp1 = int(a12 * (y - y1) + x1)
        tmp2 = int(a13 * (y - y1) + x1)

        if tmp1 > tmp2:
            tmp1, tmp2 = tmp2, tmp1

        for x in range(tmp1, tmp2):
            surface.set_at(convetScreenCoordTuple((x,y)),color)

    for y in range(y2,y3):
        tmp1 = int(a23 * (y - y2) + x2)
        tmp2 = int(a13 * (y - y1) + x1)

        if tmp1 > tmp2:
            tmp1, tmp2 = tmp2, tmp1

        for x in range(tmp1, tmp2):
            surface.set_at(convetScreenCoordTuple((x,y)),color)

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
    
    scanline(screen, [(100,50),(50,200),(150,250)],(255,0,0))
    scanline(screen, [(-50,50),(-150,200),(-100,250)],(255,0,0))
    scanline(screen, [(100,-50),(50,-50),(150,-250)],(255,0,0))
    scanline(screen, [(-100,-50),(-50,-250),(-150,-250)],(255,0,0))

    pygame.display.flip()
    
pygame.quit()