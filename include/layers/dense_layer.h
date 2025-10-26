#ifndef DENSE_LAYER_H
#define DENSE_LAYER_H

#include "../matrix.h"

class DenseLayer {
    private:
        Matrix weights;
        Matrix biases;
        Matrix output;

    public:
        DenseLayer();
        DenseLayer(int n_inputs, int n_neurons);

        void forward(const Matrix& inputs);

        const Matrix& getOuptut() const;
};

#endif