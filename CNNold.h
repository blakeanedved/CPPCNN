#ifndef _CNN_HPP_
#define _CNN_HPP_
#include "NeuralNet.hpp"
#include <vector>

#define CNN_NONE 0
#define CNN_VALID 1
#define CNN_SAME 2
#define CNN_FULL 3
#define CNN_MIN 10
#define CNN_MAX 11
#define CNN_AVG 12
#define CNN_ADD 13
#define CNN_RELU 20


namespace CNN {
class NeuralNet;

class Network;

class Convolution {
  private:
    int type, method, stride, padding, activation;
    std::vector<std::vector<float>> convolution;
    std::vector<std::vector<float>> preFilterValues;
    friend class Network;

  public:
    Convolution(int method, int activation, int stride, int padding,
                std::vector<std::vector<float>> convolution);
    ~Convolution();

    auto Activate(std::vector<std::vector<float>> &previousFunctionOutput)
        -> std::vector<std::vector<float>>;
    auto BackPropagate(std::vector<std::vector<float>> &previousDeltas)
        -> std::vector<std::vector<float>>;

  private:
    auto GeneratePadding(std::vector<std::vector<float>> &image) -> void;
};

class Network {
  private:
    int inputWidth, inputHeight, outputShape;
    std::vector<std::vector<CNN::Convolution>> layers;
    std::vector<float> output;
    NeuralNet neuralNet;

  public:
    Network(int inputWidth, int inputHeight);
    ~Network();

	auto GetOutput() -> std::vector<float>;
    auto BackPropagate(std::vector<std::vector<float>> input,
                       std::vector<float> output) -> void;
    // auto Fire(std::vector<std::vector<unsigned char>> &input)
    // ->std::vector<float>;
    auto Activate(std::vector<std::vector<float>> input) -> void;
    auto Activate(std::vector<float> input) -> void;
    // auto Fire(std::vector<unsigned char> &input) -> std::vector<float>;
    // auto NextLayer() -> void;
    // auto AddConvolution(CNN::Convolution &convolution) -> void;
    auto ConvolutionalLayer(int filters, std::pair<int, int> kernelSize,
                            int stride, int method, int activation) -> void;
    auto ConvolutionalLayer(int filters, std::pair<int, int> kernelSize,
                            int stride, int padding, int method, int activation)
        -> void;

    // auto AddConvolution(int method, int activation, int stride, int padding,
    // std::vector<std::vector<float>> convolution) -> void;
    auto GenerateNeuralNet(std::vector<int> layers, float learningRate) -> void;
    auto GetOutputShape() -> int;

  private:
    auto GenerateConvolution(std::pair<int, int> kernelSize)
        -> std::vector<std::vector<float>>;
    // auto BackPropagateDeltas(std::vector<float> target) -> void;
    // auto
    // BackPropagateWeights()->std::vector<std::vector<std::vector<std::vector<float>>>>;
};

auto Ones(int width, int height) -> std::vector<std::vector<float>>;
auto Sigmoid(float value) -> float;
}; // namespace CNN

#endif
