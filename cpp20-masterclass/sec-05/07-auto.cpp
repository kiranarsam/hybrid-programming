#include <iostream>
// auto keyword tells the compiler to infer the type of an expression and use
// that as the type for our variable
int main() {
	auto var1 {12};
    auto var2 {13.0};
    auto var3 {14.0f};
    auto var4 {15.0l};
    auto var5 {'e'};
    //int modifier suffixes
    auto var6 { 123u}; // unsigned
    auto var7 { 123ul}; //unsigned long
    auto var8 { 123ll}; // long long
    std::cout << "var1 = 12 occupies : " << sizeof(var1) << " bytes" << std::endl;
    std::cout << "var2 = 13.0 occupies : " << sizeof(var2) << " bytes" << std::endl;
    std::cout << "var3 = 14.0f occupies : " << sizeof(var3) << " bytes" << std::endl;
    std::cout << "var4 = 15.0l occupies : " << sizeof(var4) << " bytes" << std::endl;
    std::cout << "var5 = 'e' occupies : " << sizeof(var5) << " bytes" << std::endl;
    std::cout << "var6 = 123u occupies : " << sizeof(var6) << " bytes" << std::endl;
    std::cout << "var7 = 123ul occupies : " << sizeof(var7) << " bytes" << std::endl;
    std::cout << "var8 = 123ll occupies : " << sizeof(var8) << " bytes" << std::endl;
    return 0;
}