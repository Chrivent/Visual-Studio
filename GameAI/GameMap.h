#pragma once
class CGameMap
{
	int **m_map;
	bool **m_visitInfo;
	int m_width;
	int m_height;
public:
	CGameMap();
	~CGameMap();
	CGameMap(int w, int h) : m_width(w), m_height(h) {
		m_map = new int *[h];
		m_visitInfo = new bool *[h];
		for (int i = 0; i < h; i++) {
			m_map[i] = new int[w];
			m_visitInfo[i] = new bool[w];
		}
		initMap();
	}

	void initMap();
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
	void setMap(int **map);

	void setMapVal(int x, int y, int val) { m_map[y][x] = val; }
	int getMapVal(int x, int y) { return m_map[y][x]; }

	void setVisitInfo(int x, int y, bool val) { m_visitInfo[y][x] = val; }
	bool getVisitInfo(int x, int y) { return m_visitInfo[y][x]; }

	void draw();
};

