#include "./VideoCache.h"
#include <algorithm>

namespace ml
{
    void VideoCache::add(const VideoImgData& data)
    {
        _imgs[data.frame] = data;
    }

    void VideoCache::clear(long from,long to)
    {
        for (long i = from; i <= to; i++)
            _imgs.erase(i);
    }

    void VideoCache::clearFarest(long from, long quantity)
    {
        if (_imgs.size() <= quantity)
            quantity = _imgs.size() - 1;

        // Create a vector of pairs (frame_index, distance_from_target)
        std::vector<std::pair<long, long>> distances;
        distances.reserve(_imgs.size());

        for (const auto& pair : _imgs)
        {
            long distance = std::abs(from - pair.first);
            distances.emplace_back(pair.first, distance);
        }

        // Sort by distance (descending)
        std::sort(distances.begin(), distances.end(), 
                [](const auto& a, const auto& b) { return a.second > b.second; });

        // Remove the 'quantity' frames with the largest distance
        size_t to_remove = std::min(static_cast<size_t>(quantity), distances.size());
        for (size_t i = 0; i < to_remove; ++i) {
            _imgs.erase(distances[i].first);
        }
    }

    void VideoCache::clearIfNeeded(long from, long quantity)
    {
        if (_imgs.size() >= _maxImagesCanLoad)
            this->clearFarest(from, quantity);
    }

    void VideoCache::clearAll()
    {
        _imgs.clear();
    }

    bool VideoCache::exists(long idx) const
    {
        return _imgs.find(idx) != _imgs.end();
    }
}
