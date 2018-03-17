#include "gui.h"


ConstructWindow::ConstructWindow()
: m_Box(Gtk::ORIENTATION_VERTICAL),
  m_point_frame("Points"),
  m_edge_frame("Edges"),
  m_submit("All Points Done"),
  m_add_point("Add More Points"),
  m_add_label("Add Label to this Point"),
  m_add_edge("Add Edge"),
  m_create("Front View Done")
{
  front = new OrthoProjection;
  top = new OrthoProjection;
  side = new OrthoProjection;
  cp = new ClusteredPoint;
  this->projection = 0;

  set_title("Front View");
  set_border_width(12);

  add(m_Box);
  m_Box.pack_start(m_point_frame, Gtk::PACK_EXPAND_WIDGET, 10);

  // Add Points
  m_point_frame.add(m_point_grid);

  m_entry_x.set_max_length(10);
  m_entry_x.set_text("x");
  m_entry_x.select_region(0, m_entry_x.get_text_length());

  m_entry_y.set_max_length(10);
  m_entry_y.set_text("y");
  m_entry_y.select_region(0, m_entry_y.get_text_length()); 

  m_entry_z.set_max_length(10);
  m_entry_z.set_text("z");
  m_entry_z.select_region(0, m_entry_z.get_text_length());  

  m_entry_label.set_max_length(10);
  m_entry_label.set_text("label");
  m_entry_label.select_region(0, m_entry_label.get_text_length());

  m_point_grid.add(m_entry_x);
  m_point_grid.attach_next_to(m_entry_y, m_entry_x, Gtk::POS_RIGHT, 1, 1);
  m_point_grid.attach_next_to(m_entry_z, m_entry_y, Gtk::POS_RIGHT, 1, 1);
  m_point_grid.attach_next_to(m_entry_label, m_entry_z, Gtk::POS_RIGHT, 1, 1);
  m_point_grid.attach_next_to(m_submit, m_entry_x, Gtk::POS_BOTTOM, 1, 1);
  m_point_grid.attach_next_to(m_add_point, m_submit, Gtk::POS_RIGHT, 1, 1);
  m_point_grid.attach_next_to(m_add_label, m_add_point, Gtk::POS_RIGHT, 2, 1);

  // Add Edges
  m_Box.pack_start(m_edge_frame, Gtk::PACK_EXPAND_WIDGET, 10);

  m_edge_p1.set_max_length(30);
  m_edge_p1.set_text("Label of First Point");
  m_edge_p1.select_region(0, m_edge_p1.get_text_length());

  m_edge_p2.set_max_length(30);
  m_edge_p2.set_text("Label of Second Point");
  m_edge_p2.select_region(0, m_edge_p1.get_text_length());

  m_edge_frame.add(m_edge_grid);
  m_edge_grid.add(m_edge_p1);
  m_edge_grid.attach_next_to(m_edge_p2, m_edge_p1, Gtk::POS_RIGHT, 1, 1);
  m_edge_grid.attach_next_to(m_add_edge, m_edge_p1, Gtk::POS_BOTTOM, 2, 1);
  // m_edge_grid.attach_next_to(m_add_edge, m_edge_submit, Gtk::POS_RIGHT, 1, 1);

  m_add_edge.set_sensitive(false);
  m_create.set_sensitive(false);

  // Create Button
  m_Box.pack_start(m_create, Gtk::PACK_EXPAND_WIDGET, 10);

  // Signal Handlers
  m_submit.signal_clicked().connect(sigc::mem_fun(*this,
      &ConstructWindow::on_button_submit) );
  m_add_point.signal_clicked().connect(sigc::mem_fun(*this,
      &ConstructWindow::on_button_addpoint) );
  m_add_label.signal_clicked().connect(sigc::mem_fun(*this,
      &ConstructWindow::on_button_addlabel) );
  m_add_edge.signal_clicked().connect(sigc::mem_fun(*this,
      &ConstructWindow::on_button_addedge) );
  m_create.signal_clicked().connect(sigc::mem_fun(*this,
    &ConstructWindow::on_button_created) );
  show_all_children();
}

void ConstructWindow::on_button_submit()
{
  std::cout << "Entered text: " << m_entry_x.get_text() << m_entry_y.get_text() 
    << m_entry_z.get_text() << m_entry_label.get_text() << std::endl;
  Point p;
  double x = atof(m_entry_x.get_text().c_str());
  double y = atof(m_entry_y.get_text().c_str());
  double z = atof(m_entry_z.get_text().c_str());
  string label = std::string(m_entry_label.get_text());
  p.setCoordinatesAndLabel(x,y,z,label);
  cp->points.push_back(p);
  if(this->projection==0)
    front->vertices.push_back(*cp);
  else if(this->projection==1)
    top->vertices.push_back(*cp);
  else
    side->vertices.push_back(*cp);
  m_add_edge.set_sensitive(true);
  m_create.set_sensitive(true);
  this->m_entry_x.set_text("x");
  this->m_entry_y.set_text("y");
  this->m_entry_z.set_text("z");
  this->m_entry_label.set_text("label");
}

void ConstructWindow::on_button_addpoint()
{
  std::cout << "Entered text: " << m_entry_x.get_text() << m_entry_y.get_text() 
    << m_entry_z.get_text() << m_entry_label.get_text() << std::endl;
  Point p;
  double x = atof(m_entry_x.get_text().c_str());
  double y = atof(m_entry_y.get_text().c_str());
  double z = atof(m_entry_z.get_text().c_str());
  string label = std::string(m_entry_label.get_text());
  p.setCoordinatesAndLabel(x,y,z,label);
  cp->points.push_back(p);
  if(this->projection==0)
    front->vertices.push_back(*cp);
  else if(this->projection==1)
    top->vertices.push_back(*cp);
  else
    side->vertices.push_back(*cp);
  cp = new ClusteredPoint;
  this->m_entry_x.set_text("x");
  this->m_entry_y.set_text("y");
  this->m_entry_z.set_text("z");
  this->m_entry_label.set_text("label");
}

void ConstructWindow::on_button_addlabel()
{
  std::cout << "Entered text: " <<  m_entry_label.get_text() << std::endl;
  this->m_entry_label.set_text("label");
  Point p;
  double x = atof(m_entry_x.get_text().c_str());
  double y = atof(m_entry_y.get_text().c_str());
  double z = atof(m_entry_z.get_text().c_str());
  string label = std::string(m_entry_label.get_text());
  p.setCoordinatesAndLabel(x,y,z,label);
  cp->points.push_back(p);
  this->m_entry_label.set_text("label");  
}

void ConstructWindow::on_button_addedge()
{
  string label1 = std::string(m_edge_p1.get_text());
  string label2 = std::string(m_edge_p2.get_text());\
  OrthoProjection* currProjection;
  if(this->projection==0) 
    currProjection = this->front;
  else if(this->projection==1) 
    currProjection = this->top;
  else
    currProjection = this->side;
  auto it1 = find_if(currProjection->vertices.begin(),currProjection->vertices.end(),
            [label1] (ClusteredPoint cp) -> bool {
                        int flag = 0;
                        for(int i = 0; i < cp.points.size(); i++) {
                            if(cp.points[i].label==label1)
                                return true;
                        }
                        return false;});
  auto it2 = find_if(currProjection->vertices.begin(),currProjection->vertices.end(),
            [label2] (ClusteredPoint cp) -> bool {
                        int flag = 0;
                        for(int i = 0; i < cp.points.size(); i++) {
                            if(cp.points[i].label==label2)
                                return true;
                        }
                        return false;});
  if(it1!=currProjection->vertices.end() && it2!=currProjection->vertices.end()) {
    Edge2D edge;
    edge.cp1 = *it1;
    edge.cp2 = *it2;
    currProjection->edges.push_back(edge);
  }
  this->m_edge_p1.set_text("Label of First Point");
  this->m_edge_p2.set_text("Label of Second Point");
}

void ConstructWindow::on_button_created()
{
  projection++;
  m_add_edge.set_sensitive(false);
  m_create.set_sensitive(false);
  this->m_entry_x.set_text("x");
  this->m_entry_y.set_text("y");
  this->m_entry_z.set_text("z");
  this->m_entry_label.set_text("label");
  this->m_edge_p1.set_text("Label of First Point");
  this->m_edge_p2.set_text("Label of Second Point");
  cp = new ClusteredPoint;
  if(projection==1) {
    m_create.set_label("Top View Done");
    this->set_title("Top View");
  }
  else if(projection==2) {
    m_create.set_label("Side View Done");
    this->set_title("Side View");
  }
  else {
    this->create = true;
    proj->frontview = *(this->front);
    proj->topview = *(this->top);
    proj->sideview = *(this->side);
    createProjection(proj);
  }
}

ConstructWindow::~ConstructWindow()
{
}