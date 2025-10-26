#ifndef RELU_ACTIVATION_H
#define RELU_ACTIVATION_H

#include "../matrix.h"

class ReluActivation {

    private:
        Matrix inputs_;
        Matrix output_;

        Matrix dinputs_;

    public:
        ReluActivation();

        void forward(const Matrix& inputs);
        void backward(const Matrix& inputs);

        const Matrix& getOutput() const;
};

#endif 