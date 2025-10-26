#ifndef RELU_ACTIVATION_H
#define RELU_ACTIVATION_H

#include "../matrix.h"

class ReluActivation {

    private:
        Matrix output;

    public:
        ReluActivation();

        void forward(const Matrix& inputs);

        const Matrix& getOutput() const;
};

#endif 