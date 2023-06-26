import pygame
import numpy as np
import math
from pygame.locals import *
import keyboard

# 화면 설정
WIDTH, HEIGHT = 1280, 720
BG_COLOR = (105,105,105)

# 초기화
pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))

# 메쉬 데이터 초기화
    # 정점 데이터 구성
cube_size = 100
half_size = cube_size / 2
tripoint = np.array([
    [-1* half_size, -1* half_size, 1* half_size, 1],
    [ 1* half_size, -1* half_size, 1* half_size, 1],
        [ 1* half_size, 1* half_size, 1* half_size, 1],
        [-1* half_size, 1* half_size, 1* half_size, 1],
        [-1* half_size, -1* half_size, -1* half_size, 1],
        [ 1* half_size, -1* half_size, -1* half_size, 1],
        [ 1* half_size, 1* half_size, -1* half_size, 1],
        [-1* half_size, 1* half_size, -1* half_size, 1]
    ])

    # 삼각형을 이루는 정점 인덱스 구축
trifaces = [
        [0, 1, 2], # Front
        [2, 3, 0], # Front
        [7, 6, 5], # Back
        [5, 4, 7], # Back
        [4, 5, 1], # Bottom
        [1, 0, 4], # Bottom
        [3, 2, 6], # Top
        [6, 7, 3], # Top
        [4, 0, 3], # Left
        [3, 7, 4], # Left
        [1, 5, 6], # Right
        [6, 2, 1] # Right
    ]

    # model matrix 구성
    # numpy 라이브러리를 이용해서 단위행렬을 만들 때에 np.eye(차원) 사용
model_matrix = np.eye(4)

    # 이동 변환 행렬
translate_pos = [0,0,0]
translate_matrix = np.array([
        [1, 0, 0, translate_pos[0]],
        [0, 1, 0, translate_pos[1]],
        [0, 0, 1, translate_pos[2]],
        [0, 0, 0, 1]
    ])

    # 크기 변환 행렬
scale_value = [1,1,1]
scale_matrix = np.array([
        [scale_value[0], 0, 0, 0],
        [0, scale_value[1], 0, 0],
        [0, 0, scale_value[2], 0],
        [0, 0, 0, 1]
    ])

    # 회전 변환 행렬
    # 회전 변환 행렬의 값은 radian값이므로 주의 : math.radians 혹은 numpy.deg2rad 사용
rotation_value = [0,0,0]
rotation_x = np.array([
        [1, 0, 0, 0],
        [0, np.cos(rotation_value[0]), -np.sin(rotation_value[0]), 0],
        [0, np.sin(rotation_value[0]), np.cos(rotation_value[0]), 0],
        [0, 0, 0, 1]
    ])

rotation_y = np.array([
        [np.cos(rotation_value[1]), 0, np.sin(rotation_value[1]), 0],
        [0, 1, 0, 0],
        [-np.sin(rotation_value[1]), 0, np.cos(rotation_value[1]),0],
        [0, 0, 0, 1]
    ])

rotation_z = np.array([
        [np.cos(rotation_value[2]), -np.sin(rotation_value[2]), 0, 0],
        [np.sin(rotation_value[2]), np.cos(rotation_value[2]), 0, 0],
        [0, 0, 1, 0],
        [0, 0, 0, 1]
    ])

    # Rotaiton : Ry.Rx.Rz
rotation_matrix = np.matmul(rotation_y,np.matmul(rotation_x,rotation_z))

    # model matrix : T.R.S
model_matrix = np.matmul(translate_matrix,np.matmul(rotation_matrix,scale_matrix)) 

    # view matrix 구성
    # 카메라 위치
cam_pos = np.array([0, 0, 300])
    # 바라보는 위치
target_pos = np.array([0, 0, 0])
    # 카메라의 위쪽 방향 기준 벡터
up = np.array([0, 1, 0])

    # x,y,z축은 모두 정규화 : 벡터의 노름을 반환하는 np.linalg.norm 이용
view_z = (target_pos - cam_pos)
view_z = view_z / np.linalg.norm(view_z)
view_x = np.cross(up, view_z)
view_x = view_x / np.linalg.norm(view_x)
view_y = np.cross(view_z, view_x)
view_y = view_y/ np.linalg.norm(view_y)

cam_inv_model_matrix = np.array([
        [view_x[0], view_x[1], view_x[2], -np.dot(view_x, cam_pos)],
        [view_y[0], view_y[1], view_y[2], -np.dot(view_y, cam_pos)],
        [view_z[0], view_z[1], view_z[2], -np.dot(view_z, cam_pos)],
        [0, 0, 0, 1]
    ])
    
rotation_y_180 = np.array([
        [-1, 0, 0, 0],
        [ 0, 1, 0, 0],
        [ 0, 0, -1, 0],
        [ 0, 0, 0, 1]
    ])

    # y축 180를 회전시켜서 x,y축이 수학적인 2차원 좌표계처럼 보이게 수정
view_matrix = np.matmul(rotation_y_180,cam_inv_model_matrix)

    # clip Space : projection matrix
fov = math.radians(80)

k = WIDTH / HEIGHT # aspectio ration
n = 0.1 # near clip plane
f = 1000 # far clip plane

d = 1 / np.tan(fov / 2) # forcal length

projection_matrix = np.array([
        [d/k, 0, 0, 0],
        [0, d, 0, 0],
        [0, 0, (n + f) / (n - f), (2 * n * f) / ( n - f)],
        [0, 0, -1, 0]
    ])

    # screen space : viewport transform
viewport_matrix = np.array([
        [WIDTH / 2, 0, 0, WIDTH / 2],
        [0, -HEIGHT / 2, 0, HEIGHT / 2],
        [0, 0, 0.5, 0.5],
        [0, 0, 0, 1]
    ])



CUBE_COLOR = (255,0,0)

# 게임 루프
running = True
while running:
    for event in pygame.event.get():
        if event.type == QUIT:
            running = False

    # Update
    proj_view_model_matrix =np.matmul(projection_matrix,np.matmul(view_matrix,model_matrix))
    transform_points = []

    for vertex in tripoint:
        # 3D 좌표계에서 2D 좌표계로 변환
        v = np.matmul(proj_view_model_matrix, vertex)
        # NDC 좌표 변환
        v /= v[3]
        #화면 좌표 변환
        v = np.matmul(viewport_matrix, v)
        transform_points.append(v[:3])

    # 렌더링
    screen.fill(BG_COLOR)
    for face in trifaces:
        face_points = []
        for j in face:
            face_points.append(transform_points[j][:2])
        pygame.draw.polygon(screen, CUBE_COLOR, face_points)
        
    pygame.display.flip()

pygame.quit()