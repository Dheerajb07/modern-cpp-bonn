#include "html_writer.hpp"

using namespace html_writer;

int indent_level = 0;

int main(){
    OpenDocument();
    
    AddTitle("Image Browser");
    
    AddCSSStyle("style.css");
    
    OpenBody();
    
    // Row 1
    OpenRow();
    // Img 1
    AddImage("data/000000.png",0.98,true);
    // Img 2
    AddImage("data/000100.png",0.96);
    // Img 3
    AddImage("data/000200.png",0.88);
    // Close Row 1
    CloseRow();

    // Row 2
    OpenRow();
    // Img 1
    AddImage("data/000300.png",0.87);
    // Img 2
    AddImage("data/000400.png",0.80);
    // Img 3
    AddImage("data/000500.png",0.79);
    // Close Row 2
    CloseRow();

    // Row 3
    OpenRow();
    // Img 1
    AddImage("data/000600.png",0.76);
    // Img 2
    AddImage("data/000700.png",0.75);
    // Img 3
    AddImage("data/000800.png",0.20);
    // Close Row 2
    CloseRow();

    CloseBody();

    CloseDocument();
    
    return 0;
}