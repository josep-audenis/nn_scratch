#ifndef SOFTMAX_ACTIVATION_H
#define SOFTMAX_ACTIVATION_H

#include "../matrix.h"

class SoftmaxActivation {

    private:
        Matrix output_;

    public:
        SoftmaxActivation();

        void forward(const Matrix& inputs);

        const Matrix& getOutput() const;
};

#endif