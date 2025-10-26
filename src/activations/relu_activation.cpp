#include "../../include/activations/relu_activation.h"

ReluActivation::ReluActivation() {}

void ReluActivation::forward(const Matrix& inputs) {
    output = inputs.maximum(0);
}

const Matrix& ReluActivation::getOutput() const {
    return output;
}



