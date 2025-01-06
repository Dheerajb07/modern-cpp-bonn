#include "html_writer.hpp"
#include <iomanip>
#include <iostream>
#include <string>

// extern int indent_level;

void IndentLine(int level) {
  // Print spaces for indentation
  for (int i = 0; i < level; i++) {
    std::cout << "  ";
  }
}

void html_writer::OpenDocument() {
  std::cout << "<!DOCTYPE html>" << std::endl;
  std::cout << "<html>" << std::endl;
}

void html_writer::CloseDocument() { std::cout << "</html>" << std::endl; }

void html_writer::AddCSSStyle(const std::string &stylesheet) {
  // head tag
  IndentLine(1);
  std::cout << "<head>" << std::endl;
  // link tag
  IndentLine(2);
  std::cout << "<link rel=\"stylesheet\" type=\"text/css\" href=\""
            << stylesheet << "\" />" << std::endl;
  // end head tag
  IndentLine(1);
  std::cout << "</head>" << std::endl;
}

void html_writer::AddTitle(const std::string &title) {
  IndentLine(1);
  // Print title block
  std::cout << "<title>" << title << "</title>" << std::endl;
}

void html_writer::OpenBody() {
  IndentLine(1);
  std::cout << "<body>" << std::endl;
}

void html_writer::CloseBody() {
  IndentLine(1);
  std::cout << "</body>" << std::endl;
}

void html_writer::OpenRow() {
  IndentLine(2);
  std::cout << "<div class=\"row\">" << std::endl;
}

void html_writer::CloseRow() {
  IndentLine(2);
  std::cout << "</div>" << std::endl;
}

void html_writer::AddImage(const std::string &img_path, float score,
                           bool highlight) {
  // open column div
  IndentLine(3);
  if (highlight) {
    std::cout << "<div class=\"column\" style=\"border: 5px solid green;\">"
              << std::endl;
  } else {
    std::cout << "<div class=\"column\">" << std::endl;
  }

  // get image title
  std::string img_title = img_path.substr(5);
  // add title
  IndentLine(4);
  std::cout << "<h2>" << img_title << "</h2>" << std::endl;

  // add image
  IndentLine(4);
  std::cout << "<img src=\"" << img_path << "\" />" << std::endl;

  // add score
  IndentLine(4);
  std::cout << "<p>" << "score = " << std::fixed << std::setprecision(2)
            << score << "</p>" << std::endl;

  // close column div
  IndentLine(3);
  std::cout << "</div>" << std::endl;
}