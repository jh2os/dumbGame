#ifndef COLLISIONMAP_H
#define COLLISIONMAP_H

class collisionMap {
private:
	int width;
	int height;
public:
	vector<int> id;
	vector<int> col;

	void resetMap(int x, int y) {
		width = x;
		height = y;
		if(id.size() == 0){
			for(int i = 0; i < x * y; i++) {
				id.push_back(0);
			}

		}
		for(int i = 0; i < x * y; i++) {
			id.at(i) = 0;
		}
	}
	void clearMap() {
		id.clear();
	}
	int checkSpace(int x, int y) {
		return id[x * width + y];
	}
	void setSpace(int x, int y, int val) {
		id[x*width + y] = val;
	}
};

#endif
