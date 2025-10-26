#include "../../include/loss/categorical_crossentropy_loss.h"

std::vector<double> CategoricalCrossentropyLoss::forward(const Matrix& y_pred, const Matrix& y_true) const {
    int samples = y_pred.getRows();

    Matrix y_pred_clipped = y_pred.clipped(1e-7, 1.0 - 1e-7);

    std::vector<double> correct_confidence(samples);

    if (y_true.getCols() == 1) {
        for (int i = 0; i < samples; i++) {
            int class_idx = static_cast<int>(y_true(i, 0));
            correct_confidence[i] = y_pred_clipped(0, class_idx);
        }
    } else {
        for (int i = 0; i < samples; i++) {
            double sum = 0.0;
            for (int j = 0; j < y_true.getCols(); j++) {
                sum += y_pred_clipped(i, j) * y_true(i, j);
            }
            correct_confidence[i] = sum;
        }
    }

    std::vector<double> losses(samples);
    for (int i = 0; i < samples; i++) {
        losses[i] = -std::log(correct_confidence[i]);
    }
    return losses;
}