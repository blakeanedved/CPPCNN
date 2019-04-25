#include <boost/ptr_container/ptr_vector.hpp>
#include <vector>
#include <iostream>
#include "classes/CNNnew.h"

auto main() -> int {

	CNN::Network cnn;

	cnn.AddLayer(CNN::Layers::Conv2d(32, {5, 5}, 1, CNN::Padding::SAME, Activation::Activation_Function::RELU));

	//cnn.AddLayer(CNN::Layers::MaxPool({2, 2}, 2));

	cnn.AddLayer(CNN::Layers::Conv2d(32, {5, 5}, 1, CNN::Padding::SAME, Activation::Activation_Function::RELU));

	//cnn.AddLayer(CNN::Layers::MaxPool({2, 2}, 2));

	//cnn.AddLayer(CNN::Layers::Dropout(0.25));

	std::vector<std::vector<float>> input;

	for (int i = 0; i < 28; i++){
		input.push_back(std::vector<float>());
		for (int j = 0; j < 28; j++){
			input[i].push_back((rand()%10)/10);
		}
	}

	auto data = cnn.Activate(input);

	std::cout << "Data (" << data.size() << "x" << data[0].size() << "x" << data[0][0].size() << ")" << std::endl;

	cnn.BackPropagate(data);

	//for (int i = 0; i < data.size(); i++){
		//for (int j = 0; j < data[i].size(); j++){
			//std::cout << data[i][j] << " ";

		//}
	//}

	return 0;
}
