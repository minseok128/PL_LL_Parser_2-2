#ifndef VALUE_H
#define VALUE_H

# include "ContextManager.h"

class Var {
private:
    int value;
    bool isInitialized;

public:
    Var();

    explicit Var(int val);

    static Var cal(const Var &v1, const Var &v2, char op);

    int getValue() const;

    bool getIsInitialized() const;
};

#endif // VALUE_H
