#include "CNN.hpp"
#include <cmath>
#include <iostream>

auto CNN::Sigmoid(float value) -> float { return 1.0 / (1 + exp(-value)); }

CNN::Convolution::Convolution(int method, int activation, int stride,
                              int padding,
                              std::vector<std::vector<float>> convolution) {
    this->method = method;
    this->activation = activation;
    this->stride = stride;
    this->convolution = convolution;
    if (this->padding == CNN_VALID) {
        this->padding = 0;
    } else if (this->padding == CNN_SAME) {
        this->padding = static_cast<int>(this->convolution.size() / 2);
    } else if (this->padding == CNN_FULL) {
        this->padding = this->convolution.size() - 1;
    }
}

CNN::Convolution::~Convolution() {}

auto CNN::Network::GetOutput() -> std::vector<float> {
	return this->neuralNet.GetOutput();
}

auto CNN::Convolution::Activate(
    std::vector<std::vector<float>> &previousFunctionOutput)
    -> std::vector<std::vector<float>> {
    std::vector<std::vector<float>> output;

    this->preFilterValues = previousFunctionOutput;

    std::vector<std::vector<float>> temp;
    float out;
    for (int y = -this->padding; y + this->convolution.size() <
                                 previousFunctionOutput.size() + this->padding;
         y += this->stride) {
        output.push_back(std::vector<float>());
        for (int x = -this->padding;
             x + this->convolution[0].size() <
             previousFunctionOutput[y].size() + this->padding;
             x += this->stride) {
            temp.clear();
            out = 0;
            for (int i = 0; i < this->convolution.size(); i++) {
                temp.push_back(std::vector<float>());
                for (int j = 0; j < this->convolution[i].size(); j++) {
                    if (i + y >= 0 && j + x >= 0 &&
                        i + y < previousFunctionOutput.size() &&
                        j + x < previousFunctionOutput[y].size()) {
                        temp[i].push_back(this->convolution[i][j] *
                                          previousFunctionOutput[y + i][x + j]);
                        if (i == 0 && j == 0) {
                            out = temp[i][j];
                        } else {
                            if (this->method == CNN_MIN) {
                                if (temp[i][j] < out)
                                    out = temp[i][j];
                            } else if (this->method == CNN_MAX) {
                                if (temp[i][j] > out)
                                    out = temp[i][j];
                            } else if (this->method == CNN_AVG) {
                                out += temp[i][j];
                            } else if (this->method == CNN_ADD) {
                                out += temp[i][j];
                            }
                        }
                    }
                }
            }

            if (this->method == CNN_AVG) {
                out /= temp.size() * temp[0].size();
            }

            if (this->activation == CNN_RELU) {
                out = out < 0.0 ? 0.0 : out;
            }

            output.back().push_back(out);
        }
    }

    return output;
}

auto CNN::Convolution::BackPropagate(
    std::vector<std::vector<float>> &previousDeltas)
    -> std::vector<std::vector<float>> {
    std::vector<std::vector<float>> changeWeights = this->convolution;
    std::vector<std::vector<float>> deltas = this->preFilterValues;

    for (int i = 0; i < this->preFilterValues.size(); i++) {
        for (int j = 0; j < this->preFilterValues[i].size(); j++) {
            deltas[i][j] = 0;
        }
    }

    for (int i = 0; i < this->convolution.size(); i++) {
        changeWeights.push_back(std::vector<float>());
        for (int j = 0; j < this->convolution[i].size(); j++) {
            changeWeights[i].push_back(0);
        }
    }

    for (int i = -this->padding; i + this->convolution.size() <
                                 this->preFilterValues.size() + this->padding;
         i += this->stride) {
        for (int j = -this->padding;
             j + this->convolution[0].size() <
             this->preFilterValues[i].size() + this->padding;
             j += this->stride) {
            for (int y = 0; y < this->convolution.size(); y++) {
                for (int x = 0; x < this->convolution[y].size(); x++) {
                    if (i + y >= 0 && j + x >= 0 &&
                        i + y < this->preFilterValues.size() &&
                        j + x < this->preFilterValues[i].size()) {
                        changeWeights[y][x] +=
                            previousDeltas[i + this->padding]
                                          [j + this->padding] *
                            this->preFilterValues[i + y][j + x];
                        deltas[i + y][j + x] +=
                            this->convolution[y][x] *
                            previousDeltas[i + this->padding]
                                          [j + this->padding];
                    }
                }
            }
        }
    }

    for (int y = 0; y < this->convolution.size(); y++) {
        for (int x = 0; x < this->convolution[y].size(); x++) {
            this->convolution[y][x] = changeWeights[y][x];
        }
    }

    return deltas;
}

auto CNN::Ones(int width, int height) -> std::vector<std::vector<float>> {
    std::vector<std::vector<float>> ones(height);
    std::vector<float> temp(width, 1.0);
    for (int i = 0; i < height; i++) {
        ones.push_back(temp);
    }
    return ones;
}

CNN::Network::Network(int inputWidth, int inputHeight) {
    this->inputWidth = inputWidth;
    this->inputHeight = inputHeight;
	this->outputShape = -1;

    this->layers.push_back(std::vector<CNN::Convolution>());
}

CNN::Network::~Network() {}

auto CNN::Network::Activate(std::vector<std::vector<float>> input) -> void {
    if (input.size() != this->inputHeight ||
        input[0].size() != this->inputWidth) {
        std::cout << "This image is not the correct size" << std::endl;
        exit(1);
    }

    std::vector<std::vector<std::vector<float>>> temp(this->layers[0].size(),
                                                      input);

    for (auto &layer : this->layers) {
        for (int i = 0; i < temp.size(); i++) {
            temp[i] = layer[i].Activate(temp[i]);
        }
    }

    std::vector<float> output;
    for (int i = 0; i < temp.size(); i++) {
        for (int j = 0; j < temp[i].size(); j++) {
            for (int k = 0; k < temp[i][j].size(); k++) {
                output.push_back(CNN::Sigmoid(temp[i][j][k]));
            }
        }
    }

    this->neuralNet.Fire(output);
    this->output = this->neuralNet.GetOutput();
}

auto CNN::Network::Activate(std::vector<float> input) -> void {
    std::vector<std::vector<float>> newInput;

    for (int i = 0; i < this->inputHeight; i++) {
        newInput.push_back(std::vector<float>());
        for (int j = 0; j < this->inputWidth; j++) {
            newInput[i].push_back(input[i * this->inputWidth + j]);
        }
    }

    this->Activate(newInput);
}

inline auto dReLU(float val) { return (val > 0 ? 1.0 : 0.0); }

auto CNN::Network::BackPropagate(std::vector<std::vector<float>> input,
                                 std::vector<float> target) -> void {
    this->Activate(input);
    this->neuralNet.BackPropagateDeltas(target);
    auto changeWeightsNN = this->neuralNet.BackPropagateWeights();

    std::vector<std::vector<std::vector<float>>> previousDeltas;
    std::vector<float> NNDeltas(this->outputShape, 0.0f);
    for (int i = 0; i < this->outputShape; i++) {
        for (int q = 0; q < this->neuralNet.layers[1].neurons.size(); ++q) {
            NNDeltas[i] +=
                this->neuralNet.layers[1].neurons[q].delta *
                dReLU(this->neuralNet.layers[1].neurons[q].valuePreSigmoid) *
                this->neuralNet.layers[1].neurons[q].weights[i];
        }
    }

    for (int i = 0, c = 0, index = this->layers.size() - 1;
         i < this->layers[index].size(); i++) {
        previousDeltas.push_back(std::vector<std::vector<float>>());
        for (int j = 0; j < this->layers[index][i].convolution.size(); j++) {
            previousDeltas[i].push_back(std::vector<float>());
            for (int k = 0; k < this->layers[index][i].convolution[j].size();
                 k++) {
                previousDeltas[i][j].push_back(NNDeltas[c++]);
            }
        }
    }

    for (int i = this->layers.size() - 2; i >= 0; i--) {
        for (int j = 0; j < this->layers[i].size(); j++) {
            previousDeltas[j] =
                this->layers[i][j].BackPropagate(previousDeltas[j]);
        }
    }

    for (int i = 1; i < this->neuralNet.layers.size(); i++) {
        for (int j = 0; j < this->neuralNet.layers[i].neurons.size(); j++) {
            for (int k = 0;
                 k < this->neuralNet.layers[i].neurons[j].weights.size(); k++) {
                this->neuralNet.layers[i].neurons[j].weights[k] +=
                    changeWeightsNN[i][j][k];
            }
        }
    }
}

// auto CNN::Network::BackPropagateDeltas(std::vector<float> target) -> void {
//     for (int i = this->layers.size() - 2; i > 0; i--) {
//         for (int j = 0; j < this->layers[i].neurons.size(); j++) {
//             this->neuralNet.layers[i].neurons[j].delta = 0;

//             for (int k = 0; k < this->neuralNet.layers[i + 1].neurons.size();
//                  k++) {
//                 this->neuralNet.layers[i].neurons[j].delta +=
//                     this->neuralNet.layers[i + 1].neurons[k].delta *
//                     this->neuralNet.SigmoidDerivative(
//                         this->neuralNet.layers[i + 1]
//                             .neurons[k]
//                             .valuePreSigmoid) *
//                     this->neuralNet.layers[i + 1].neurons[k].weights[j];
//             }
//         }
//     }
//     for (int i = this->layers.size() - 2; i >= 0; i--) {
//         for (int j = 0; j < this->layers[i].size(); j++) {
//         }
//     }
// }

// auto CNN::Network::BackPropagateWeights()
//     -> std::vector<std::vector<std::vector<std::vector<float>>>> {
//     std::vector<std::vector<std::vector<std::vector<float>>>> weightDeltas(
//         this->layers.size());

//     for (int i = 1; i < this->layers.size(); ++i) {
//         weightDeltas[i] =
//             std::vector<std::vector<float>>(this->layers[i].neurons.size());
//         for (int j = 0; j < this->layers[i].neurons.size(); j++) {
//             weightDeltas[i][j] =
//                 std::vector<float>(this->layers[i - 1].neurons.size());
//         }
//     }

//     for (int i = this->layers.size() - 1; i > 0; i--) {
//         for (int j = 0; j < this->layers[i].neurons.size(); j++) {
//             for (int k = 0; k < this->layers[i].neurons[j].weights.size();
//                  k++) {
//                 weightDeltas[i][j][k] =
//                     -this->learningRate * this->layers[i].neurons[j].delta *
//                     this->SigmoidDerivative(
//                         this->layers[i].neurons[j].valuePreSigmoid) *
//                     this->layers[i - 1].neurons[k].value;
//             }
//         }
//     }

//     return weightDeltas;
// }

auto CNN::Network::ConvolutionalLayer(int filters,
                                      std::pair<int, int> kernelSize,
                                      int stride, int method, int activation)
    -> void {
    for (int i = 0; i < filters; i++) {
        this->layers.back().push_back(
            CNN::Convolution(method, activation, stride, CNN_SAME,
                             this->GenerateConvolution(kernelSize)));
    }
}

auto CNN::Network::ConvolutionalLayer(int filters,
                                      std::pair<int, int> kernelSize,
                                      int stride, int padding, int method,
                                      int activation) -> void {
    for (int i = 0; i < filters; i++) {
        this->layers.back().push_back(
            CNN::Convolution(method, activation, stride, padding,
                             this->GenerateConvolution(kernelSize)));
    }
}

auto CNN::Network::GenerateConvolution(std::pair<int, int> kernelSize)
    -> std::vector<std::vector<float>> {
    std::vector<std::vector<float>> tmp;
    for (int i = 0; i < kernelSize.second; i++) {
        tmp.push_back(std::vector<float>());
        for (int j = 0; j < kernelSize.first; j++) {
            tmp[i].push_back(static_cast<float>(rand() % 100) / 100 - 0.5);
        }
    }
    return tmp;
}

auto CNN::Network::GenerateNeuralNet(std::vector<int> layers,
                                     float learningRate) -> void {
    layers.insert(layers.begin(), this->GetOutputShape());
    this->neuralNet = NeuralNet(layers, learningRate);
}

auto CNN::Network::GetOutputShape() -> int {

    if (this->outputShape == -1) {
        std::vector<std::vector<float>> input;
        for (int i = 0; i < this->inputHeight; i++) {
            input.push_back(std::vector<float>());
            for (int j = 0; j < this->inputWidth; j++) {
                input[i].push_back(0.0);
            }
        }

        std::vector<std::vector<std::vector<float>>> temp(
            this->layers[0].size(), input);

        for (auto &layer : this->layers) {
            for (int i = 0; i < temp.size(); i++) {
                temp[i] = layer[i].Activate(temp[i]);
            }
        }

        std::vector<float> output;
        for (int i = 0; i < temp.size(); i++) {
            for (int j = 0; j < temp[i].size(); j++) {
                for (int k = 0; k < temp[i][j].size(); k++) {
                    output.push_back(CNN::Sigmoid(temp[i][j][k]));
                }
            }
        }

        this->outputShape = output.size();
        return this->outputShape;
    } else {
        return this->outputShape;
    }
}
