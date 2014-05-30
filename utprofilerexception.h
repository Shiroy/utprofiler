#ifndef UTPROFILEREXCEPTION_H
#define UTPROFILEREXCEPTION_H

#include <exception>
#include <string>
#include <sstream>

#define UTPROFILER_EXCEPTION(m) throw UTProfilerException(__FILE__, __LINE__, m);

class UTProfilerException : public std::exception
{
    std::string file, msg;
    int lineno;
public:
    UTProfilerException(const char* filename, int line, const std::string& message) noexcept : file(filename), lineno(line), msg(message) {}
    ~UTProfilerException() noexcept {}

    const char* what() const noexcept
    {
        std::stringstream ss;
        ss << "[Exception fichier " << file << " ligne n°" << lineno << " : " << msg << "\n";
        return ss.str().c_str();
    }
};

#endif // UTPROFILEREXCEPTION_H
