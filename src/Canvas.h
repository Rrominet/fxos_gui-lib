#pragma once
#include "./Widget.h"
#include "TextMetrics.h"
#include "Color.h"

#include <memory>
#ifdef __EMSCRIPTEN__
#include "./em/Canvas_impl.h"
#else
#include "./gtk/Canvas_impl.h"
#endif

namespace ml
{
    class Canvas : public Widget
    {
        public : 
            Canvas();
            virtual ~Canvas() = default;
            virtual void init() override;

            std::shared_ptr<ml::Canvas_impl> canvas(){return std::static_pointer_cast<Canvas_impl>(_impl);}

            unsigned int addToDraws(const std::function<void (int , int)>& callback);
            void clearDraws();
            bool removeFromDraws(unsigned int index);

            void fillRect(int x, int y, int w, int h, const Color<double>& color)
            {canvas()->fillRect(x, y, w, h, color);}

            void strokeRect(int x, int y, int w, int h, const Color<double>& color, double lineWidth = 1.0)
            {canvas()->strokeRect(x, y, w, h, color, lineWidth);}

            // Arc operations
            void fillArc(int x, int y, int radius, double startAngle, double endAngle, const Color<double>& color)
            {canvas()->fillArc(x, y, radius, startAngle, endAngle, color);}

            void strokeArc(int x, int y, int radius, double startAngle, double endAngle, const Color<double>& color, double lineWidth = 1.0)
            {canvas()->strokeArc(x, y, radius, startAngle, endAngle, color, lineWidth);}

            // Circle operations
            void fillCircle(int x, int y, int radius, const Color<double>& color)
            {canvas()->fillCircle(x, y, radius, color);}

            void strokeCircle(int x, int y, int radius, const Color<double>& color, double lineWidth = 1.0)
            {canvas()->strokeCircle(x, y, radius, color, lineWidth);}

            // Line operations
            void drawLine(int x1, int y1, int x2, int y2, const Color<double>& color, double lineWidth = 1.0)
            {canvas()->drawLine(x1, y1, x2, y2, color, lineWidth);}

            // Polygon operations
            void fillPolygon(const std::vector<std::pair<int, int>>& points, const Color<double>& color)
            {canvas()->fillPolygon(points, color);}

            void strokePolygon(const std::vector<std::pair<int, int>>& points, const Color<double>& color, double lineWidth = 1.0)
            {canvas()->strokePolygon(points, color, lineWidth);}

            // Text operations
            // the x,y correspond to the left up corner of the text.
            void drawText(int x, int y, const std::string& text, const TextStyle& style = {12.0, false, false, false, false, "sans-serif"}, const Color<double>& color = {1.0, 1.0, 1.0, 1.0});

            // Path operations
            void beginPath()
            {canvas()->beginPath();}

            void closePath()
            {canvas()->closePath();}

            void moveTo(int x, int y)
            {canvas()->moveTo(x, y);}

            void lineTo(int x, int y)
            {canvas()->lineTo(x, y);}

            void fill(const Color<double>& color)
            {canvas()->fill(color);}

            void stroke(const Color<double>& color, double lineWidth = 1.0)
            {canvas()->stroke(color, lineWidth);}

            void arc(double x, double y, double radius, double startAngle, double endAngle)
            {canvas()->arc(x, y, radius, startAngle, endAngle);}

            void fillRoundedRect(int x, int y, int w, int h, int radius, const Color<double>& color);
            void strokeRoundedRect(int x, int y, int w, int h, int radius, const Color<double>& color, double lineWidth = 1.0);

            TextMetrics textMetrics(const std::string& text, const TextStyle& style = {12.0, false, false, false, false, "sans-serif"})
            {return canvas()->textMetrics(text, style);}

            void drawImage(const std::string& path,int x,int y,int pivotx = 0, int pivoty = 0, float scaleX = 1.0, float scaleY = 1.0 )
            {canvas()->drawImage(path,x,y, pivotx, pivoty, scaleX, scaleY);}

        protected : 
            std::vector<std::function<void (int , int)>> _draws;

            void _roundedRectPath(int x, int y, int w, int h, int radius);
    };


}
