#ifndef UTPROFILEREXCEPTION_H
#define UTPROFILEREXCEPTION_H

#include <exception>
#include <string>
#include <sstream>

#define UTPROFILER_EXCEPTION(m) throw UTProfilerException(__FILE__, __LINE__, m);

///Cette classe formate une exception en indiquant le fichier, la ligne de lancement et le message d'exception
class UTProfilerException : public std::exception
{
    std::string file, msg;
    int lineno;
public:
    UTProfilerException(const char* filename, int line, const std::string& message) noexcept : file(filename), msg(message), lineno(line) {}
    ~UTProfilerException() noexcept {}

    const char* what() const noexcept
    {
        std::stringstream ss;
        ss << "[Exception fichier " << file << " ligne n°" << lineno << "] : " << msg << "\n";
        return ss.str().c_str();
    }
};

#endif // UTPROFILEREXCEPTION_H
