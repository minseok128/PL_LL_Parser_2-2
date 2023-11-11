#ifndef VALUE_H
#define VALUE_H

class Var {
private:
    int value;
    bool isInitialized;

public:
    Var();

    explicit Var(int val);

    Var(const Var &v);

    static Var cal(const Var &v1, const Var &v2, char op);

    // Additional methods to access and modify private members, if needed
    int getValue() const;

    bool getIsInitialized() const;

    void setValue(int val);

    void setIsInitialized(bool val);
};

#endif // VALUE_H
