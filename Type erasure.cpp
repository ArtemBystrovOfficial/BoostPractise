
// Type erasure side of things

#include <vector>
#include <iostream>

class any {
public:
	template <class T>
	any(const T& t) : ptr(new TypeErasure<T>(t)) {
		
	}
	template <class T>
	T cast_any() {
		if (typeid(T) != ptr->type_info())
			throw std::exception("bad_cast");
		return static_cast<TypeErasure<T> *>(ptr.get())->m_t;
	}
private:

	class BaseType {
	public:
		virtual const std::type_info& type_info() const = 0;
	};

	template<class T>
	class TypeErasure : public BaseType {
	public:
		TypeErasure(const T & t) : m_t(t){}
		const std::type_info& type_info() const {
			return typeid(m_t);
		}
		T m_t;
	};

	std::unique_ptr<BaseType> ptr;
};

int main() {
	any test = int(5);
	auto type = test.cast_any<int>();
	std::cout << type;
}
