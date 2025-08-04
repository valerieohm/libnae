#ifndef LIBNAE_H
#define LIBNAE_H

#include <string>
namespace nae {

    enum class Type {
        Undefined,
        Node,
        Edge,
        Unknown
    };
    
    inline std::string typeToString(Type type) {
        switch (type) {
            case Type::Undefined: return "Undefined";
            case Type::Node: return "Node";
            case Type::Edge: return "Edge";
            case Type::Unknown: return "Unknown";
            default: return "Invalid Type";
        }
    }

    inline Type stringToType(std::string const& str) {
        if (str =="Node") return Type::Node;
        if (str == "Edge") return Type::Edge;
        if (str == "Unknown") return Type::Unknown;
        return Type::Undefined;
    }
class Obj {
public:
    explicit Obj(Type) : type(Type::Undefined) {};
    Obj(Type type, std::string const& name) : type(type), name(name) {}
    
    Type getType() const { return type; }
    std::string getName() const { return name; }
    void setName(std::string const& newName) { name = newName; }

    virtual std::string toString() const {
        return "Obj(type: " + typeToString(type) + ", name: " + name + ")";
    }

    virtual bool isValid() const {
        return type != Type::Undefined && !name.empty();
    }
    virtual ~Obj() = 0;
    private:
    Type type;
    std::string name;
};



} // namespaee nae


#endif // LIBNAE_H