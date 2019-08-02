#include "dialog.h"

#include <cstdio>
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

//Does not compile? Do 'sudo apt-get install libpoppler-qt5-dev'
#include <poppler/qt5/poppler-qt5.h>
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog)
{
  ui->setupUi(this);

 //Write a graph to file
  //Define the type of graph:
  //boost::adjacency_list is the 'Swiss army knife' graph
  typedef boost::adjacency_list
  <
    //Store all edges as a std::vector
    boost::vecS,
    //Store all vertices in a std::vector
    boost::vecS,
    //Relations are both ways (in this example)
    //(note: but you can freely change it to boost::directedS)
    boost::undirectedS,
    //All vertices are person names of type std::string
    boost::property<boost::vertex_name_t,std::string>,
    //All edges are weights equal to the encounter frequencies
    boost::property<boost::edge_weight_t,double>,
    //Graph itself has a std::string name
    boost::property<boost::graph_name_t,std::string>
  > Graph;

  Graph  g;

  //All vertex names
  //Note: cannot use spaces
  std::vector<std::string> names;
  names.push_back("Mr_A");
  names.push_back("Mrs_B");
  names.push_back("Dr_C");
  names.push_back("Prof_D");

  const Graph::vertex_descriptor v0 = boost::add_vertex(names[0],g);
  const Graph::vertex_descriptor v1 = boost::add_vertex(names[1],g);
  const Graph::vertex_descriptor v2 = boost::add_vertex(names[2],g);
  const Graph::vertex_descriptor v3 = boost::add_vertex(names[3],g);

  std::vector<double> frequencies;
  frequencies.push_back(0.9);
  frequencies.push_back(0.5);
  frequencies.push_back(0.6);
  frequencies.push_back(0.1);

  boost::add_edge(v0,v1,frequencies[0],g);
  boost::add_edge(v1,v2,frequencies[1],g);
  boost::add_edge(v2,v3,frequencies[2],g);
  boost::add_edge(v0,v3,frequencies[3],g);

  //Writing graph to file
  {
    std::ofstream f("test.dot");

    boost::dynamic_properties p;
    p.property("label", boost::get(boost::edge_weight, g));
    p.property("weight", boost::get(boost::edge_weight, g));
    p.property("node_id", boost::get(boost::vertex_name, g));
    //boost::write_graphviz(f,g,p); //Does not compile
    boost::write_graphviz(f,g); //Does not compile
    f.close();
  }
  //Convert test.dot file to test.pdf
  //Don't forget: 'sudo apt-get install dot2tex'
  const int result_1 = std::system("dot2tex test.dot > test.tex");
  assert(result_1 == 0);
  const int result_2 = std::system("texi2pdf test.tex");
  assert(result_2 == 0);

  //Load test.pdf in QLabel
  Poppler::Document *doc = Poppler::Document::load("test.pdf");
  const int current_page = 0;
  const double scale = 1.0;

  QImage image = doc->page(current_page)->renderToImage(
                            scale * physicalDpiX(),
                            scale * physicalDpiY());

  ui->label->setPixmap(QPixmap::fromImage(image));
}

Dialog::~Dialog()
{
  delete ui;
}
