//Copyright 2021 <rinamuka4@gmail.com>

#include "htmlParser.hpp"

#include "gumbo.h"
#include "htmlDownloader.hpp"
#include "iostream"
#include "output.hpp"

static void search_for_images(GumboNode* node, std::vector<std::string>& imgs) {
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

static void search_for_links(GumboNode* node, std::vector<url>& links) {
  if (node->type != GUMBO_NODE_ELEMENT) {
    return;
  }
  GumboAttribute* href;
  if (node->v.element.tag == GUMBO_TAG_A &&
      (href = gumbo_get_attribute(&node->v.element.attributes, "href")) &&
      (std::string(
           gumbo_get_attribute(&node->v.element.attributes, "href")->value)
           .substr(0, 4) == "http") &&
      (std::string(
           gumbo_get_attribute(&node->v.element.attributes, "href")->value)
           .substr(0, 5) != "https") &&
      (std::string(
           gumbo_get_attribute(&node->v.element.attributes, "href")->value)
           .substr(0, std::string(gumbo_get_attribute(
                                      &node->v.element.attributes, "href")
                                      ->value)
                              .size() -
                          3) != "png") &&
      (std::string(
           gumbo_get_attribute(&node->v.element.attributes, "href")->value)
           .substr(std::string(
                       gumbo_get_attribute(&node->v.element.attributes, "href")
                           ->value)
                           .size() -
                       3,
                   3) != "jpg")) {
    url urlLink = url();
    std::string host = href->value;
    if (host.find("http://") == 0) host = host.substr(7);
    size_t i = 0;
    if (host.size() != 0) {
      for (; i < host.size(); ++i) {
        if ((host[i] == '/') || (host[i] == '?')) break;
      }
    } else return;

    urlLink.domen = host.substr(0, i);

    std::string target = href->value;
    if (target.find("http://") == 0) {
      target = target.substr(7);
    }
    int pos = target.find('/');
    if (pos == -1) {
      urlLink.uri = "/";
    } else {
      urlLink.uri = target.substr(pos);
    }

    links.push_back(urlLink);
  }

  GumboVector* children = &node->v.element.children;
  for (unsigned int i = 0; i < children->length; ++i) {
    search_for_links(static_cast<GumboNode*>(children->data[i]), links);
  }
}

void htmlParser::collectIMG(std::vector<std::string> pages,
                            htmlDownloader& downloader, int depth) {
  std::vector<std::string> imgs;
  if (pages.empty()) {
    return;
  }
  for (auto& page : pages) {
    GumboOutput* output = gumbo_parse(page.c_str());
    search_for_images(output->root, imgs);
    gumbo_destroy_output(&kGumboDefaultOptions, output);
  }
  outputObj_.writeIMG(imgs);
  std::vector<url> links;
  for (auto& page : pages) {
    GumboOutput* output = gumbo_parse(page.c_str());
    search_for_links(output->root, links);
    gumbo_destroy_output(&kGumboDefaultOptions, output);
  }

  downloader.startDownload(links, depth - 1);
}

void htmlParser::startParse(std::vector<std::string> pages,
                            htmlDownloader& downloader, int depth) {
  parserPool_.enqueue([this, pages, depth, &downloader]() {
    this->collectIMG(pages, downloader, depth);
  });
}
