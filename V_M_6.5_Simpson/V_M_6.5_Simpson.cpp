#include <iostream>
#include <cmath>
#include <locale>

double f(double x) {
    return 1.0 / sqrt(1.0 + pow(x, 4));
}

double simpson_integration(double (*func)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double result = func(a) + func(b);

    for (int i = 1; i < n; i += 2) {
        result += 4 * func(a + i * h);
    }

    for (int i = 2; i < n - 1; i += 2) {
        result += 2 * func(a + i * h);
    }

    return result * h / 3.0;
}

std::pair<double, int> adaptive_simpson_integration(double (*func)(double), double a, double b, int n0, double relative_accuracy) {
    int n = n0;
    double integral_value = simpson_integration(func, a, b, n);
    double prev_integral_value;

    do {
        n *= 2;
        prev_integral_value = integral_value;
        integral_value = simpson_integration(func, a, b, n);
    } while (std::abs(integral_value - prev_integral_value) > relative_accuracy * std::abs(integral_value));

    return std::make_pair(integral_value, n);
}

int main() {
    setlocale(LC_ALL, "");
    double a = 0.0;
    double b = 2.0;
    int n0 = 6;
    double relative_accuracy;

    std::cout << "Enter the required integration accuracy: ";
    std::cin >> relative_accuracy;
    if (relative_accuracy == 0) {
        relative_accuracy = 1e-6;
    }

    std::pair<double, int> integral_result = adaptive_simpson_integration(f, a, b, n0, relative_accuracy);
    double integral_value = integral_result.first;
    int final_nodes = integral_result.second;
    double integration_accuracy = std::abs(simpson_integration(f, a, b, final_nodes * 2) - integral_value);

    std::cout << std::scientific << "Integral value: " << integral_value << std::endl;
    std::cout << "Final number of nodes: " << final_nodes << std::endl;
    std::cout << std::scientific << "Integration accuracy: " << integration_accuracy << std::endl;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Press Enter to exit...";
    std::cin.get();


    return 0;
}
