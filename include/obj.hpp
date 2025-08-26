#ifndef OBJ_H
#define OBJ_H
#include <climits>
#include <memory>
#include <string>
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

    // Existing user int field methods
    int64_t getUserIntField() const { return userIntField; }
    void setUserIntField(int64_t value) { userIntField = value; }

    // Add user string field methods
    std::string getUserStringField() const { return userStringField; }
    void setUserStringField(const std::string &value) {
        userStringField = value;
    }

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
    int64_t userIntField = 0;
    std::string userStringField;
    std::shared_ptr<Obj> userObjField = nullptr;
};
} // namespace nae

#endif
