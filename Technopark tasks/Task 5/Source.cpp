#include <iostream>
#include <assert.h>

using namespace std;

struct Step {
	int width;
	int height;
	int beginX;

	Step() {};
	Step(int w, int h) : width(w), height(h) {};
};

class StackOfSteps {

private:
	int bufferSize = 30;
	Step* buffer = new Step[bufferSize];
	int head = 0;
	int maxSquare = 0;

	void grow() {
		bufferSize *= 2;
		Step* temp = new Step[bufferSize];
		for (int i = 0; i < head; i++) {
			temp[i] = buffer[i];
		}
		delete[] buffer;
		buffer = temp;
	}

	void push(Step s) {
		if (bufferSize == head) {
			grow();
		}
		buffer[head++] = s;
	}

	Step pop() {
		assert(head > 0);
		Step res = buffer[--head];
		return res;
	}

public:

	StackOfSteps() {}

	int getMaxSquare() 
	{
		add(Step(1, 0));
		return maxSquare;
	}

	void concatStepsToMaxSquare(Step s) {
		int endX = s.beginX + s.width;
		Step prevStep = pop();
		int lastEndX = prevStep.beginX + prevStep.width;
		int squareOfLastBigStep = prevStep.width * prevStep.height;

		if (squareOfLastBigStep > maxSquare) {
			maxSquare = squareOfLastBigStep;
		}

		while (head > 0 && buffer[head - 1].height >= s.height) {
			prevStep = pop();
			squareOfLastBigStep = (lastEndX - prevStep.beginX) * prevStep.height;
			if (squareOfLastBigStep > maxSquare) {
				maxSquare = squareOfLastBigStep;
			}
		}

		int beginXOfNewConcatedStep = buffer[head].beginX;
		Step newConcatedStep(endX - beginXOfNewConcatedStep, s.height);
		newConcatedStep.beginX = beginXOfNewConcatedStep;
		push(newConcatedStep);
	}

	void add(Step s) {

		if (head == 0) {
			s.beginX = 0;
			int square = s.width * s.height;
			if (square > maxSquare) {
				maxSquare = square;
			}
			push(s);
			return;
		}
		else {
			s.beginX = buffer[head - 1].beginX + buffer[head - 1].width;
		}

		if (s.height <= buffer[head - 1].height) {
			concatStepsToMaxSquare(s);
		}
		else {
			push(s);
		}

	}

	~StackOfSteps() {
		delete[] buffer;
	}

};


int main() {

	StackOfSteps s;
	int N = 4;
	cin >> N;

	int Width = 0;
	int Height = 0;

	for (int i = 0; i < N; i++) {
		cin >> Width;
		cin >> Height;
		s.add(Step(Width, Height));
	}

	 int result = s.getMaxSquare();

	cout << result;

	return 0;
}
