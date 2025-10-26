#include "../../include/activations/relu_activation.h"

ReluActivation::ReluActivation() {}

void ReluActivation::forward(const Matrix& inputs) {
    inputs_ = inputs;
    output_ = inputs.maximum(0);
}

void ReluActivation::backward(const Matrix& dvalues) {
    dinputs_ = dvalues;
    for (int i = 0; i < inputs_.getRows(); i++) {
        for (int j = 0; j < inputs_.getCols(); j++) {
            if (inputs_(i, j) <= 0) {
                dinputs_(i, j) = 0;
            }
        }
    }
}

const Matrix& ReluActivation::getOutput() const {
    return output_;
}