import pygame
import numpy

pygame.init()

screenWidth = 1280
screenHeight = 720

BACKGROUND_COLR = (217,217,217)

screen = pygame.display.set_mode((screenWidth, screenHeight))

pygame.display.set_caption("Graphics Programming")

running = True

def ConvertViewPos(pos, cameraPos):
    posMat = numpy.array([[pos[0]],
                          [pos[1]],
                          [1]])
    
    camMat = numpy.array([[1, 0, -cameraPos[0]],
                          [0, 1, -cameraPos[1]],
                          [0, 0, 1]])
    
    scrMat = numpy.matmul(camMat, posMat)

    screen_x = scrMat[0]
    screen_y = scrMat[1]
    
    return ConvertScreenPos((screen_x,screen_y))

def ConvertScreenPos(pos):
    x, y = pos
    screen_x = screenWidth / 2 + x
    screen_y = screenHeight / 2 - y
    
    return (int(screen_x), int(screen_y))
    
def Bresenham(surface, x1, y1, x2, y2, cameraPos, color):
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
            surface.set_at(ConvertViewPos((x,y), cameraPos),color)

            if P >= 0:
                P += -2 * dy
            else:
                y += -1 if y1 > y2 else 1
                P += -2 * dy + 2 * dx
    else:
        for y in range(y1, y2, -1 if y1 > y2 else 1):
            surface.set_at(ConvertViewPos((x,y), cameraPos),color)

            if P >= 0:
                P += -2 * dx
            else:
                x += -1 if x1 > x2 else 1
                P += -2 * dx + 2 * dy

def DrawRect(pos, width, height, cameraPos, color):
    x, y = pos
    offset_x = int(width / 2)
    offset_y = int(height / 2)

    Bresenham(screen, x - offset_x, y - offset_y, x - offset_x, y + offset_y, cameraPos, color)
    Bresenham(screen, x + offset_x, y + offset_y, x + offset_x, y + offset_y, cameraPos, color)
    Bresenham(screen, x + offset_x, y + offset_y, x + offset_x, y - offset_y, cameraPos, color)
    Bresenham(screen, x + offset_x, y - offset_y, x - offset_x, y - offset_y, cameraPos, color)

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

    cameraPos = (20,20)

    DrawRect((0,0), 100, 100, cameraPos, (255,0,0))
    DrawRect((300,350), 100, 100, cameraPos, (255,0,0))
    DrawRect((-300,-300), 100, 100, cameraPos, (255,0,0))

    pygame.display.flip()
    
pygame.quit()