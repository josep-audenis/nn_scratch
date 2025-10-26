#include "../../include/layers/dense_layer.h"

DenseLayer::DenseLayer() {}

DenseLayer::DenseLayer(int n_inputs, int n_neurons) {
    weights_ = 0.01 * Matrix::random(n_inputs, n_neurons);
    biases_ = Matrix::Matrix(1, n_neurons);
}

void DenseLayer::forward(const Matrix& inputs) {
    inputs_ = inputs;
    output_ = (inputs_ * weights_) + biases_;   
}

void DenseLayer::backward(const Matrix& dvalues) {
    dweights_ = inputs_.transpose() * dvalues;
    dbiases_ = dvalues.sumRows(); // TODO: verify if is sum rows or sum cols!!!
    dinputs_ = dvalues * weights_.transpose();
}

const Matrix& DenseLayer::getOuptut() const {
    return output_;
}