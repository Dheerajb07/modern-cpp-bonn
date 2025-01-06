#include "image_browser.hpp"
#include "html_writer.hpp"

void image_browser::AddFullRow(const ImageRow &row, bool first_row) {
  // open row
  html_writer::OpenRow();

  int i = 0;
  for (auto scored_img : row) {

    // extract path and score
    auto [img_path, score] = scored_img;
    // add image
    if (first_row && i == 0) {
      html_writer::AddImage(img_path, score, true);
    } else {
      html_writer::AddImage(img_path, score);
    }
    i++;
  }

  // close row
  html_writer::CloseRow();
}

void image_browser::CreateImageBrowser(const std::string &title,
                                       const std::string &stylesheet,
                                       const std::vector<ImageRow> &rows) {
  //   int indent_level = 0;

  html_writer::OpenDocument();

  html_writer::AddTitle(title);

  html_writer::AddCSSStyle(stylesheet);

  html_writer::OpenBody();

  int i = 0;
  for (auto row : rows) {
    if (i == 0) {
      image_browser::AddFullRow(row, true);
    } else {
      image_browser::AddFullRow(row);
    }
    i++;
  }

  html_writer::CloseBody();

  html_writer::CloseDocument();
}