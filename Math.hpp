#ifndef HEADER_MATH
#define HEADER_MATH

#include <vector>

class Matrix {
public:
	Matrix(int height, int width){
		for (int i = 0; i < height; i++){
			for (int j = 0; j < width; j++){
				m[i].push_back(0);
			}
		}
	}

private:
	std::vector<std::vector<int>> m;
}

#endif