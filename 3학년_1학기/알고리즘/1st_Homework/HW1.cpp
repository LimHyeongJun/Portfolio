//실행환경 : Window에서 visual studio 2017 C++

#include <iostream>

using namespace std;

int main(void) {
	int n;

	cin >> n;

	double **arr = new double*[n + 1];
	for (int i = 0; i < n + 1; ++i) {
		arr[i] = new double[n + 1];
	}

	for (int i = 0; i < n + 1; i++) {
		for (int j = 0; j < n + 1; j++) {
			arr[i][j] = 0;
			if (j > 0 && i > 0)
				break;
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> arr[i][j];
			arr[i][j] += arr[i][j - 1]; //2차원 배열의 각 행에서의 값들을 이전 열까지의 누적합으로 한다.
		}
	}

	double maxResult = -10000000;
	double minResult = 10000000;
	int maxResultPoint[]{ 0, 0, 0, 0 };
	int minResultPoint[]{ 0, 0, 0, 0 };

	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < i + 1; j++) {
			double maxRowTempResult = 0;
			int maxRowTempResultPoint[]{ 0, 0, 0, 0 };

			double minRowTempResult = 0;
			int minRowTempResultPoint[]{ 0, 0, 0, 0 };

			for (int k = 1; k < n + 1; k++) {
				double tempResult = arr[k][i] - arr[k][j - 1];

				//최대값 구하는 부분
				if (maxRowTempResult + tempResult > tempResult) {
					maxRowTempResult = maxRowTempResult + tempResult;
					maxRowTempResultPoint[2] = k;
					maxRowTempResultPoint[3] = i;
				} else if(maxRowTempResult + tempResult <= tempResult) {
					maxRowTempResult = tempResult;
					maxRowTempResultPoint[0] = k;
					maxRowTempResultPoint[1] = j;
					maxRowTempResultPoint[2] = k;
					maxRowTempResultPoint[3] = i;
				}

				if (maxRowTempResult > maxResult) {
					maxResultPoint[0] = maxRowTempResultPoint[0];
					maxResultPoint[1] = maxRowTempResultPoint[1];
					maxResultPoint[2] = maxRowTempResultPoint[2];
					maxResultPoint[3] = maxRowTempResultPoint[3];
					maxResult = maxRowTempResult;
				}

				//최소값 구하는 부분
				if (minRowTempResult + tempResult < tempResult) {
					minRowTempResult = minRowTempResult + tempResult;
					minRowTempResultPoint[2] = k;
					minRowTempResultPoint[3] = i;
				} else if (minRowTempResult + tempResult >= tempResult) {
					minRowTempResult = tempResult;
					minRowTempResultPoint[0] = k;
					minRowTempResultPoint[1] = j;
					minRowTempResultPoint[2] = k;
					minRowTempResultPoint[3] = i;
				}

				if (minRowTempResult < minResult) {
					minResultPoint[0] = minRowTempResultPoint[0];
					minResultPoint[1] = minRowTempResultPoint[1];
					minResultPoint[2] = minRowTempResultPoint[2];
					minResultPoint[3] = minRowTempResultPoint[3];
					minResult = minRowTempResult;
				}
			}
		}
	}

	cout << minResult << endl;
	cout << "(" << minResultPoint[0] << "," << minResultPoint[1] << ")(" << minResultPoint[2] << "," << minResultPoint[3] << ")" << endl;
	cout << maxResult << endl;
	cout << "(" << maxResultPoint[0] << "," << maxResultPoint[1] << ")(" << maxResultPoint[2] << "," << maxResultPoint[3] << ")" << endl;

	delete[] arr;

	return 0;
}