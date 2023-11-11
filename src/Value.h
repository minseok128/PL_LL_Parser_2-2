#ifndef VALUE_H
#define VALUE_H

class Value {
private:
    int value;
    bool isInitialized;

public:
    Value();

    explicit Value(int val);

    Value(const Value &v);

    static Value cal(const Value &v1, const Value &v2, char op);

    // Additional methods to access and modify private members, if needed
    int getValue() const;

    bool getIsInitialized() const;

    void setValue(int val);

    void setIsInitialized(bool val);
};

#endif // VALUE_H
