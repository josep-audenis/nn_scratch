#include "../../include/activations/softmax_activation.h"

SoftmaxActivation::SoftmaxActivation() {}

void SoftmaxActivation::forward(const Matrix& inputs) {
    Matrix exp_values = (inputs - inputs.maxRows()).exp();
    output_ = exp_values / exp_values.sumRows();
}

const Matrix& SoftmaxActivation::getOutput() const {
    return output_;
}