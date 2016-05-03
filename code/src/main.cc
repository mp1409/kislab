#include <iostream>

/**
 * Example class to test doc.
 */
class Testclass {
	public:
		/**
		 * Says hi.
		 *
		 * \return A nice greeting.
		 */
		std::string hello() {
			return "Hello World!";
		}
};

int main() {
	Testclass test;
	std::cout << test.hello() << std::endl;
	return 0;
}
