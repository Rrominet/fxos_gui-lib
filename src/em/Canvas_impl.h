
#pragma once
#include "./em.h"
#include <memory>
#include "./Widget_impl.h"
#include "Color.h"
#include "../TextStyle.h"
#include "../TextMetrics.h"

namespace ml
{
    class Canvas;
    class Canvas_impl : public Widget_impl
    {
        public:
            Canvas_impl(Canvas* win);
            virtual ~Canvas_impl();

            virtual void _createWidget() override;

            void setDraw(const std::function<void (int , int)>& callback);

            // Rectangle operations
            void fillRect(int x, int y, int w, int h, const Color<double>& color);
            void strokeRect(int x, int y, int w, int h, const Color<double>& color, double lineWidth = 1.0);

            // Arc operations
            void fillArc(int x, int y, int radius, double startAngle, double endAngle, const Color<double>& color);
            void strokeArc(int x, int y, int radius, double startAngle, double endAngle, const Color<double>& color, double lineWidth = 1.0);

            // Circle operations
            void fillCircle(int x, int y, int radius, const Color<double>& color);
            void strokeCircle(int x, int y, int radius, const Color<double>& color, double lineWidth = 1.0);

            // Line operations
            void drawLine(int x1, int y1, int x2, int y2, const Color<double>& color, double lineWidth = 1.0);

            // Polygon operations
            void fillPolygon(const std::vector<std::pair<int, int>>& points, const Color<double>& color);
            void strokePolygon(const std::vector<std::pair<int, int>>& points, const Color<double>& color, double lineWidth = 1.0);
            // Text operations
            void drawText(int x, int y, const std::string& text, const TextStyle& style = {12.0, false, false, false, false, "sans-serif"}, const Color<double>& color = {1.0, 1.0, 1.0, 1.0});

            // Path operations
            void beginPath();
            void closePath();
            void moveTo(int x, int y);
            void lineTo(int x, int y);
            void fill(const Color<double>& color);
            void stroke(const Color<double>& color, double lineWidth = 1.0);
            void arc(double x, double y, double radius, double startAngle, double endAngle);

            TextMetrics textMetrics(const std::string& text, const TextStyle& style = {12.0, false, false, false, false, "sans-serif"});

            void drawImage(const std::string& path, int x, int y, int pivotx = 0, int pivoty = 0, float scaleX = 1.0, float scaleY = 1.0);
    };
}
