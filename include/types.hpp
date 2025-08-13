#ifndef TYPES_H
#define TYPES_H

#include <string>
namespace nae {

enum class Type { Undefined, Vertex, Edge, Unknown };

inline std::string typeToString(Type type) {
    switch (type) {
    case Type::Undefined:
        return "Undefined";
    case Type::Vertex:
        return "Vertex";
    case Type::Edge:
        return "Edge";
    case Type::Unknown:
        return "Unknown";
    default:
        return "Invalid Type";
    }
}

inline Type stringToType(std::string const &str) {
    if (str == "Vertex")
        return Type::Vertex;
    if (str == "Edge")
        return Type::Edge;
    if (str == "Unknown")
        return Type::Unknown;
    return Type::Undefined;
}

} // namespace nae

#endif // TYPES_H