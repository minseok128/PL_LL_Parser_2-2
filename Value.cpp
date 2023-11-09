#include "Value.h"
#include "InformationManager.h"

Value::Value() : value(0), isInitialized(false) {}

Value::Value(int val) : value(val), isInitialized(true) {}

Value::Value(const Value &v) : value(v.value), isInitialized(v.isInitialized) {}

Value Value::cal(const Value &v1, const Value &v2, char op) {
    Value res;
    res.isInitialized = v1.isInitialized && v2.isInitialized;

    if (op == '+') {
        res.value = v1.value + v2.value;
    } else if (op == '-') {
        res.value = v1.value - v2.value;
    } else if (op == '*') {
        res.value = v1.value * v2.value;
    } else if (op == '/') {
        if (v2.isInitialized && v2.value == 0) {
            res.isInitialized = false;
            InformationManager::getInstance()->pushError(2, "Division by zero");
        } else if (v2.isInitialized) {
            res.value = v1.value / v2.value;
        }
    }

    return res;
}

int Value::getValue() const {
    return value;
}

bool Value::getIsInitialized() const {
    return isInitialized;
}

void Value::setValue(int val) {
    value = val;
    isInitialized = true;
}

void Value::setIsInitialized(bool val) {
    isInitialized = val;
}
