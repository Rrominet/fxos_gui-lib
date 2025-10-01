
#include "./ProgressBar.h"

namespace ml
{
    ProgressBar::ProgressBar() : Input()
    {

    }
    void ProgressBar::init()
    {
        this->addCssClass("progressBar");
    }

    void ProgressBar::setRange(double min,double max)
    {
        _min = min;
        _max = max;
    }

    void ProgressBar::setValue(double value)
    {
        value = (value - _min)/(_max-_min);
        this->progressBar()->setValue(value);
    }

}
