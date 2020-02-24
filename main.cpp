#include<iostream>

struct TemplateHelpers {
public:
    template <typename... Ts>
    static constexpr bool IsPointer(){
        return (!!IsPointerHelper< typename std::remove_cv<Ts>::type  >::value && ...);
    }

private:
    template <typename T>
    struct IsPointerHelper {
        enum {value = false};
    };

    template <typename T>
    struct IsPointerHelper<T*> {
        enum {value = true};
    }; 
};

int main() {

    const auto *x = new int();
    constexpr auto y = int{0};
    const auto *z = new double();

    std::cout << std::boolalpha;
    std::cout << TemplateHelpers::IsPointer<decltype(x)>() << "\n";
    std::cout << TemplateHelpers::IsPointer<int[10]>() << "\n";
    std::cout << TemplateHelpers::IsPointer<decltype(y)>() << "\n";
    std::cout << TemplateHelpers::IsPointer<decltype(x), decltype(z)>() << "\n";
    std::cout << TemplateHelpers::IsPointer<decltype(x), decltype(y), decltype(z)>() << "\n";

    return 0;
}
