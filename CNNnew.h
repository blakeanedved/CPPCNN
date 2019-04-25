#ifndef _CNN_H_
#define _CNN_H_
#include "NeuralNet.h"
#include "ActivationFunctions.h"
#include <vector>
#include <functional>

namespace CNN {
	
	enum class Padding { SAME, VALID, FULL };

	class Network;
	
	class Layer {
		friend Network;
		protected:
			unsigned int kernel_width, kernel_height, stride, amount_of_filters, width_padding, height_padding, type, original_input_size;
			float dropout_rate;
			std::vector<std::vector<std::vector<float>>> filters;
			std::vector<std::vector<std::vector<float>>> pre_values;
			std::function<float(float)> activation_function;
			std::function<float(float)> activation_function_derivative;

		public:
			Layer(unsigned int type, unsigned int amount_of_filters, unsigned int stride, unsigned int kernel_width, unsigned int kernel_height, unsigned int width_padding, unsigned int height_padding, Activation::Activation_Function activation_function);
			Layer(float dropout_rate);
			~Layer();

			auto Activate(std::vector<std::vector<std::vector<float>>>& inputs) -> std::vector<std::vector<std::vector<float>>>;
			auto ActivateConv2d(std::vector<std::vector<std::vector<float>>>& inputs) -> std::vector<std::vector<std::vector<float>>>;
			auto ActivateMaxPool(std::vector<std::vector<std::vector<float>>>& inputs) -> std::vector<std::vector<std::vector<float>>>;
			auto ActivateDropout(std::vector<std::vector<std::vector<float>>>& inputs) -> std::vector<std::vector<std::vector<float>>>;

			auto BackPropagate(std::vector<std::vector<std::vector<float>>>& previous_deltas) -> std::vector<std::vector<std::vector<float>>>;
			auto BackPropagateConv2d(std::vector<std::vector<std::vector<float>>>& previous_deltas) -> std::vector<std::vector<std::vector<float>>>;
			auto BackPropagateMaxPool(std::vector<std::vector<std::vector<float>>>& previous_deltas) -> std::vector<std::vector<std::vector<float>>>;
			auto BackPropagateDropout(std::vector<std::vector<std::vector<float>>>& previous_deltas) -> std::vector<std::vector<std::vector<float>>>;
	};

	namespace Layers {
		
		auto Conv2d(unsigned int amount_of_filters, std::pair<unsigned int, unsigned int> kernel_size, unsigned int stride, CNN::Padding padding, Activation::Activation_Function activation_function) -> CNN::Layer;

		auto MaxPool(std::pair<unsigned int, unsigned int> kernel_size, unsigned int stride) -> CNN::Layer;

		auto Dropout(float dropout_rate) -> CNN::Layer;

	}

	class Network {
		protected:
			std::vector<CNN::Layer> layers;
		public:
			Network();
			~Network();

			auto AddLayer(CNN::Layer layer) -> void;

			auto Activate(std::vector<std::vector<float>>& input) -> std::vector<std::vector<std::vector<float>>>;
			auto BackPropagate(std::vector<std::vector<std::vector<float>>>& data) -> void;

			auto QueryLayerDims() -> void;
	};

}
#endif
