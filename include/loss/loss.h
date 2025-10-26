#ifndef LOSS_H
#define LOSS_H

#include "../matrix.h"

class Loss {
    public:
        virtual ~Loss() = default;
        virtual std::vector<double> forward(const Matrix& y_pred, const Matrix& y_true) const = 0;

        double calculate(const Matrix& y_pred, const Matrix& y_true) const;
};

#endif