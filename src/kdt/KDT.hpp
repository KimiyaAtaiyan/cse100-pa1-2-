#ifndef KDT_HPP
#define KDT_HPP

#include <math.h>     // pow, abs
#include <algorithm>  // sort, max, min
#include <limits>     // numeric_limits<type>::max()
#include <vector>     // vector<typename>
#include "Point.hpp"

using namespace std;

class KDT {
  private:
    /** Inner class which defines a KD tree node */
    class KDNode {
      public:
        KDNode* left;
        KDNode* right;
        Point point;

        KDNode(Point point) : point(point) {}
    };

    // root of KD tree
    KDNode* root;

    // number of dimension of data points
    unsigned int numDim;

    // smallest squared distance to query point so far
    double threshold;

    unsigned int isize;
    int iheight;

    // current nearest neighbor
    Point nearestNeighbor;

    // Extra Credit: smallest bounding box containing all points
    vector<pair<double, double>> boundingBox;

    // Extra Credit: result container
    // (Set during searching, and clear before another search)
    vector<Point> pointsInRange;

  public:
    /** Constructor of KD tree */
    KDT()
        : root(0),
          numDim(0),
          threshold(numeric_limits<double>::max()),
          isize(0),
          iheight(-1) {}

    /** Destructor of KD tree */
    virtual ~KDT() { deleteAll(root); }

    void build(vector<Point>& points) {
    	
	//if vector is empty, return directly
    	if(points.empty()){
		return;
	}

	this->numDim = points[0].numDim;
	int height = iheight;
	this->isize = points.size();
	int dim = this->numDim;


	root = buildSubtree(points, 0, points.size(), dim, height);

    }

    /*
     * Function name: findNearestNeighbor
     * Function Prototype: Point* findNearestNeigbor(Point & queryPoint)
     * Description : Find the nearest neighbor to the Point queryPoint, using its helper
     * 			method findNNHelper
     * Return: Pointer to points with closest distance to querypoint, nullptr if KD Tree empty
     */
    Point* findNearestNeighbor(Point& queryPoint) {


   	//if KD Tree is empty, return nullptr
	if(isize == 0){
		return nullptr;
	}

   	int curDim = 0;

   	findNNHelper(root, queryPoint, curDim);
   
	return nullptr; //WHAT GETS RETURNED HERE????????????????????
   
    }

    /** Extra credit */
    vector<Point> rangeSearch(vector<pair<double, double>>& queryRegion) {
        return {};
    }

    unsigned int size() const { 
    
    	return isize;
    }

    int height() const {
   
   	return iheight;
    }

  private:

    KDNode* buildSubtree(vector<Point>& points, unsigned int start,
                         unsigned int end, unsigned int curDim, int height) {

	    	if( start < end){
			
			//sort the vector comparing curDim values
			sort(points.begin(), points.end()-1 , CompareValueAt(curDim));

	    		//find median
    			int median = ((end-start)/2) + start;
		
			//check if dimension valid, otherwise reset dimension
			if(curDim > numDim){
				curDim = 0;
			}	
			
			KDNode * curr = new KDNode(points[median]);
			height++;
			curr->left = buildSubtree(points, 0, median, curDim++, height);
			curr->right = buildSubtree(points, median+1, points.size(),curDim++, height);
			
			//set iheight
			if( height > iheight ){
				
				iheight = height;
			}	
	  	}
		else{
			return new KDNode(points[start]);  
		}

    }	

    /** TODO */
    void findNNHelper(KDNode* node, Point& queryPoint, unsigned int curDim) {
    
    	//compare query point do corresponding dimension to guide left or right
	KDNode* temp = node;

	if(curDim > numDim){
		curDim = 0;
	}

	if(temp != 0){

		//Go left if query-value at current dimension is less than node-value
		if( queryPoint.valueAt(curDim) < temp->point.valueAt(curDim)){

			temp = temp->left;
			curDim++;
			
			findNNHelper(temp, queryPoint, curDim);




			//compare treshhold to parent[dimension], if (curr.dim - query.dim)^2 < treshhold go right
			if(pow(temp->point.valueAt(curDim)- queryPoint.valueAt(curDim),2) < threshold){

				temp = temp->right;
				findNNHelper(temp, queryPoint,curDim);

			}	

		}
		else if( queryPoint.valueAt(curDim) > temp->point.valueAt(curDim)){

			temp = temp->right;
			curDim++;
			findNNHelper(temp, queryPoint, curDim);


			if(pow(temp->point.valueAt(curDim) - queryPoint.valueAt(curDim),2) < threshold){

				temp = temp->left;
				findNNHelper(temp, queryPoint, curDim);
			}

		}
		else{ //if equal, always go right

			temp = temp->right;
			curDim++;

			findNNHelper(temp, queryPoint, curDim);

			if(pow(temp->point.valueAt(curDim) - queryPoint.valueAt(curDim),2) < threshold){

				temp = temp->left;
				findNNHelper(temp, queryPoint, curDim);
			}
		}

		//calculate treshhold
		
		node->point.setDistToQuery(queryPoint); 	//distance to current point

		if( threshold > node->point.distToQuery){

			nearestNeighbor = node->point;
			nearestNeighbor.setDistToQuery(queryPoint);
			threshold = nearestNeighbor.distToQuery;
		}

	}
	else{
		return;
	}

    }

    /** Extra credit */
    void rangeSearchHelper(KDNode* node, vector<pair<double, double>>& curBB,
                           vector<pair<double, double>>& queryRegion,
                           unsigned int curDim) {}

    /** TODO */
    static void deleteAll(KDNode* n) {}

    // Add your own helper methods here
};
#endif  // KDT_HPP
