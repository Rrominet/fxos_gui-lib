#include "./Canvas.h"

namespace ml
{
    Canvas::Canvas() : Widget()
    {

    }

    void Canvas::init()
    {
        this->addCssClass("canvas");
        auto d = [this](int w, int h)
        {
            for (const auto& draw : _draws)
                draw(w, h);
        };

        this->canvas()->setDraw(d);
    }

    unsigned int Canvas::addToDraws(const std::function<void (int , int)>& callback)
    {
        _draws.push_back(callback);
        return _draws.size() - 1;
    }
    
    void Canvas::clearDraws()
    {
        _draws.clear();
    }

    bool Canvas::removeFromDraws(unsigned int index)
    {
        if (index < _draws.size())
        {
            _draws.erase(_draws.begin() + index);
            return true;
        }
        return false;
    }

    void Canvas::_roundedRectPath(int x, int y, int w, int h, int radius)
    {
        radius = std::min(radius, std::min(w / 2, h / 2));
        this->beginPath();
        this->moveTo(x + radius, y);
        this->lineTo(x + w - radius, y);
        this->arc(x + w - radius, y + radius, radius, -M_PI/2, 0);
        this->lineTo(x + w, y + h - radius);
        this->arc(x + w - radius, y + h - radius, radius, 0, M_PI/2);
        this->lineTo(x + radius, y + h);
        this->arc(x + radius, y + h - radius, radius, M_PI/2, M_PI);
        this->lineTo(x, y + radius);
        this->arc(x + radius, y + radius, radius, M_PI, -M_PI/2);
        this->closePath();
    }

    void Canvas::fillRoundedRect(int x,int y,int w,int h,int radius,const Color<double>& color)
    {
        _roundedRectPath(x, y, w, h, radius);
        this->fill(color);
    }


    void Canvas::strokeRoundedRect(int x, int y, int w, int h, int radius, const Color<double>& color, double lineWidth )
    {
        _roundedRectPath(x, y, w, h, radius);
        this->stroke(color, lineWidth);
    }

    void Canvas::drawText(int x,int y,const std::string& text,const TextStyle& style,const Color<double>& color)
    {
        auto m = this->textMetrics(text, style);
        x -= m.x_bearing;
        y -= m.y_bearing; //changed
        this->canvas()->drawText(x, y, text, style, color);
    }
}
