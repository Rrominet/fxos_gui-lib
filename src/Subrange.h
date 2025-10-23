#pragma once
#include "./ComposedWidget.h"
#include "vec.h"

namespace ml
{
    class Box;
    class Subrange : public ComposedWidget 
    {
        public:
            Subrange(Box* parent);
            Subrange(Box* parent, double min, double max, double start, double end);
            virtual ~Subrange() = default;

            virtual void addEventListener(Event event, const std::function<void(EventInfos&)>& callback);
            void setMin(double val);
            void setMax(double val);
            void setStart(double val);
            void setEnd(double val);

            void setHeight(float height);

            enum InputType
            {
                NONE = 0,
                START,
                END
            };

            void addOnMinChange(const std::function<void(double)>& callback){_onMinChange.push_back(callback);}
            void addOnMaxChange(const std::function<void(double)>& callback){_onMaxChange.push_back(callback);}
            void addOnStartChange(const std::function<void(double)>& callback){_onStartChange.push_back(callback);}
            void addOnEndChange(const std::function<void(double)>& callback){_onEndChange.push_back(callback);}

        protected : 
            ml::Box* _container;
            ml::Box* _1;
            ml::Box* _2;
            ml::Box* _3;

            double _min = 0; //bp cg
            double _max = 100; //bp cg
            double _start = 0; //bp cg
            double _end = 100; //bp cg

            bool _dragging = false;
            InputType _inputType = InputType::NONE;
                         
            float _pixelFromRatio(double ratio);
            void _updateGui();
            void _init(Box* parent);
            void _setEvents();
            void _onMouseDown(EventInfos& e);
            void _onMouseUp(EventInfos& e);
            void _onMouseMove(EventInfos& e);
            void _setInputTypeFromRatio(double ratio);

            float _start_ratio() const;
            float _end_ratio() const;

            ml::Vec<std::function<void(double)>> _onMinChange;
            ml::Vec<std::function<void(double)>> _onMaxChange;
            ml::Vec<std::function<void(double)>> _onStartChange;
            ml::Vec<std::function<void(double)>> _onEndChange;

        public : 
#include "./Subrange_gen.h"
    };
}
