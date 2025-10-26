#ifndef DENSE_LAYER_H
#define DENSE_LAYER_H

#include "../matrix.h"

class DenseLayer {
    private:
        Matrix inputs_;
        Matrix weights_;
        Matrix biases_;
        Matrix output_;

        Matrix dinputs_;
        Matrix dweights_;
        Matrix dbiases_;

    public:
        DenseLayer();
        DenseLayer(int n_inputs, int n_neurons);

        void forward(const Matrix& inputs);
        void backward(const Matrix& dvalues);

        const Matrix& getOuptut() const;
};

#endif