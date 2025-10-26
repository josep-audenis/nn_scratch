#ifndef CATEGORICAL_CROSSENTROPY_LOSS_H
#define CATEGORICAL_CROSSENTROPY_LOSS_H

#include "loss.h"

class CategoricalCrossentropyLoss : public Loss {
    public:
        std::vector<double> forward(const Matrix& y_pred, const Matrix& y_true) const override;
};

#endif