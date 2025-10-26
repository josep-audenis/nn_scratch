#include "../../include/loss/loss.h"

double Loss::calculate(const Matrix& y_pred, const Matrix& y_true) const {
    std::vector<double> sample_losses = forward(y_pred, y_true);
    double sum = std::accumulate(sample_losses.begin(), sample_losses.end(), 0.0);
    return sum / static_cast<double>(sample_losses.size());
}