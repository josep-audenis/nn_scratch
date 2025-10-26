#include "../../include/layers/dense_layer.h"

DenseLayer::DenseLayer() {}

DenseLayer::DenseLayer(int n_inputs, int n_neurons) {
    weights = 0.01 * Matrix::random(n_inputs, n_neurons);
    biases = Matrix::Matrix(1, n_neurons);
}

void DenseLayer::forward(const Matrix& inputs) {
    output = (inputs * weights) + biases;   
}

const Matrix& DenseLayer::getOuptut() const {
    return output;
}