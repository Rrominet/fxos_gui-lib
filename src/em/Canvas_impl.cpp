
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

    //TODO : I'm here.
    void Canvas_impl::setDraw(const std::function<void (int , int)>& callback)
    {

    }

    void Canvas_impl::fillRect(int x,int y,int w,int h,const Color<double>& color)
    {

    }

    void Canvas_impl::strokeRect(int x,int y,int w,int h,const Color<double>& color,double lineWidth)
    {

    }

    void Canvas_impl::fillArc(int x,int y,int radius,double startAngle,double endAngle,const Color<double>& color)
    {

    }

    void Canvas_impl::strokeArc(int x,int y,int radius,double startAngle,double endAngle,const Color<double>& color,double lineWidth)
    {

    }

    void Canvas_impl::fillCircle(int x,int y,int radius,const Color<double>& color)
    {

    }

    void Canvas_impl::strokeCircle(int x,int y,int radius,const Color<double>& color,double lineWidth)
    {

    }

    void Canvas_impl::drawLine(int x1,int y1,int x2,int y2,const Color<double>& color,double lineWidth)
    {

    }

    void Canvas_impl::fillPolygon(const std::vector<std::pair<int,int>>& points,const Color<double>& color)
    {

    }

    void Canvas_impl::strokePolygon(const std::vector<std::pair<int,int>>& points,const Color<double>& color,double lineWidth)
    {

    }

    void Canvas_impl::drawText(int x,int y,const std::string& text,const TextStyle& style,const Color<double>& color)
    {

    }

    void Canvas_impl::beginPath()
    {

    }

    void Canvas_impl::closePath()
    {

    }

    void Canvas_impl::moveTo(int x,int y)
    {

    }

    void Canvas_impl::lineTo(int x,int y)
    {

    }

    void Canvas_impl::fill(const Color<double>& color)
    {

    }

    void Canvas_impl::stroke(const Color<double>& color,double lineWidth)
    {

    }

    void Canvas_impl::arc(double x,double y,double radius,double startAngle,double endAngle)
    {

    }

    TextMetrics Canvas_impl::textMetrics(const std::string& text,const TextStyle& style)
    {

    }

    void Canvas_impl::drawImage(const std::string& path,int x,int y,int pivotx,int pivoty,float scaleX,float scaleY)
    {

    }
}
