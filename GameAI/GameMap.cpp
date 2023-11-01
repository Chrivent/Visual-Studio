#include "GameMap.h"
#include <iostream>
using namespace std;

CGameMap::CGameMap()
{
}


CGameMap::~CGameMap()
{
	for (int i = 0; i < m_height; i++) {
		delete[] m_map[i];
		delete[] m_visitInfo[i];
	}
	delete[] m_map;
	delete[] m_visitInfo;
	
}

void CGameMap::initMap()
{
	for (int h = 0; h < m_height; h++)
		for (int w = 0; w < m_width; w++) {
			m_map[h][w] = 1000;
			m_visitInfo[h][w] = false;
	}
}

void CGameMap::setMap(int ** map)
{
	memcpy(m_map, map, sizeof(int)*m_width*m_height);
	//for (int h = 0; h < m_height; h++)
	//	for (int w = 0; w < m_width; w++)
	//		m_map[h][w] = map[h][w];
}

void CGameMap::draw()
{
	cout << "=====================" << endl;
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			cout << m_map[y][x] << "\t";
		}
		cout << endl;
	}
}
