#include "htmlParser.hpp"
#include "output.hpp"
#include "htmlDownloader.hpp"
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

static void search_for_links(GumboNode* node, std::vector<url>& links) {
  if (node->type != GUMBO_NODE_ELEMENT) {
    return;
  }
  GumboAttribute* href;
  if (node->v.element.tag == GUMBO_TAG_A &&
      (href = gumbo_get_attribute(&node->v.element.attributes, "href")) &&
      (std::string(
           gumbo_get_attribute(&node->v.element.attributes, "href")->value)
           .substr(0, 4) == "http")) {
    url urlLink = url();
    std::string host = href->value;

    if (host.find("http://") == 0)
      host = host.substr(7);
    size_t i = 0;
    for (; i < host.size(); ++i) {
      if ((host[i] == '/') || (host[i] == '?')) break;
    }
    urlLink.domen = host.substr(0, i);

    std::string target = href->value;
    //std::cout<<target<<std::endl;
    if (target.find("http://") == 0){
      target = target.substr(7);
    }
    int pos = target.find('/');
    if (pos == -1)
      urlLink.uri = "/";
    urlLink.uri = target.substr(pos);
    std::cout<<urlLink.domen<<"   "<<urlLink.uri<<std::endl;
    links.push_back(urlLink);
  }

  GumboVector* children = &node->v.element.children;
  for (unsigned int i = 0; i < children->length; ++i) {
    search_for_links(static_cast<GumboNode*>(children->data[i]), links);
  }
}


void htmlParser::collectIMG(
    std::vector<std::string> pages, htmlDownloader& downloader , int& depth) {
  std::vector<std::string> imgs;
  if (pages.empty()){
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
  for (auto i: links){std::cout<<i.uri<<std::endl;}
  downloader.downloadPages(links, depth-1);
}

/*
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

void htmlParser::startParse(std::vector<std::string>& pages, ThreadPool& downloaderPool, ThreadPool & parserPool, ThreadPool& outputPool, std::string path) {
  std::vector<std::string> links;

  for (auto& page : pages) {
    GumboOutput* output = gumbo_parse(page.c_str());
    search_for_links(output->root, links);
    gumbo_destroy_output(&kGumboDefaultOptions, output);
  }
  std::vector<std::string> imgs;
  for (auto& page : pages) {
    GumboOutput* output = gumbo_parse(page.c_str());
    search_for_images(output->root, imgs);
    gumbo_destroy_output(&kGumboDefaultOptions, output);
  }
  downloaderPool.enqueue([&](void){
    htmlDownloader downloader = htmlDownloader();
    downloader.startDownloadPages(links, parserPool, downloaderPool, outputPool, path);
  });
  std::cout<<"htlll";
  outputPool.enqueue([&](void){
    outPut output = outPut();
    output.writeFile(path, imgs);
  });

}*/
