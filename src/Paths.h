#pragma once
#include <string>

#ifdef __EMSCRIPTEN__
#include "./em/Paths_impl.h"
#else
#include "./gtk/Paths_impl.h"
#endif

namespace ml
{
    class Paths
    {
        public : 

            // for gtk : execdir
            // for em : the url root
            std::string root() const {return _impl.root();}

            // for gtk will return the abosule path of the file on disk
            // for em will return the url of the file like https://your-url/your-file/path (if relative == your/file/path)
            std::string path(const std::string& relative) const {return _impl.path(relative);}

        protected : 
            Paths_impl _impl; //bp cg
    };
}
