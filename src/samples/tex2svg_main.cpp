#include <iostream>
#include <fstream>
#include <string>

// Include the real MicroTeX core headers
#include "latex.h"
#include "render.h"
#include "graphic/graphic_svg.h"

int main() {
    // 1. Initialise the engine with its default resource path
    tex::LaTeX::init();

    // 2. Define the target math formula
    std::string formula = R"(\int_{-\infty}^{\infty} e^{-x^2} dx = \sqrt{\pi})";

    // 3. FIX C2660 & C2065: Call the actual 5-argument parse method
    // Arguments: code, logical_width, font_size, line_space, foreground_color
    tex::Render* render = tex::LaTeX::parse(
        formula, 
        720,             // logical layout width
        20.0f,           // font size in points
        10.0f,           // extra line spacing
        0xFF000000       // ARGB Black color
    );

    if (render != nullptr) {
        // 4. FIX C2039: Use SVGCanvas to record the vector paths
        tex::SVGCanvas svg_canvas;
        
        // Draw the formula layout onto the vector canvas canvas (at x=0, y=0)
        render->draw(svg_canvas, 0, 0);

        // 5. Fetch the complete structural SVG XML string string
        std::string svg_output = svg_canvas.getSVG();
        
        // Save to disk
        std::ofstream out("formula.svg");
        out << svg_output;
        out.close();

        std::cout << "Vector instructions successfully written to formula.svg\n";
        
        // 6. FIX C2541: Properly delete the pointer instance
        delete render;
    } else {
        std::cerr << "Failed to parse formula. Check syntax.\n";
        return 1;
    }

    // 7. Clean up global font resources before exiting
    tex::LaTeX::release();
    return 0;
}
