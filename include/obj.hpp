#ifndef OBJ_H
#define OBJ_H

#include <types.hpp>

namespace nae {
class Obj {
public:
    explicit Obj(Type) : type(Type::Undefined) {};
    Obj(Type type, std::string const &name) : type(type), name(name) {}

    Type getType() const { return type; }
    std::string getName() const { return name; }
    void setName(std::string const &newName) { name = newName; }

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
} // namespace nae

#endif
