#include "CNNnew.h"
#include <iostream>

CNN::Layer::Layer(unsigned int type, unsigned int amount_of_filters, unsigned int stride, unsigned int kernel_width, unsigned int kernel_height, unsigned int width_padding, unsigned int height_padding, Activation::Activation_Function activation_function) {
	this->type = type;
	this->amount_of_filters = amount_of_filters;
	this->stride = stride;
	this->kernel_width = kernel_width;
	this->kernel_height = kernel_height;
	this->width_padding = width_padding;
	this->height_padding = height_padding;

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

	if (type == 0){
		for (int i = 0; i < this->amount_of_filters; i++){
			this->filters.push_back(std::vector<std::vector<float>>());
			for (int j = 0; j < this->kernel_height; j++){
				this->filters[i].push_back(std::vector<float>());
				for (int k = 0; k < this->kernel_width; k++){
					this->filters[i][j].push_back(((rand()%200)/1000)-0.1);
				}
			}
		}
	}
}

CNN::Layer::Layer(float dropout_rate){
	this->type = 2;
	this->dropout_rate = dropout_rate;
}

CNN::Layer::~Layer(){}

auto CNN::Layer::Activate(std::vector<std::vector<std::vector<float>>>& inputs) -> std::vector<std::vector<std::vector<float>>> {
	if (this->type == 0) return this->ActivateConv2d(inputs);
	else if (this->type == 1) return this->ActivateMaxPool(inputs);
	else if (this->type == 2) return this->ActivateDropout(inputs);
	else {
		std::cout << "Incorrect type" << std::endl;
		exit(1);
	}
}

auto CNN::Layer::ActivateConv2d(std::vector<std::vector<std::vector<float>>>& inputs) -> std::vector<std::vector<std::vector<float>>> {

	this->pre_values = inputs;

	while (inputs.size() > this-> amount_of_filters)
		inputs.pop_back();

	int inp = 0;
	this->original_input_size = inputs.size();
	while (this->amount_of_filters > inputs.size())
		inputs.push_back(inputs[(inp++)%this->original_input_size]);

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

auto CNN::Layer::ActivateMaxPool(std::vector<std::vector<std::vector<float>>>& inputs) -> std::vector<std::vector<std::vector<float>>> {

	std::vector<std::vector<std::vector<float>>> outputs;

	this->pre_values = inputs;

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

auto CNN::Layer::ActivateDropout(std::vector<std::vector<std::vector<float>>>& inputs) -> std::vector<std::vector<std::vector<float>>> {

	unsigned int amount_to_drop = static_cast<unsigned int>(this->dropout_rate * inputs.size());

	while (amount_to_drop > 0){
		inputs.erase(inputs.begin() + (rand() % inputs.size()));
		amount_to_drop--;
	}

	return inputs;
}

auto CNN::Layer::BackPropagate(std::vector<std::vector<std::vector<float>>>& previous_deltas) -> std::vector<std::vector<std::vector<float>>> {
	if (this->type == 0) return this->BackPropagateConv2d(previous_deltas);
	else if (this->type == 1) return this->BackPropagateMaxPool(previous_deltas);
	else if (this->type == 2) return this->BackPropagateDropout(previous_deltas);
	else {
		std::cout << "Incorrect type" << std::endl;
		exit(1);
	}
}

auto CNN::Layer::BackPropagateConv2d(std::vector<std::vector<std::vector<float>>>& previous_deltas) -> std::vector<std::vector<std::vector<float>>> {

	std::vector<std::vector<std::vector<float>>> change_weights;
	std::vector<std::vector<std::vector<float>>> deltas;

    for (int i = 0; i < this->pre_values.size(); i++) {
		deltas.push_back(std::vector<std::vector<float>>());
        for (int j = 0; j < this->pre_values[i].size(); j++) {
			deltas[i].push_back(std::vector<float>());
			for (int k = 0; k < this->pre_values[i][j].size(); k++){
				deltas[i][j].push_back(0);
			}
        }
    }

	for (int i = 0; i < this->filters.size(); i++){
		change_weights.push_back(std::vector<std::vector<float>>());
		for (int j = 0; j < this->filters[i].size(); j++){
			change_weights[i].push_back(std::vector<float>());
			for (int k = 0; k < this->filters[i][j].size(); k++){
				change_weights[i][j].push_back(0);
			}
		}
	}
	
	int newi;
	for (int i = 0; i < this->amount_of_filters; i++){
		if (i != 0){
			newi = this->pre_values.size() % i;
		} else {
			newi = 0;
		}
		for (int j = -this->height_padding; j + this->kernel_height < this->pre_values[newi].size() + this->height_padding; j+=this->stride){
			for (int k = -this->width_padding; k + this->kernel_width < this->pre_values[newi][j].size() + this->width_padding; j+=this->stride){
				for (int y = 0; y < this->kernel_height; y++){
					for (int x = 0; x < this->kernel_width; x++){
						if (j + y >= 0 && k + x >= 0 && j + y < this->pre_values[newi].size() && k + x < this->pre_values[newi][j].size()){
							change_weights[i][y][x] += previous_deltas[i][j + this->height_padding][k + this->width_padding] * this->pre_values[newi][j + y][k + x];
							deltas[newi][j + y][k + x] += this->filters[i][y][x] * previous_deltas[i][j + this->height_padding][k + this->width_padding];
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < this->filters.size(); i++){
		for (int y = 0; y < this->filters[i].size(); y++) {
			for (int x = 0; x < this->filters[i][y].size(); x++) {
				this->filters[i][y][x] = change_weights[i][y][x];
			}
		}
	}

    return deltas;
}

auto CNN::Layer::BackPropagateMaxPool(std::vector<std::vector<std::vector<float>>>& previous_deltas) -> std::vector<std::vector<std::vector<float>>> {
	return previous_deltas;
}

auto CNN::Layer::BackPropagateDropout(std::vector<std::vector<std::vector<float>>>& previous_deltas) -> std::vector<std::vector<std::vector<float>>> {
	return previous_deltas;
}

auto CNN::Layers::Conv2d(unsigned int amount_of_filters, std::pair<unsigned int, unsigned int> kernel_size, unsigned int stride, CNN::Padding padding, Activation::Activation_Function activation_function) -> CNN::Layer {

	unsigned int width_padding = 0;
	unsigned int height_padding = 0;

	switch (padding){
		case CNN::Padding::VALID:
			width_padding = 0;
			height_padding = 0;
			break;
		case CNN::Padding::SAME:
			width_padding = static_cast<int>(kernel_size.first / 2);
			height_padding = static_cast<int>(kernel_size.second / 2);
			break;
		case CNN::Padding::FULL:
			width_padding = kernel_size.first - 1;
			height_padding = kernel_size.second - 1;
			break;
	}

	return CNN::Layer(0, amount_of_filters, stride, kernel_size.first, kernel_size.second, width_padding, height_padding, activation_function);
}

auto CNN::Layers::MaxPool(std::pair<unsigned int, unsigned int> kernel_size, unsigned int stride) -> CNN::Layer {

	return CNN::Layer(1, 1, stride, kernel_size.first, kernel_size.second, 0, 0, Activation::Activation_Function::IDENTITY);
}

auto CNN::Layers::Dropout(float dropout_rate) -> CNN::Layer {
	return CNN::Layer(dropout_rate);
}

CNN::Network::Network(){}
CNN::Network::~Network(){}

auto CNN::Network::AddLayer(CNN::Layer layer) -> void {
	this->layers.push_back(std::move(layer));
}

auto CNN::Network::Activate(std::vector<std::vector<float>>& input) -> std::vector<std::vector<std::vector<float>>> {
	std::vector<std::vector<std::vector<float>>> data;
	data.push_back(input);

	for (auto& layer : this->layers){
		data = layer.Activate(data);
	}

	return data;
}

auto CNN::Network::BackPropagate(std::vector<std::vector<std::vector<float>>>& input) -> void {
	for (auto& layer : this->layers){
		input = layer.BackPropagate(input);
	}
}
