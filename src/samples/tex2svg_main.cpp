#include <iostream>
#include <fstream>
#include <string>
#include "latex.h"

using namespace tex;

int main() {
    // 1. Initialise MicroTeX (it looks for its "res" folder with font definitions)
    // You can pass a specific path if resources are stored elsewhere
    LaTeX::init();

    // 2. Define your LaTeX math formula string
    std::string formula = R"(\int_{-\infty}^{\infty} e^{-x^2} dx = \sqrt{\pi})";

    // 3. Render the LaTeX formula into an internal formula representation
    // Arguments: formula string, text size (points), layout style, foreground colour
    Render* render = LaTeX::parse(formula, 20, "textstyle", 0xFF000000);

    if (render != nullptr) {
        // 4. Convert the rendered layout into pure SVG vector instructions
        std::string svg_output = LaTeX::toSVG(*render);
        
        // 5. Save the vector strings straight to disk
        std::ofstream out("formula.svg");
        out << svg_output;
        out.close();

        std::cout << "Vector instructions written to formula.svg\n";
        
        // Clean up memory
        delete render;
    } else {
        std::cerr << "Parsing failed. Check your LaTeX syntax.\n";
        return 1;
    }

    // 6. Release MicroTeX library resources
    LaTeX::release();
    return 0;
}
