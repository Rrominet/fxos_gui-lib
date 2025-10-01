#include "./Paths_impl.h"
#include "files.2/files.h"

namespace ml
{
    std::string Paths_impl::root() const
    {
        return files::execDir();	
    }

    std::string Paths_impl::path(const std::string& relative) const
    {
        //global for linux/unix
        if (relative[0] == '/')
            return relative;

        //global for windows/dos
        if (relative[1] == ':')
            return relative;

        return files::cleaned(this->root() + files::sep() + relative);	
    }
}
