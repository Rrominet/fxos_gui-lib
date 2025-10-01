
#include "./Canvas_impl.h"
#include "../Canvas.h"
#include "cairomm/context.h"
#include "cairomm/fontface.h"
#include "cairomm/types.h"
#include <gdkmm.h>

namespace ml
{
    Canvas_impl::Canvas_impl(Canvas* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    void Canvas_impl::_createWidget()
    {
        _gtk = std::make_shared<Gtk::DrawingArea>();
        this->canvas()->set_can_focus(true);
        this->canvas()->set_focusable(true);

        auto gtk_draw = [this](const Cairo::RefPtr<Cairo::Context>& cr, int w, int h)
        {
            _cr = cr;
            _inside_draw = true;

            _cr->set_line_cap(Cairo::Context::LineCap::ROUND);
            if (_draw)   
                _draw(w, h);

            _inside_draw = false;
        };

        this->canvas()->set_draw_func(gtk_draw);
    }

    void Canvas_impl::_check_inside() const
    {
#ifdef mydebug
        if (!_inside_draw) 
        {
            lg("Error : executing a draw function outside of the draw handler. wrap in it a function and call ml::Canvas::addToDraws instead.");
            assert(false);
        }
#endif
    }

    void Canvas_impl::fillRect(int x, int y, int w, int h, const Color<double>& color)
    {
        _check_inside();
        _cr->set_source_rgba(color.r(), color.g(), color.b(), color.a()); // changed
        _cr->rectangle(x, y, w, h);
        _cr->fill();
    }

    void Canvas_impl::strokeRect(int x, int y, int w, int h, const Color<double>& color, double lineWidth)
    {
        _check_inside();
        _cr->set_source_rgba(color.r(), color.g(), color.b(), color.a());
        _cr->set_line_width(lineWidth);
        _cr->rectangle(x, y, w, h);
        _cr->stroke();
    }

    void Canvas_impl::fillArc(int x, int y, int radius, double startAngle, double endAngle, const Color<double>& color)
    {
        _check_inside();
        _cr->set_source_rgba(color.r(), color.g(), color.b(), color.a());
        _cr->arc(x, y, radius, startAngle, endAngle);
        _cr->fill();
    }

    void Canvas_impl::strokeArc(int x, int y, int radius, double startAngle, double endAngle, const Color<double>& color, double lineWidth)
    {
        _check_inside();
        _cr->set_source_rgba(color.r(), color.g(), color.b(), color.a());
        _cr->set_line_width(lineWidth);
        _cr->arc(x, y, radius, startAngle, endAngle);
        _cr->stroke();
    }

    void Canvas_impl::fillCircle(int x, int y, int radius, const Color<double>& color)
    {
        _check_inside();
        fillArc(x, y, radius, 0, 2 * M_PI, color);
    }

    void Canvas_impl::strokeCircle(int x, int y, int radius, const Color<double>& color, double lineWidth)
    {
        _check_inside();
        strokeArc(x, y, radius, 0, 2 * M_PI, color, lineWidth);
    }

    void Canvas_impl::drawLine(int x1, int y1, int x2, int y2, const Color<double>& color, double lineWidth)
    {
        _check_inside();
        _cr->set_source_rgba(color.r(), color.g(), color.b(), color.a());
        _cr->set_line_width(lineWidth);
        _cr->move_to(x1, y1);
        _cr->line_to(x2, y2);
        _cr->stroke();
    }

    void Canvas_impl::fillPolygon(const std::vector<std::pair<int, int>>& points, const Color<double>& color)
    {
        _check_inside();
        if (points.empty()) return;

        _cr->set_source_rgba(color.r(), color.g(), color.b(), color.a());
        _cr->move_to(points[0].first, points[0].second);

        for (size_t i = 1; i < points.size(); ++i) {
            _cr->line_to(points[i].first, points[i].second);
        }

        _cr->close_path();
        _cr->fill();
    }

    void Canvas_impl::strokePolygon(const std::vector<std::pair<int, int>>& points, const Color<double>& color, double lineWidth)
    {
        _check_inside();
        if (points.empty()) return;

        _cr->set_source_rgba(color.r(), color.g(), color.b(), color.a());
        _cr->set_line_width(lineWidth);
        _cr->move_to(points[0].first, points[0].second);

        for (size_t i = 1; i < points.size(); ++i) {
            _cr->line_to(points[i].first, points[i].second);
        }

        _cr->close_path();
        _cr->stroke();
    }

    TextMetrics Canvas_impl::textMetrics(const std::string& text, const TextStyle& style)
    {
        _check_inside();
        auto weight = Cairo::ToyFontFace::Weight::NORMAL;
        auto slant = Cairo::ToyFontFace::Slant::NORMAL;

        if (style.italic)
            slant = Cairo::ToyFontFace::Slant::ITALIC;
        else if (style.oblique)
            slant = Cairo::ToyFontFace::Slant::ITALIC;

        if (style.bold)
            weight =  Cairo::ToyFontFace::Weight::BOLD;

        _cr->select_font_face(style.family, slant, weight);
        _cr->set_font_size(style.size);

        Cairo::TextExtents _ex;
        _cr->get_text_extents(text, _ex);

        return{
            _ex.x_bearing,
            _ex.y_bearing,
            _ex.width,
            _ex.height,
            _ex.x_advance,
            _ex.y_advance
        };
    }

    void Canvas_impl::drawText(int x, int y, const std::string& text, const TextStyle& style, const Color<double>& color)
    {
        _check_inside();
        _cr->move_to(x, y);
        _cr->set_source_rgba(color.r(), color.g(), color.b(), color.a());
        auto slant = Cairo::ToyFontFace::Slant::NORMAL;
        auto weight = Cairo::ToyFontFace::Weight::NORMAL;

        if (style.italic)
            slant = Cairo::ToyFontFace::Slant::ITALIC;
        else if (style.oblique)
            slant = Cairo::ToyFontFace::Slant::ITALIC;

        if (style.bold)
            weight =  Cairo::ToyFontFace::Weight::BOLD;

        _cr->select_font_face(style.family, slant, weight);
        _cr->set_font_size(style.size);
        _cr->show_text(text);
    }

    void Canvas_impl::beginPath()
    {
        _check_inside();
        _cr->begin_new_path();
    }

    void Canvas_impl::closePath()
    {
        _check_inside();
        _cr->close_path();
    }

    void Canvas_impl::moveTo(int x, int y)
    {
        _check_inside();
        _cr->move_to(x, y);
    }

    void Canvas_impl::lineTo(int x, int y)
    {
        _check_inside();
        _cr->line_to(x, y);
    }

    void Canvas_impl::fill(const Color<double>& color)
    {
        _check_inside();
        _cr->set_source_rgba(color.r(), color.g(), color.b(), color.a());
        _cr->fill();
    }

    void Canvas_impl::stroke(const Color<double>& color, double lineWidth)
    {
        _check_inside();
        _cr->set_source_rgba(color.r(), color.g(), color.b(), color.a());
        _cr->set_line_width(lineWidth);
        _cr->stroke();
    }

    void Canvas_impl::arc(double x, double y, double radius, double startAngle, double endAngle)
    {
        _check_inside();
        _cr->arc(x, y, radius, startAngle, endAngle);
    }

    void Canvas_impl::drawImage(std::shared_ptr<Gdk::Pixbuf> px,int x,int y, int pivotx , int pivoty , float scaleX , float scaleY )
    {
        _check_inside();

        if (scaleX != 1 || scaleY != 1)
        {
            _cr->save();
            _cr->translate(x, y);
            _cr->scale(scaleX, scaleY);
            _cr->translate(-pivotx, -pivoty);
        }

        Gdk::Cairo::set_source_pixbuf(_cr, px, 0, 0);
        _cr->rectangle(x, y, px->get_width(), px->get_height());
        _cr->fill();

        if (scaleX != 1 || scaleY != 1)
            _cr->restore();
    }

    void Canvas_impl::drawImage(const std::string& path,int x,int y, int pivotx, int pivoty , float scaleX , float scaleY )
    {
        auto image = Gdk::Pixbuf::create_from_file(path);
        _imgs.push_back(image);
        auto f = [this, image, x, y, pivotx, pivoty, scaleX, scaleY](int, int)
        {
            lg("Drawing image !");
            this->drawImage(image, x, y, pivotx, pivoty, scaleX, scaleY);
        };

        ((ml::Canvas*)_abstract)->addToDraws(f);
    }
}

