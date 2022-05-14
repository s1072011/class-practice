#include <iostream>

using namespace std;

class Guess {
public:
	//建構子，初始化data[],移除1234~9876中所有含有零及有數字重複的數
	Guess() {
		int i = 0;
		int first = 1234;
		int num[4];
		while (first <= 9876) {
			Spilt(first, num);
			if (noZero(num) && noRepeat(num)) {
				data[i] = first;
				i++;
			}
			first++;
		}
		size = i;
	}
	//移除不可能的答案
	void Think(int a, int b) {
		if (a > 4 || b > 4 || a < 0 || b < 0 || a + b > 4 || a + b < 0) {
			cout << "ERROR" << endl;
			inputFailed = true;
			return;
		}
		if (a == 4) {
			isOver = true;
			cout << "Bingo" << endl;
			return;
		}
		int i, j, k;
		int _ans[4];
		int _data[4];
		int newSize = 0;
		int* temp = new int[size];
		Spilt(ans, _ans);
		for (k = 0; k < size; k++) {
			int A = 0;
			int B = 0;
			Spilt(data[k], _data);
			for (i = 0; i < 4; i++) {
				for (j = 0; j < 4; j++) {
					if (_data[i] == _ans[j]) {
						if (i != j) {
							B++;
							break;
						}
						else {
							A++;
							break;
						}
					}
				}
			}
			if (A == a && B == b) {
				temp[newSize] = data[k];
				newSize++;
			}
		}
		size = newSize;
		delete[] data;
		data = new int[size];
		for (i = 0; i < size; i++)
			data[i] = temp[i];
		delete[] temp;
		round++;
	}
	//從data[]中隨機給一個答案
	void Answer() {
		if (size == 0) {
			cout << "You cheat!" << endl;
			isOver = true;
			return;
		}
		cout << size-1 << " possibilities left" << endl;
		ans = data[inputFailed ? lastRand : Random(size)];
		inputFailed = false;
		cout << "round " << round << " : " << "Ans " << ans << endl;
	}
	//回傳當前遊戲是否結束
	bool Playing() {
		return !isOver;
	}
private:
	bool isOver = false;
	bool inputFailed = false;
	int size;
	int ans = 0;
	int lastRand = 0;
	int round = 1;
	int* data = new int[3024];
	//檢查有沒有零
	bool noZero(int num[]) {
		return num[0] && num[1] && num[2] && num[3];
	}
	//檢查有沒有重複
	bool noRepeat(int num[]) {
		for (int i = 0; i < 4; i++) {
			for (int j = i + 1; j < 4; j++) {
				if (num[i] == num[j]) {
					return false;
				}
			}
		}
		return true;
	}
	//隨機生成一個介於0~size之間的數
	int Random(int size) {
		srand((unsigned)time(NULL) * 100);
		int num = rand() % size;
		lastRand = num;
		return num;
	}
	//將傳入的四位數拆分成四個數字並存入指定陣列
	void Spilt(int num, int* _array) {
		_array[0] = num / 1000;
		_array[1] = (num / 100) % 10;
		_array[2] = (num / 10) % 10;
		_array[3] = num % 10;
	}
};
int main()
{
	cout << 1072011 << endl;
	cout << "楊哲其" << endl;
Restart:
	Guess* guess = new Guess();
	while (guess->Playing()) {
		int a, b;
		guess->Answer();
		if (!guess->Playing()) {
			return 0;
		}
		cin >> a >> b;
		cout << a << "A" << b << "B" << endl;
		cout << "---------------------" << endl;
		guess->Think(a, b);
	}
	cout << "Game Over" << endl;
	cout << "Play again?(y/n)" << endl;
	char c;
	while (cin >> c) {
		if (c == 'y' || c == 'Y') {
			delete guess;
			cout << "---------------------" << endl;
			goto Restart;
		}
		else if (c == 'n' || c == 'N') {
			return 0;
		}
	}
	return 0;
}