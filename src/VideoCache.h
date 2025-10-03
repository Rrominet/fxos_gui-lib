#pragma once
#include <vector>
#include <unordered_map>
#include <mutex>
#include <atomic>
#include "./enums.h"

namespace ml
{
    struct VideoImgData
    {
        ImageFormat format = JPEG;
        std::vector<unsigned char> data;
        long frame=-1;
    };

    class VideoCache
    {
        public:
            VideoCache() = default;
            ~VideoCache() = default;

            void add(const VideoImgData& data);
            void clear(long from, long to);
            void clearFarest(long from, long quantity=5000);

            //needed if _maxImagesCanLoad is reached by _imgs.size()
            void clearIfNeeded(long from, long quantity=5000);
            void clearAll();

            long frameBeingLoaded()const {return _frameBeingLoaded.load();}
            long lastLoaded() const{return _frameBeingLoaded.load();};
            void setFrameBeingLoaded(long frame){_frameBeingLoaded = frame;}

            bool exists(long idx) const;
            long size()const {return _imgs.size();}

            VideoImgData& operator[](long idx){return _imgs[idx];}

        private : 
            long _totalImages = -1; //bp cgs
            int _maxImagesCanLoad = 32000; //bp cg

            std::unordered_map<long, VideoImgData> _imgs; //bp cg
            std::atomic_long _frameBeingLoaded = -1;

        public : 
#include "./VideoCache_gen.h"
    };
}
