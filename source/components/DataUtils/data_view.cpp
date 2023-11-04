#include <cmath>
#include "components/DataUtils/data_view.h"
#include "components/DataUtils/utils.h"

DataView::DataView(DataPool* dataPool, float sample = 1.0){
    this->dataPool = dataPool;

    long train_size = (long) std::lround(this->dataPool->num_train() * sample);
    long val_size = (long) std::lround(this->dataPool->num_val() * sample);

    this->train_indices = rand_perm(train_size);
    this->val_indices = rand_perm(val_size);
}

ArrayXXf DataView::X_train() {
    return this->dataPool->X_train(this->train_indices, Eigen::all);
}

ArrayXXf DataView::X_val() {
    return this->dataPool->X_val(this->val_indices, Eigen::all);
}


ArrayXf DataView::y_val() {
    return this->dataPool->y_val(this->val_indices);
}

ArrayXf DataView::y_train() {
    return this->dataPool->y_train(this->train_indices);
}