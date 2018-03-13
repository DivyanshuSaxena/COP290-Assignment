#include "Classes.h"
#include <algorithm>
using namespace std;


Wireframe Projection2D::create3D(){
    allpoints = determineAllPoints();
    determineIntersectedEdges();
    executeCorollary1();
    chkif3edgesanddefthem();
    while(numofpossibleedge()!=0){
        //function below checks if for a point a possible and definite point are collinear and removes the possible point
        bool ifcollinearpossanddef = chkcollinearpossanddef();
        bool ifcollinearpossandposs = chkcollinearpossandposs();


    }
    // vector<Edge> doublecalculatedpossibleedges;
    // // doublecalculatedpossibleedges has all the edges calculated twice
    // vector<vector<Edge> > correspondingpossibleedges;
    // vector<vector<Point> > correspondingtopviewneighbours;
    // vector<vector<Point> > correspondingfronviewneighbours;
    // vector<Edge> definiteedges;
    // for(auto allpointitr = allpoints.begin();allpointitr!=allpoints.begin();allpointitr++){
    //     vector<Point> topviewpossibleneighbours = topview.possibleNeighbours(*(allpointitr));
    //     vector<Point> frontviewpossibleneighbours = frontview.possibleNeighbours(*(allpointitr));
    //     vector<Edge> possibleedges = determinePossibleEdges(*(allpointitr),&(topviewpossibleneighbours),&(frontviewpossibleneighbours),&(allpoints));
    //     for(auto possibleedgesitr = possibleedges.begin();possibleedgesitr!=possibleedges.end();possibleedgesitr++){
    //         doublecalculatedpossibleedges.push_back(* possibleedgesitr);
    //     }
    //     correspondingpossibleedges.push_back(possibleedges);
    //     correspondingtopviewneighbours.push_back(topviewpossibleneighbours);
    //     correspondingfronviewneighbours.push_back(frontviewpossibleneighbours);
    //     //same cluster from top and corresponding in front
    //     Point thispoint = * allpointitr;
    //     vector<Point> sametopcluster = topview.sameclusterpoints(* (allpointitr));
    //     for(auto sametopclusteritr = sametopcluster.begin();sametopclusteritr!=sametopcluster.end();sametopclusteritr++){
    //         auto corresfrontpointptr = find_if(frontviewpossibleneighbours.begin(),frontviewpossibleneighbours.end(),[sametopclusteritr](Point p)->bool{
    //             return(sametopclusteritr->label==p.label);
    //         });
    //         if(corresfrontpointptr!= frontviewpossibleneighbours.end()){
    //             Edge definitepoint;
    //             definitepoint.p1 = *allpointitr;
    //             definitepoint.p2 = determinePoint(*sametopclusteritr,*corresfrontpointptr);
    //             definiteedges.push_back(definitepoint);
    //         }
    //     }
    //     //same cluster from front and corresponding in top
    //     thispoint = * allpointitr;
    //     vector<Point> samefrontcluster = frontview.sameclusterpoints(* (allpointitr));
    //     for(auto samefrontclusteritr = samefrontcluster.begin();samefrontclusteritr!=samefrontcluster.end();samefrontclusteritr++){
    //         auto correstoppointptr = find_if(topviewpossibleneighbours.begin(),topviewpossibleneighbours.end(),[samefrontclusteritr](Point p)->bool{
    //             return(samefrontclusteritr->label==p.label);
    //         });
    //         if(correstoppointptr!= topviewpossibleneighbours.end()){
    //             Edge definitepoint;
    //             definitepoint.p1 = *allpointitr;
    //             definitepoint.p2 = determinePoint(*samefrontclusteritr,*correstoppointptr);
    //             definiteedges.push_back(definitepoint);
    //         }
    //     }
        //corollary 1 complete
        
}

//  kl   //doublecalculaedpossibleedges has all the edges calculated twice now


vector<Point> Projection2D::determineAllPoints(){
    vector<Point> answer;
    for(auto it=(frontview.vertices.begin());it!=frontview.vertices.end();it++){
        for(auto nestit=(it->points.begin());nestit!=it->points.end();nestit++){
            string thislabel = nestit->label;
            for(auto itfind=topview.vertices.begin();itfind!=topview.vertices.end();itfind++){
                bool found = false;
                for(auto nestitfind=itfind->points.begin();nestitfind!= itfind->points.end();nestitfind++){
                    string findlabel = nestitfind->label;
                    if(thislabel==findlabel){
                        found=true;
                        Point determinedpoint = determinePoint(*nestit, *nestitfind);
                        answer.push_back(determinedpoint);
                        int sizeanswer = answer.size();
                        determinedpoint.adjacencyIndex=sizeanswer-1;
                        indextopointmap.insert(make_pair(sizeanswer-1,&determinedpoint));
                        labeltopointmap.insert(make_pair(determinedpoint.label,&determinedpoint));
                        //knownpoints.push_back(&determinedpoint);
                        break;
                    }
                    
                }
                if(found==true){
                    break;
                }
            }

        }
    }
    int numpoints = answer.size();
    
    //adjacencyMatrix(numpoints,temp);
    for(int i=0;i<numpoints;i++){
        vector<int> temp(numpoints,0);
        adjacencyMatrix.push_back(temp);
    }
    return answer;
}

Point Projection2D::determinePoint(Point pfront, Point ptop) {
    ///
    /// This function extends the points from the top view and front view to give the 3D projection of the Point
    ///
    Point coincidingpoint;
    if(!(pfront.x == ptop.x)){
        //throw exception that not possible
        cout << "not possible projection" << endl;
    }
    coincidingpoint.setCoordinatesAndLabel(ptop.x,ptop.y,pfront.z,ptop.label);
    return coincidingpoint;
}

vector<Edge> Projection2D::determinePossibleEdges(Point vertex, vector<Point> *topneighbourptr, vector<Point> *frontneighbourptr) {
    ///
    /// This function determines the edges containing the Point vertex as one of the endpoints
    /// By interpreting its neighbours from the top view and front view
    ///
    vector<Edge> answer;
    vector<Point> intersection;
    vector<Point> topneighbour = * (topneighbourptr);
    vector<Point> frontneighbour = * (frontneighbourptr);
    for(auto topneighbouritr=topneighbourptr->begin();topneighbouritr!=topneighbourptr->end();topneighbouritr++){
        auto correspondingpointinfrontasptr = find_if(frontneighbourptr->begin(),frontneighbourptr->end(),[topneighbouritr](Point p)->bool{
            if(p.label==topneighbouritr->label){
                return true;
            }else{
                return false;
            }
        });
        if(correspondingpointinfrontasptr!=frontneighbourptr->end()){
            Point collidedpoint = determinePoint(*(topneighbouritr),*(correspondingpointinfrontasptr));
            intersection.push_back(collidedpoint);
        }
    }
    for(auto intersectionitr = intersection.begin();intersectionitr!=intersection.end();intersectionitr++){
        Edge tempedge;
        tempedge.p1 = vertex;
        tempedge.p2 = *(labeltopointmap[intersectionitr->label]);
        int i = vertex.adjacencyIndex;
        int j = labeltopointmap[intersectionitr->label]->adjacencyIndex;
        adjacencyMatrix[i][j]=adjacencyMatrix[i][j]+1;
        adjacencyMatrix[j][i]=adjacencyMatrix[j][i]+1;
        answer.push_back(tempedge);
    }
    return answer;
    
}

void Projection2D::determineIntersectedEdges(){
    for(auto pointitr=allpoints.begin();pointitr!=allpoints.end();pointitr++){
        vector<Point> topneighbours = topview.possibleNeighbours(* pointitr);
        vector<Point> frontneighbours = frontview.possibleNeighbours(* pointitr);
        vector<Point> sideneighbours = sideview.possibleNeighbours(* pointitr);
        vector<Edge> topAndFront = determinePossibleEdges(*pointitr,&topneighbours,&frontneighbours);
        vector<Edge> sideAndFront = determinePossibleEdges(*pointitr,&sideneighbours,&frontneighbours);
        int numpoints = allpoints.size();
        for(int i = 0; i<numpoints;i++){
            for(int j=0;j<numpoints;j++){
                if(adjacencyMatrix[i][j]==2){
                    adjacencyMatrix[i][j] =1;
                }else if(adjacencyMatrix[i][j]==1){
                    adjacencyMatrix[i][j]=0;
                }
            }
        }

    }
}

void Projection2D::executeCorollary1onebyone(OrthoProjection* view1, OrthoProjection* view2){
    for(auto clusteritr = view1->vertices.begin();clusteritr!=view1->vertices.end();clusteritr++){
        if(clusteritr->points.size()==2){
            bool isconnectedinotherview = view2->isConnected(clusteritr->points[0].label,clusteritr->points[1].label);
            if(isconnectedinotherview){
                int i = labeltopointmap[clusteritr->points[0].label]->adjacencyIndex;
                int j = labeltopointmap[clusteritr->points[1].label]->adjacencyIndex;
                if(adjacencyMatrix[i][j]==1 || adjacencyMatrix[j][i]==1){
                    adjacencyMatrix[i][j] = 2;
                }               
            }     
        }
    }
}
void Projection2D::executeCorollary1(){
    executeCorollary1onebyone(&topview,&frontview);
    executeCorollary1onebyone(&frontview,&topview);
    executeCorollary1onebyone(&frontview,&sideview);
    executeCorollary1onebyone(&sideview,&frontview);
    executeCorollary1onebyone(&topview,&sideview);
    executeCorollary1onebyone(&sideview,&topview);
}
void Projection2D::chkif3edgesanddefthem(){
    int numpointsall = allpoints.size();
    for(int i=0; i<numpointsall;i++){
        int numedge = count_if(adjacencyMatrix[i].begin(),adjacencyMatrix[i].end(),[](int v)->bool{
            return(v>0);
        });
        if(numedge==3){
            for(int j=0;j<numpointsall;j++){
                if(adjacencyMatrix[i][j]==1){
                    adjacencyMatrix[i][j] =2;
                }
            }
        }
    }
}
int Projection2D::numofpossibleedge(){
    int num1=0;
    int numpointsall = allpoints.size();
    for(int i=0;i<numpointsall;i++){
        num1 = num1 + count(adjacencyMatrix[i].begin(),adjacencyMatrix[i].end(),1);
    }
    return num1;
}
bool Projection2D::chkcollinearpossanddef(){
    int numpoints = allpoints.size();
    bool ret =false;
    for(int i=0;i<numpoints;i++){
        Point * thispoint = & (allpoints[i]);
        vector<int> thisvec = adjacencyMatrix[i];
        int numposs = count(thisvec.begin(),thisvec.end(),1);
        int numdef = count(thisvec.begin(),thisvec.end(),2);
        if(numposs>0 && numdef>0){
            vector<int> defindexvec;
            for(int j=0;j<numpoints;j++){
                if(thisvec[j]==2){
                    defindexvec.push_back(j);
                }
            }
            for(int j=0;j<numpoints;numpoints++){
                if(thisvec[j]==1){
                    Point * posspoint = (indextopointmap[j]);
                    for(auto defindexvecitr = defindexvec.begin();defindexvecitr!=defindexvec.end();defindexvecitr++){
                        Point * defpoint = indextopointmap[(* defindexvecitr)];
                        bool iscollinear = thispoint->checkcollinear(posspoint, defpoint);
                        if(iscollinear){
                            adjacencyMatrix[i][j] =0;
                            adjacencyMatrix[j][i] = 0;
                            ret = true;
                            break;
                        }
                    }
                }
            }
        }
    }
    return ret;
}
bool Projection2D::chkcollinearpossandposs(){
    int numpoints = allpoints.size();
    bool ret =false;
    for(int i=0;i<numpoints;i++){
        Point * thispoint = & (allpoints[i]);
        vector<int> thisvec = adjacencyMatrix[i];
        int numposs = count(thisvec.begin(),thisvec.end(),1);
        int numdef = count(thisvec.begin(),thisvec.end(),2);
        if(numposs>=2){
            for(int j=0;j<numpoints;j++){
                if(adjacencyMatrix[i][j]==1){
                    for(int k=0;k<numpoints;k++){
                        if(adjacencyMatrix[i][k]==1){
                            if(indextopointmap[i]->checkcollinear(indextopointmap[j],indextopointmap[k])){
                                Point * jpointptr = indextopointmap[j];
                                Point * kpointptr = indextopointmap[k];
                                vector<Point> topcluster = topview.sameclusterpoints(*thispoint);
                                auto jiterator = find_if(topcluster.begin(),topcluster.end(),[jpointptr](Point p)->bool{
                                    return(jpointptr->label==p.label);
                                });
                                if(jiterator!=topcluster.end()){
                                    auto kiterator = find_if(topcluster.begin(),topcluster.end(),[kpointptr](Point p)->bool{
                                        return(kpointptr->label==p.label);
                                    });
                                    if(kiterator!=topcluster.end()){
                                        if(topcluster.begin()->label==thispoint->label || topcluster.end()->label==thispoint->label){
                                            Vector3d a1 = 
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return ret;
}
