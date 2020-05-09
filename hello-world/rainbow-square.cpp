#include <iostream>

int main()
{
	const int image_width = 256;
	const int image_height = 256;

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height-1; j >= 0; --j)
	{
		for (int i = image_width-1; i >= 0; --i)
		{
			// red goes from black to fully red, from left to right
			auto r = double(i) / (image_width-1);
			// green goes from balck to fully green, from bottom to top
			auto g = double(j) / (image_height-1);
		}
	}
}
