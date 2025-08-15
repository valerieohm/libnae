#ifndef OBJ_H
#define OBJ_H
#include <climits>
#include <memory>
#include <types.hpp>

namespace nae {
class Obj {
public:
    explicit Obj(Type) : type(Type::Undefined) {};
    Obj(Type type, std::string const &name)
        : type(type), weight(LONG_MAX), name(name) {}

    Type getType() const { return type; }
    const std::string &getName() const { return name; }
    void setName(std::string const &newName) { name = newName; }

    void setWeight(int64_t newWeight) { weight = newWeight; }
    int64_t getWeight() const { return weight; }

    void setUserIntField(int64_t field) { userIntField = field; }
    int64_t getUserIntField() const { return userIntField; }

    void setUserObjectField(std::shared_ptr<Obj> obj) { userObjField = obj; }
    std::shared_ptr<Obj> getUserObjectField() const { return userObjField; }

    virtual std::string toString() const {
        std::string result =
            "Obj(type: " + typeToString(type) + ", name: " + name;
        result += ", userIntField: " + std::to_string(userIntField);
        if (userObjField != nullptr) {
            result += ", userObjectField: " + userObjField->getName();
        } else {
            result += ", userObjectField: null";
        }
        result += ")";
        return result;
    }

    virtual bool isValid() const {
        return type != Type::Undefined && !name.empty();
    }
    virtual ~Obj() = 0;

private:
    Type type;
    int64_t weight = INT64_MAX; // Default weight
    std::string name;

protected:
    int64_t userIntField = 0;                    // Default user field
    std::shared_ptr<Obj> userObjField = nullptr; // Default user object field
};
} // namespace nae

#endif
