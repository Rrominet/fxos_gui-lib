#pragma once
#include <functional>
#include <nlohmann/json.hpp>

//this only works with global ml::app() (App) instance singleton.
namespace ml
{
    class ChangeChecker
    {
        public : 
            ChangeChecker(size_t intervalPeriod = 5000);
            virtual ~ChangeChecker() = default;

            void setOnchange(const std::function<void()>& f); //changed
            bool changed() const;
            bool stop();
            bool start();

            void setGetDataFunction(const std::function<nlohmann::json()>& f){_getCurrent = f;}

            bool started() const {return _intervalid != -1;}

        private : 
            std::function<void()> _onchange = 0;
            std::function<void()> _oninterval = 0;

            nlohmann::json _prev = nlohmann::json::object();
            nlohmann::json _current = nlohmann::json::object();
            std::function<nlohmann::json()> _getCurrent = 0;

            void _update();

            int _intervalid = -1;
            size_t _intervalPeriod = 5000;
    };
}
