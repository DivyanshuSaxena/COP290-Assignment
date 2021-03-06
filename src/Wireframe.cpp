#include "Classes.h"
#include <Eigen/Dense>
#include <math.h>
using namespace Eigen;

int Wireframe::normalise() {
    double sumx = 0.0;
    double sumy = 0.0;
    double sumz = 0.0;
    for(int i = 0; i < this->vertices.size(); i++) {
        sumx += this->vertices[i].x;
        sumy += this->vertices[i].y;
        sumz += this->vertices[i].z;
    }
    sumx = sumx/(this->vertices.size());
    sumy = sumy/(this->vertices.size());
    sumz = sumz/(this->vertices.size());
    for(int i = 0; i < this->edges.size(); i++) {
        this->edges[i].p1.x -= sumx;
        this->edges[i].p1.y -= sumy;
        this->edges[i].p1.z -= sumz;
        this->edges[i].p2.x -= sumx;
        this->edges[i].p2.y -= sumy;
        this->edges[i].p2.z -= sumz;
    }
    return 0;
}

Wireframe* Wireframe::projectFrame() {
    ///
    /// Project the frame on xz plane
    ///
    double plane[4] = {0,0,1,0};
    Wireframe* projected;
    projected = new Wireframe;
    for(int i = 0; i < this->edges.size(); i++) {
        Edge edge;
        edge.p1 = edges[i].p1.projectPoint(plane);
        edge.p2 = edges[i].p2.projectPoint(plane);        
        projected->edges.push_back(edge);
    }
    return projected;
}

int Wireframe::rotateFrame(int type) {
    ///
    /// Rotate the Wireframe by ten degrees
    ///
    Matrix3d rot;
    double theta = 0.2;
    double costheta = cos(theta);
    double sintheta = sin(theta);    
    if(type==1) {
        rot << 1, 0, 0,
            0, costheta, sintheta,
            0, -sintheta, costheta;          
    }
    if(type==2) {
        rot << costheta, 0, -sintheta,
            0, 1, 0,
            sintheta, 0, costheta;          
    }
    if(type==3) {
        rot << 1, 0, 0,
            0, costheta, -sintheta,
            0, sintheta, costheta;          
    }
    if(type==4) {
        rot << costheta, 0, sintheta,
            0, 1, 0,
            -sintheta, 0, costheta;             
    }
    for(int i = 0; i < this->edges.size(); i++) {
        Vector3d p1(edges[i].p1.x,edges[i].p1.y,edges[i].p1.z);
        Vector3d p2(edges[i].p2.x,edges[i].p2.y,edges[i].p2.z);
        Vector3d p1new = rot*p1;
        Vector3d p2new = rot*p2;
        edges[i].p1.setCoordinates(p1new.x(),p1new.y(),p1new.z());
        edges[i].p2.setCoordinates(p2new.x(),p2new.y(),p2new.z()); 
    }
    return 0; 
}