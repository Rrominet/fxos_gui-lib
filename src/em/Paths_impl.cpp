#include "./Paths_impl.h"
#include "files.2/files.h"

namespace ml
{
    std::string Paths_impl::root() const
    {
        return "";
    }

    std::string Paths_impl::lib() const
    {
        return "lib";
    }

    std::string Paths_impl::path(const std::string& relative) const
    {
        //global for linux/unix
        if (relative[0] == '/')
            return files::cleaned(this->root() + relative);	

        //global for windows/dos
        if (relative[1] == ':')
            return files::cleaned(this->root() + relative.substr(1));	

        return files::cleaned(this->root() + "/" + relative);	
    }
}
