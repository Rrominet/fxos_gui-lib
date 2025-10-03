#pragma once
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "fmod.hpp"
#include <boost/process/exception.hpp>
#include <boost/process.hpp>
#include <nlohmann/json.hpp>
#include "./Events.h"
#include "sound/mlSystem.h"

class mlSound;
namespace ml
{
    //you can react to the events : 
    //loaded

    class VideoSound
    {
        public : 
            VideoSound();
            VideoSound(const std::string& path);
            ~VideoSound();

            //will emit the event loaded
            void load_async();
            void play();
            void pause();

            long int bytes = 0;

            ml::Events& events() { return _events; }
            mlSystem* system() { return _sys.get(); }

            void setPath(const std::string& path);
            bool loaded() const;
            
            std::string _ffmpeg_path() const;
            std::string _ffprobe_path() const;

            double currentTime() const;
            void seek(double time);

            void setVolume(double volume);
            double volume() const;

            void setSpeed(double speed);
            double speed() const;

        protected : 
            json _data;
            std::string _path;

            std::unique_ptr<mlSystem> _sys = nullptr;
            mlSound* _sound = nullptr; //bp cgs 
                                       //
            ml::Events _events;
            mutable std::mutex _mtx;

            bool _loaded = false;
            double _speed = 1.0;

        public : 
#include "./VideoSound_gen.h"
    };
}
