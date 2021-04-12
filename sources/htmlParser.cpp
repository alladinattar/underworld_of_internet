#include "htmlParser.hpp"

#include "gumbo.h"
#include "iostream"

static void search_for_images(GumboNode* node, std::vector<std::string> imgs) {
  if (node->type != GUMBO_NODE_ELEMENT) {
    return;
  }
  GumboAttribute* src;
  if (node->v.element.tag == GUMBO_TAG_IMG &&
      (src = gumbo_get_attribute(&node->v.element.attributes, "src"))) {
    imgs.push_back(src->value);
  }

  GumboVector* children = &node->v.element.children;
  for (unsigned int i = 0; i < children->length; ++i) {
    search_for_images(static_cast<GumboNode*>(children->data[i]), imgs);
  }
}

static void search_for_links(GumboNode* node, std::vector<std::string> links) {
  if (node->type != GUMBO_NODE_ELEMENT) {
    return;
  }
  GumboAttribute* href;
  if (node->v.element.tag == GUMBO_TAG_A &&
      (href = gumbo_get_attribute(&node->v.element.attributes, "href")) &&
      (std::string(
           gumbo_get_attribute(&node->v.element.attributes, "href")->value)
           .substr(0, 4) == "http")) {
    links.push_back(href->value);
  }

  GumboVector* children = &node->v.element.children;
  for (unsigned int i = 0; i < children->length; ++i) {
    search_for_links(static_cast<GumboNode*>(children->data[i]), links);
  }
}

std::vector<std::string> htmlParser::collectIMG(
    std::vector<std::string> pages) {
  std::vector<std::string> imgs;
  for (auto& page : pages) {
    GumboOutput* output = gumbo_parse(page.c_str());
    search_for_images(output->root, imgs);
    gumbo_destroy_output(&kGumboDefaultOptions, output);
  }
  return imgs;
}

std::vector<std::string> htmlParser::collectLinks(
    std::vector<std::string> pages) {
  std::vector<std::string> links;
  for (auto& page : pages) {
    GumboOutput* output = gumbo_parse(page.c_str());
    search_for_links(output->root, links);
    gumbo_destroy_output(&kGumboDefaultOptions, output);
  }
  return links;
}