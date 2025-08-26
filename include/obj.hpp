#ifndef OBJ_H
#define OBJ_H
#include <climits>
#include <memory>
#include <types.hpp>

namespace nae {
class Obj {
public:
    explicit Obj(Type) : type(Type::Undefined) {};
    Obj(Type type, std::string const &name, int cost)
        : type(type), cost(cost), name(name) {}

    Type getType() const { return type; }
    const std::string &getName() const { return name; }
    void setName(std::string const &newName) { name = newName; }

    void setCost(int64_t newCost) { cost = newCost; }
    int64_t getCost() const { return cost; }

    void setUserIntField(int64_t field) { userIntField = field; }
    int64_t getUserIntField() const { return userIntField; }

    void setUserObjectField(std::shared_ptr<Obj> obj) { userObjField = obj; }
    std::shared_ptr<Obj> getUserObjectField() const { return userObjField; }

    virtual std::string toString() const {
        std::string result =
            "Obj(" + typeToString(type) + ") " + name +
            " cost=" + std::to_string(cost) +
            " user=" + std::to_string(userIntField) + " " +
            std::to_string(userIntField) + " " +
            (userObjField ? userObjField->getName() : std::string("null"));

        return result;
    }

    virtual bool isValid() const {
        return type != Type::Undefined && !name.empty();
    }
    virtual ~Obj() = 0;

private:
    Type type;
    int64_t cost; 
    std::string name;

protected:
    int64_t userIntField = 0;                    // Default user field
    std::shared_ptr<Obj> userObjField = nullptr; // Default user object field
};
} // namespace nae

#endif
