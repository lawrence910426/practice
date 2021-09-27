#include <iostream>
#include <string>

// abstract class
class Food {
	public:
		enum class Type {
			IdiotSandwich,
			NormalSandwich
		};
		friend std::ostream & operator << (std::ostream &out, Food &d) {
			d.print(out);
			return out;
		}
		Type getType() { return type; }
		void setType(Type x) { type = x; }
	private:
		virtual void print(std::ostream &out) {}
		Type type;
};

class IdiotSandwich : public Food {
	public:
		IdiotSandwich(int x) {
			setType(Type::IdiotSandwich);
			setINT(x);
		}
		void setINT(int x) { intelligence = x; }
		int getINT() { return intelligence; }
	private:
		// TODO
		void print(std::ostream &out) {
            out << "An idiot sandwich with intelligence level " << intelligence << " only.";
        }
		int intelligence;
};

class NormalSandwich : public Food {
	public:
		NormalSandwich(std::string x) {
			setType(Type::NormalSandwich);
			setName(x);
		}
		void setName(std::string x) { name = x; }
		std::string getName() { return name; }
	private:
		// TODO
		void print(std::ostream &out) {
            out << name << ". Masterpiece of sandwiches.";
        }
		std::string name;
};

class Dish {
	public:
		Dish() { food = nullptr; }
		~Dish();
		Food &getFood() { return (*food); }
		const Food &getFood() const { return (*food); }
		// TODO
		friend std::istream & operator >> (std::istream &in, Dish &d) ; 
		Food *food;
};

Dish::~Dish() { delete food; }

std::istream & operator >> (std::istream &in, Dish &d) {
    if(d.food != nullptr) delete d.food;
    
    std::string name;
    in >> name;
    if(name == "Ramsay") {
        int intelli;
        in >> intelli;
        d.food = new IdiotSandwich(intelli);
    } else {
        d.food = new NormalSandwich(name);
    }
    return in;
}
