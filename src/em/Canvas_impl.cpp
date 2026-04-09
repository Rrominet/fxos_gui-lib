
#include "./Canvas_impl.h"
#include "../Canvas.h"

namespace ml
{
    Canvas_impl::Canvas_impl(Canvas* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    Canvas_impl::~Canvas_impl()
    {
    }

    void Canvas_impl::_createWidget()
    {
        auto domWidget = em::createElement("canvas");
        _dom = std::make_shared<emval>(domWidget);
        (*_dom)["classList"].call<void, std::string>("add", "canvas");
    }

    static std::string _colorToCss(const Color<double>& color)
    {
        int r = (int)(color.r() * 255);
        int g = (int)(color.g() * 255);
        int b = (int)(color.b() * 255);
        double a = color.a();
        return "rgba(" + std::to_string(r) + "," + std::to_string(g) + "," + std::to_string(b) + "," + std::to_string(a) + ")";
    }

    void Canvas_impl::setDraw(const std::function<void(int, int)>& callback)
    {
        _draw = callback;
        _ctx = std::make_shared<emval>((*_dom).call<emval>("getContext", std::string("2d")));
    }

    void Canvas_impl::redraw()
    {
        if (!_ctx || !_draw)
            return;
        int w = (*_dom)["width"].as<int>();
        int h = (*_dom)["height"].as<int>();
        _draw(w, h);
    }

    emval& Canvas_impl::ctx()
    {
        if (!_ctx)
            _ctx = std::make_shared<emval>((*_dom).call<emval>("getContext", std::string("2d")));
        return *_ctx;
    }

    void Canvas_impl::fillRect(int x, int y, int w, int h, const Color<double>& color)
    {
        ctx().set("fillStyle", _colorToCss(color));
        ctx().call<void>("fillRect", x, y, w, h);
    }

    void Canvas_impl::strokeRect(int x, int y, int w, int h, const Color<double>& color, double lineWidth)
    {
        ctx().set("strokeStyle", _colorToCss(color));
        ctx().set("lineWidth", lineWidth);
        ctx().call<void>("strokeRect", x, y, w, h);
    }

    void Canvas_impl::fillArc(int x, int y, int radius, double startAngle, double endAngle, const Color<double>& color)
    {
        ctx().set("fillStyle", _colorToCss(color));
        ctx().call<void>("beginPath");
        ctx().call<void>("arc", x, y, radius, startAngle, endAngle);
        ctx().call<void>("fill");
    }

    void Canvas_impl::strokeArc(int x, int y, int radius, double startAngle, double endAngle, const Color<double>& color, double lineWidth)
    {
        ctx().set("strokeStyle", _colorToCss(color));
        ctx().set("lineWidth", lineWidth);
        ctx().call<void>("beginPath");
        ctx().call<void>("arc", x, y, radius, startAngle, endAngle);
        ctx().call<void>("stroke");
    }

    void Canvas_impl::fillCircle(int x, int y, int radius, const Color<double>& color)
    {
        this->fillArc(x, y, radius, 0, 2 * M_PI, color);
    }

    void Canvas_impl::strokeCircle(int x, int y, int radius, const Color<double>& color, double lineWidth)
    {
        this->strokeArc(x, y, radius, 0, 2 * M_PI, color, lineWidth);
    }

    void Canvas_impl::drawLine(int x1, int y1, int x2, int y2, const Color<double>& color, double lineWidth)
    {
        ctx().set("strokeStyle", _colorToCss(color));
        ctx().set("lineWidth", lineWidth);
        ctx().call<void>("beginPath");
        ctx().call<void>("moveTo", x1, y1);
        ctx().call<void>("lineTo", x2, y2);
        ctx().call<void>("stroke");
    }

    void Canvas_impl::fillPolygon(const std::vector<std::pair<int, int>>& points, const Color<double>& color)
    {
        if (points.empty()) return;
        ctx().set("fillStyle", _colorToCss(color));
        ctx().call<void>("beginPath");
        ctx().call<void>("moveTo", points[0].first, points[0].second);
        for (size_t i = 1; i < points.size(); i++)
            ctx().call<void>("lineTo", points[i].first, points[i].second);
        ctx().call<void>("closePath");
        ctx().call<void>("fill");
    }

    void Canvas_impl::strokePolygon(const std::vector<std::pair<int, int>>& points, const Color<double>& color, double lineWidth)
    {
        if (points.empty()) return;
        ctx().set("strokeStyle", _colorToCss(color));
        ctx().set("lineWidth", lineWidth);
        ctx().call<void>("beginPath");
        ctx().call<void>("moveTo", points[0].first, points[0].second);
        for (size_t i = 1; i < points.size(); i++)
            ctx().call<void>("lineTo", points[i].first, points[i].second);
        ctx().call<void>("closePath");
        ctx().call<void>("stroke");
    }

    void Canvas_impl::drawText(int x, int y, const std::string& text, const TextStyle& style, const Color<double>& color)
    {
        std::string fontStr = "";
        if (style.italic) fontStr += "italic ";
        if (style.oblique) fontStr += "oblique ";
        if (style.bold) fontStr += "bold ";
        fontStr += std::to_string((int)style.size) + "px " + style.family;

        ctx().set("font", fontStr);
        ctx().set("fillStyle", _colorToCss(color));
        ctx().call<void>("fillText", text, x, y);
    }

    void Canvas_impl::beginPath()
    {
        ctx().call<void>("beginPath");
    }

    void Canvas_impl::closePath()
    {
        ctx().call<void>("closePath");
    }

    void Canvas_impl::moveTo(int x, int y)
    {
        ctx().call<void>("moveTo", x, y);
    }

    void Canvas_impl::lineTo(int x, int y)
    {
        ctx().call<void>("lineTo", x, y);
    }

    void Canvas_impl::fill(const Color<double>& color)
    {
        ctx().set("fillStyle", _colorToCss(color));
        ctx().call<void>("fill");
    }

    void Canvas_impl::stroke(const Color<double>& color, double lineWidth)
    {
        ctx().set("strokeStyle", _colorToCss(color));
        ctx().set("lineWidth", lineWidth);
        ctx().call<void>("stroke");
    }

    void Canvas_impl::arc(double x, double y, double radius, double startAngle, double endAngle)
    {
        ctx().call<void>("arc", x, y, radius, startAngle, endAngle);
    }

    TextMetrics Canvas_impl::textMetrics(const std::string& text, const TextStyle& style)
    {
        std::string fontStr = "";
        if (style.italic) fontStr += "italic ";
        if (style.oblique) fontStr += "oblique ";
        if (style.bold) fontStr += "bold ";
        fontStr += std::to_string((int)style.size) + "px " + style.family;

        ctx().set("font", fontStr);
        emval metrics = ctx().call<emval>("measureText", text);

        TextMetrics _r;
        _r.width = metrics["width"].as<double>();
        _r.height = style.size;
        _r.x_bearing = -metrics["actualBoundingBoxLeft"].as<double>();
        _r.y_bearing = -metrics["actualBoundingBoxAscent"].as<double>();
        _r.x_advance = metrics["width"].as<double>();
        _r.y_advance = 0;
        return _r;
    }

    void Canvas_impl::drawImage(const std::string& path, int x, int y, int pivotx, int pivoty, float scaleX, float scaleY)
    {
        std::string canvasId = (*_dom)["id"].as<std::string>();
        std::string js =
            std::string("(function(){")
            + std::string("var img=new Image();")
            + std::string("img.onload=function(){")
            + std::string("var c=document.getElementById('") + canvasId + std::string("');")
            + std::string("if(!c)return;")
            + std::string("var ctx=c.getContext('2d');")
            + std::string("ctx.save();")
            + std::string("ctx.translate(") + std::to_string(x) + std::string(",") + std::to_string(y) + std::string(");")
            + std::string("ctx.scale(") + std::to_string(scaleX) + std::string(",") + std::to_string(scaleY) + std::string(");")
            + std::string("ctx.drawImage(img,") + std::to_string(-pivotx) + std::string(",") + std::to_string(-pivoty) + std::string(");")
            + std::string("ctx.restore();")
            + std::string("};")
            + std::string("img.src='") + path + std::string("';")
            + std::string("})();");
        emval::global("eval")(js);
    }
}
