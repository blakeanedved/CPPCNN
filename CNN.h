#ifndef _CNN_H_
#define _CNN_H_
#include "NeuralNet.h"
#include "ActivationFunctions.h"
#include <vector>
#include <functional>
#include <boost/ptr_container/ptr_vector.hpp>

namespace CNN {
	
	enum class Padding { SAME, VALID, FULL };

	class Network;

	namespace Layers {

		class Conv2d;
		class MaxPool;

		//class Input {
			//friend Network;
			//friend Conv2d;
			//protected:
				//unsigned int input_width, input_height, amount_of_filters, output_width, output_height;
			//public:
				//Input(std::pair<unsigned int, unsigned int> input_size);
				//Input(std::pair<unsigned int, unsigned int> input_size, std::pair<unsigned int, unsigned int> resized_dimensions);
				//~Input();
				//auto Activate(std::vector<std::vector<float>>& inputs) -> std::vector<std::vector<std::vector<float>>>;
		//};

		class Layer {
			friend Network;
			friend Conv2d;
			friend MaxPool;
			protected:
				unsigned int kernel_width, kernel_height, stride, input_width, input_height, output_width, output_height, amount_of_filters;
				std::vector<std::vector<std::vector<float>>> filters;

			public:
				Layer();
				virtual ~Layer() = default;
				virtual auto Activate(std::vector<std::vector<std::vector<float>>>& inputs) -> std::vector<std::vector<std::vector<float>>> = 0;
				virtual auto BackPropagate(std::vector<std::vector<std::vector<float>>>& previous_deltas) -> std::vector<std::vector<std::vector<float>>> = 0;
				//virtual auto Attach(CNN::Layers::Layer& input_layer) -> void = 0;
				//virtual auto Attach(CNN::Layers::Input& input_layer) -> void = 0;
				auto ReportDims() -> void;
		};

		class Conv2d: public Layer {
			protected:
				unsigned int width_padding, height_padding;
				std::vector<std::vector<std::vector<float>>> filters;
				std::function<float(float)> activation_function;
				std::function<float(float)> activation_function_derivative;
			public:
				//Conv2d(CNN::Layers::Layer& input_layer, int filters, std::pair<int, int> kernel_size, int stride, Padding padding, Activation::Activation_Function activation_function);
				//Conv2d(CNN::Layers::Input& input_layer, int filters, std::pair<int, int> kernel_size, int stride, Padding padding, Activation::Activation_Function activation_function);
				Conv2d(int filters, std::pair<int, int> kernel_size, int stride, Padding padding, Activation::Activation_Function activation_function);
				~Conv2d();
				auto Activate(std::vector<std::vector<std::vector<float>>>& inputs) -> std::vector<std::vector<std::vector<float>>> override;
				auto BackPropagate(std::vector<std::vector<std::vector<float>>>& previous_deltas) -> std::vector<std::vector<std::vector<float>>> override;
				//auto Attach(CNN::Layers::Layer& input_layer) -> void override;
				//auto Attach(CNN::Layers::Input& input_layer) -> void override;
		};

		class MaxPool: public Layer {
			public:
				//MaxPool(CNN::Layers::Layer& input_layer, std::pair<int, int> kernel_size, int stride);
				MaxPool(std::pair<int, int> kernel_size, int stride);
				~MaxPool();
				auto Activate(std::vector<std::vector<std::vector<float>>>& inputs) -> std::vector<std::vector<std::vector<float>>> override;
				auto BackPropagate(std::vector<std::vector<std::vector<float>>>& previousDeltas) -> std::vector<std::vector<std::vector<float>>> override;
				//auto Attach(CNN::Layers::Layer& input_layer) -> void override;
				//auto Attach(CNN::Layers::Input& input_layer) -> void override;
		};

	}

	class Network {
		protected:
			//CNN::Layers::Input input_layer;
			boost::ptr_vector<CNN::Layers::Layer> layers;
		public:
			Network();
			~Network();

			auto AddLayer(CNN::Layers::Conv2d layer) -> void;
			auto AddLayer(CNN::Layers::MaxPool layer) -> void;
			//auto AddLayer(CNN::Layers::Input layer) -> void;

			auto Activate(std::vector<std::vector<float>>& input) -> std::vector<std::vector<std::vector<float>>>;

			auto QueryLayerDims() -> void;
	};

}
#endif
