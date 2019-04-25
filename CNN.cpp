#include "CNN.h"
#include <iostream>

//CNN::Layers::Input::Input(std::pair<unsigned int, unsigned int> input_size){
	//this->input_width = input_size.first;
	//this->input_height = input_size.second;
	//this->output_width = input_size.first;
	//this->output_height = input_size.second;
//}

//CNN::Layers::Input::Input(std::pair<unsigned int, unsigned int> input_size, std::pair<unsigned int, unsigned int> resized_dimensions){
	//this->input_width = input_size.first;
	//this->input_height = input_size.second;

	//// TODO: implement a image resizer for input
//}

//CNN::Layers::Input::~Input(){}

//auto CNN::Layers::Input::Activate(std::vector<std::vector<float>>& inputs) -> std::vector<std::vector<std::vector<float>>> {
	//if (this->amount_of_filters == 0){
		//std::cout << "The Input layer cannot be the only layer (CNN.cpp:)" << std::endl;
		//exit(1);
	//}
	//return std::vector<std::vector<std::vector<float>>>(this->amount_of_filters, inputs);
//}

CNN::Layers::Layer::Layer(){}
//auto CNN::Layers::Layer::Activate(std::vector<std::vector<std::vector<float>>>& inputs) -> std::vector<std::vector<std::vector<float>>> {std::cout << "base" << std::endl;return inputs;}
//auto CNN::Layers::Layer::BackPropagate(std::vector<std::vector<std::vector<float>>>& previous_deltas) -> std::vector<std::vector<std::vector<float>>> {return previous_deltas;}
auto CNN::Layers::Layer::ReportDims() -> void {
	std::cout << "input (" << this->input_width << "x" << this->input_height << ") -> output (" << this->output_width << "x" << this->output_height << ")" << std::endl;
}

//CNN::Layers::Conv2d::Conv2d(CNN::Layers::Layer& input_layer, int filters, std::pair<int, int> kernel_size, int stride, CNN::Padding padding, Activation::Activation_Function activation_function){
	//this->kernel_width = kernel_size.first;
	//this->kernel_height = kernel_size.second;
	//switch (padding){
		//case CNN::Padding::VALID:
			//this->width_padding = 0;
			//this->height_padding = 0;
			//break;
		//case CNN::Padding::SAME:
			//this->width_padding = static_cast<int>(this->kernel_width / 2);
			//this->height_padding = static_cast<int>(this->kernel_height / 2);
			//break;
		//case CNN::Padding::FULL:
			//this->width_padding = this->kernel_width - 1;
			//this->height_padding = this->kernel_height - 1;
			//break;
	//}
	//this->amount_of_filters = filters;
	////this->input_width = input_layer.output_width;
	////this->input_height = input_layer.output_height;
	//this->stride = stride;

	////this->output_width = (this->input_width - this->kernel_width + 2 * this->width_padding)/(this->stride) + 1;
	////this->output_height = (this->input_height - this->kernel_height + 2 * this->height_padding)/(this->stride) + 1;
	
	//switch (activation_function){
		//case Activation::IDENTITY:
			//this->activation_function = Activation::Identity;
			//this->activation_function_derivative = Activation::Identity_Derivative;
			//break;
		//case Activation::SIGMOID:
			//this->activation_function = Activation::Sigmoid;
			//this->activation_function_derivative = Activation::Sigmoid_Derivative;
			//break;
		//case Activation::RELU:
			//this->activation_function = Activation::Relu;
			//this->activation_function_derivative = Activation::Relu_Derivative;
			//break;
		//case Activation::HYPERBOLIC_TANGENT:
			//this->activation_function = Activation::Hyperbolic_Tangent;
			//this->activation_function_derivative = Activation::Hyperbolic_Tangent_Derivative;
			//break;
		//case Activation::FAST_SIGMOID:
			//this->activation_function = Activation::Fast_Sigmoid;
			//this->activation_function_derivative = Activation::Fast_Sigmoid_Derivative;
			//break;
	//}

	//for (int i = 0; i < amount_of_filters; i++){
		//this->filters.push_back(std::vector<std::vector<float>>());
		//for (int j = 0; j < kernel_height; j++){
			//this->filters[i].push_back(std::vector<float>());
			//for (int k = 0; k < kernel_width; k++){
				//this->filters[i][j].push_back(((rand()%200)/1000)-0.1);
			//}
		//}
	//}
//}

//CNN::Layers::Conv2d::Conv2d(CNN::Layers::Input& input_layer, int filters, std::pair<int, int> kernel_size, int stride, CNN::Padding padding, Activation::Activation_Function activation_function){
	//this->kernel_width = kernel_size.first;
	//this->kernel_height = kernel_size.second;
	//switch (padding){
		//case CNN::Padding::VALID:
			//this->width_padding = 0;
			//this->height_padding = 0;
			//break;
		//case CNN::Padding::SAME:
			//this->width_padding = static_cast<int>(this->kernel_width / 2);
			//this->height_padding = static_cast<int>(this->kernel_height / 2);
			//break;
		//case CNN::Padding::FULL:
			//this->width_padding = this->kernel_width - 1;
			//this->height_padding = this->kernel_height - 1;
			//break;
	//}
	//this->amount_of_filters = filters;
	////input_layer.amount_of_filters = filters;
	////this->input_width = input_layer.output_width;
	////this->input_height = input_layer.output_height;
	//this->stride = stride;

	////this->output_width = (this->input_width - this->kernel_width + 2 * this->width_padding)/(this->stride) + 1;
	////this->output_height = (this->input_height - this->kernel_height + 2 * this->height_padding)/(this->stride) + 1;
	
	//switch (activation_function){
		//case Activation::IDENTITY:
			//this->activation_function = Activation::Identity;
			//this->activation_function_derivative = Activation::Identity_Derivative;
			//break;
		//case Activation::SIGMOID:
			//this->activation_function = Activation::Sigmoid;
			//this->activation_function_derivative = Activation::Sigmoid_Derivative;
			//break;
		//case Activation::RELU:
			//this->activation_function = Activation::Relu;
			//this->activation_function_derivative = Activation::Relu_Derivative;
			//break;
		//case Activation::HYPERBOLIC_TANGENT:
			//this->activation_function = Activation::Hyperbolic_Tangent;
			//this->activation_function_derivative = Activation::Hyperbolic_Tangent_Derivative;
			//break;
		//case Activation::FAST_SIGMOID:
			//this->activation_function = Activation::Fast_Sigmoid;
			//this->activation_function_derivative = Activation::Fast_Sigmoid_Derivative;
			//break;
	//}

	//for (int i = 0; i < amount_of_filters; i++){
		//this->filters.push_back(std::vector<std::vector<float>>());
		//for (int j = 0; j < kernel_height; j++){
			//this->filters[i].push_back(std::vector<float>());
			//for (int k = 0; k < kernel_width; k++){
				//this->filters[i][j].push_back(((rand()%200)/1000)-0.1);
			//}
		//}
	//}
//}

CNN::Layers::Conv2d::Conv2d(int filters, std::pair<int, int> kernel_size, int stride, CNN::Padding padding, Activation::Activation_Function activation_function){
	this->kernel_width = kernel_size.first;
	this->kernel_height = kernel_size.second;
	switch (padding){
		case CNN::Padding::VALID:
			this->width_padding = 0;
			this->height_padding = 0;
			break;
		case CNN::Padding::SAME:
			this->width_padding = static_cast<int>(this->kernel_width / 2);
			this->height_padding = static_cast<int>(this->kernel_height / 2);
			break;
		case CNN::Padding::FULL:
			this->width_padding = this->kernel_width - 1;
			this->height_padding = this->kernel_height - 1;
			break;
	}
	this->amount_of_filters = filters;
	this->stride = stride;

	//this->output_width = (this->input_width - this->kernel_width + 2 * this->width_padding)/(this->stride) + 1;
	//this->output_height = (this->input_height - this->kernel_height + 2 * this->height_padding)/(this->stride) + 1;
	
	switch (activation_function){
		case Activation::IDENTITY:
			this->activation_function = Activation::Identity;
			this->activation_function_derivative = Activation::Identity_Derivative;
			break;
		case Activation::SIGMOID:
			this->activation_function = Activation::Sigmoid;
			this->activation_function_derivative = Activation::Sigmoid_Derivative;
			break;
		case Activation::RELU:
			this->activation_function = Activation::Relu;
			this->activation_function_derivative = Activation::Relu_Derivative;
			break;
		case Activation::HYPERBOLIC_TANGENT:
			this->activation_function = Activation::Hyperbolic_Tangent;
			this->activation_function_derivative = Activation::Hyperbolic_Tangent_Derivative;
			break;
		case Activation::FAST_SIGMOID:
			this->activation_function = Activation::Fast_Sigmoid;
			this->activation_function_derivative = Activation::Fast_Sigmoid_Derivative;
			break;
	}

	for (int i = 0; i < this->amount_of_filters; i++){
		this->filters.push_back(std::vector<std::vector<float>>());
		for (int j = 0; j < this->kernel_height; j++){
			this->filters[i].push_back(std::vector<float>());
			for (int k = 0; k < this->kernel_width; k++){
				this->filters[i][j].push_back(((rand()%200)/1000)-0.1);
			}
		}
	}

	std::cout << "made Conv2d" << std::endl;
	std::cout << this->filters.size() << std::endl;
	std::cout << this->filters[0].size() << std::endl;
	std::cout << this->filters[0][0].size() << std::endl;
}

CNN::Layers::Conv2d::~Conv2d(){}

auto CNN::Layers::Conv2d::Activate(std::vector<std::vector<std::vector<float>>>& inputs) -> std::vector<std::vector<std::vector<float>>> {

	while (inputs.size() > this-> amount_of_filters)
		inputs.pop_back();

	int inp = 0, original_size = inputs.size();
	while (this->amount_of_filters > inputs.size())
		inputs.push_back(inputs[(inp++)%original_size]);

	std::vector<std::vector<std::vector<float>>> outputs;

	int total;
	for (int i = 0; i < this->amount_of_filters; i++){
		outputs.push_back(std::vector<std::vector<float>>());
		
		for (int j = -this->height_padding; j + this->kernel_height <= inputs[0].size() + this->height_padding; j+=this->stride){
			outputs[i].push_back(std::vector<float>());
			for (int k = -this->width_padding; k + this->kernel_width <= inputs[0][0].size() + this->width_padding; k+=this->stride){
				total = 0;
				for (int y = 0; y < this->kernel_height; y++){
					for (int x = 0; x < this->kernel_width; x++){
						if (y + j >= 0 && y + j < inputs[0].size() && x + k >= 0 && x + k < inputs[0][0].size()){
							//std::cout << inputs[i].size() << std::endl;
							//std::cout << "i=" << i << ",j=" << j << ",k=" << k << ",y=" << y << ",x=" << x << std::endl;
							std::cout << "i=" << i << ",j=" << j << ",k=" << k << ",y=" << y << ",x=" << x << std::endl;
							std::cout << "=================" << std::endl;
							std::cout << inputs.size() << std::endl;
							std::cout << inputs[i].size() << std::endl;
							std::cout << inputs[i][y+j].size() << std::endl;
							std::cout << inputs[i][y+j][x+k] << std::endl;
							std::cout << "=================" << std::endl;
							std::cout << this->filters.size() << std::endl;
							std::cout << this->filters[i].size() << std::endl;
							std::cout << this->filters[i][y].size() << std::endl;
							std::cout << this->filters[i][y][x] << std::endl;
							std::cout << "=================" << std::endl;
							total += inputs[i][y+j][x+k] * this->filters[i][y][x];
						}
					}
				}
				outputs[i].back().push_back(this->activation_function(total));
			}
		}
	}

	return outputs;
}

auto CNN::Layers::Conv2d::BackPropagate(std::vector<std::vector<std::vector<float>>>& previous_deltas) -> std::vector<std::vector<std::vector<float>>> {
	return previous_deltas;
}

//auto CNN::Layers::Conv2d::Attach(CNN::Layers::Layer& input_layer) -> void {
	//this->input_width = input_layer.output_width;
	//this->input_height = input_layer.output_height;
//}

//auto CNN::Layers::Conv2d::Attach(CNN::Layers::Input& input_layer) -> void {
	//this->input_width = input_layer.output_width;
	//this->input_height = input_layer.output_height;
	//input_layer.amount_of_filters = this->amount_of_filters;
//}

//CNN::Layers::MaxPool::MaxPool(CNN::Layers::Layer& input_layer, std::pair<int, int> kernel_size, int stride) {
	////this->input_height = input_layer.output_height;
	////this->input_width = input_layer.output_width;
	//this->kernel_width = kernel_size.first;
	//this->kernel_height = kernel_size.second;
	//this->stride = stride;
	////this->output_width = (this->input_width - this->kernel_width)/(this->stride) + 1;
	////this->output_height = (this->input_height - this->kernel_height)/(this->stride) + 1;
	////this->amount_of_filters = input_layer.amount_of_filters;
//}

CNN::Layers::MaxPool::MaxPool(std::pair<int, int> kernel_size, int stride) {
	this->kernel_width = kernel_size.first;
	this->kernel_height = kernel_size.second;
	this->stride = stride;
	//this->output_width = (this->input_width - this->kernel_width)/(this->stride) + 1;
	//this->output_height = (this->input_height - this->kernel_height)/(this->stride) + 1;
}

CNN::Layers::MaxPool::~MaxPool(){}

auto CNN::Layers::MaxPool::Activate(std::vector<std::vector<std::vector<float>>>& inputs) -> std::vector<std::vector<std::vector<float>>> {

	std::cout << "MaxPool::Activate()" << std::endl;
	this->ReportDims();

	std::vector<std::vector<std::vector<float>>> outputs;

	float max, min_float = -std::numeric_limits<float>::max();
	for (int i = 0; i < inputs.size(); i++){
		outputs.push_back(std::vector<std::vector<float>>());

		for (int j = 0; j + this->kernel_height <= inputs[0].size(); j+=this->stride){
			outputs[i].push_back(std::vector<float>());
			max = min_float;
			for (int k = 0; k + this->kernel_width <= inputs[0][0].size(); k+=this->stride){
				for (int y = 0; y < this->kernel_height; y++){
					for (int x = 0; x < this->kernel_width; x++){
						max = std::fmax(max, inputs[i][y+j][x+k]);
					}
				}
				outputs[i].back().push_back(max);
			}
		}
	}

	return outputs;
}

auto CNN::Layers::MaxPool::BackPropagate(std::vector<std::vector<std::vector<float>>>& previous_deltas) -> std::vector<std::vector<std::vector<float>>> {
	return previous_deltas;
}

//auto CNN::Layers::MaxPool::Attach(CNN::Layers::Layer& input_layer) -> void {
	//this->input_height = input_layer.output_height;
	//this->input_width = input_layer.output_width;
	//this->amount_of_filters = input_layer.amount_of_filters;
//}

//auto CNN::Layers::MaxPool::Attach(CNN::Layers::Input& input_layer) -> void {
	//std::cout << "A MaxPool layer cannot be added after an Input Layer (CNN.cpp:)" << std::endl;
	//exit(1);
//}

CNN::Network::Network(){}
CNN::Network::~Network(){}

auto CNN::Network::AddLayer(CNN::Layers::Conv2d layer) -> void {
	//std::cout << "======================" << std::endl;
	//layer.ReportDims();
	//if (this->layers.size() == 0){
		//layer.Attach(this->input_layer);
	//} else {
		//layer.Attach(this->layers.back());
	//}
	//layer.ReportDims();
	//std::cout << "======================" << std::endl;
	this->layers.push_back(&layer);
}

auto CNN::Network::AddLayer(CNN::Layers::MaxPool layer) -> void {
	//if (this->layers.size() == 0){
		//layer.Attach(this->input_layer);
	//} else {
		//layer.Attach(this->layers.back());
	//}
	this->layers.push_back(&layer);
}

//auto CNN::Network::AddLayer(CNN::Layers::Input layer) -> void {
	//this->input_layer = std::move(layer);
	//std::cout << "INPUT LAYER DIMS: " << this->input_layer.input_width << "x" << this->input_layer.input_height << " -> " << this->input_layer.output_width << "x" << this->input_layer.output_height << std::endl;
//}

auto CNN::Network::Activate(std::vector<std::vector<float>>& input) -> std::vector<std::vector<std::vector<float>>> {
	std::vector<std::vector<std::vector<float>>> data;
	data.push_back(input);

	for (auto& layer : this->layers){
		data = layer.Activate(data);
	}

	return data;
}

auto CNN::Network::QueryLayerDims() -> void {
	for (auto& layer : this->layers){
		layer.ReportDims();
	}
}
