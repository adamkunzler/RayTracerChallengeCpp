#include <iostream>

int main()
{
	int width = 320;
	int height = 64;
	int numThreads = 32;

	int threadCount = 0;
	int yStart = 0;
	int yStep = (int)height / numThreads;
	for (int i = 0; i < numThreads; i++)
	{
		//Color* data = new Color[(int)camera.hSize * yStep];
		//datas.push_back(data);

		int yEnd = yStart + yStep > height ? yEnd = height : yStart + yStep;
		//std::thread t(renderThreadFunc, std::ref(camera), std::ref(world), (int)camera.hSize, yStart, yEnd, data);

		//std::cout << "\n Thread #" << threadCount << "\t start: " << yStart << "\t end: " << yEnd;

		//threads.push_back(std::move(t));

		yStart += yStep;
		threadCount++;
	}

	int sum = 0;
	for (int i = 0; i <= 200; i++)
	{
		std::cout << "\n 32 x " << i << " = \t " << sum;
		sum += 32;
	}


	return 0;
}