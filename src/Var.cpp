#include "Var.h"

Var::Var() : value(0), isInitialized(false) {}

Var::Var(int val) : value(val), isInitialized(true) {}

Var Var::cal(const Var &v1, const Var &v2, char op) {
	Var res;
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
			ContextManager::getInstance()->pushError(2, "");
		} else if (v2.isInitialized) {
			res.value = v1.value / v2.value;
		}
	}

	return (res);
}

int Var::getValue() const {
	return (value);
}

bool Var::getIsInitialized() const {
	return (isInitialized);
}
