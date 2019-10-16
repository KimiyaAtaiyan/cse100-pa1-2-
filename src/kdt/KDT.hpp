/*
 * Author: Kimiya Ataiyan 
 * UserID: kataiyan 
 * Date: 10/12/19
 * Filename: KDT.hpp
 */

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
		virtual ~KDT() { 

			deleteAll(root); 
		}


		/*
		 * Function name: build 
		 * Function Prototype: void build(vector<Point>& points)
		 * Description: calls the helper function buildSubtree, in order
		 * 			to recursively build KDT, and sets member variable root
		 * 	Return: none
		 */
		void build(vector<Point>& points) {

			//if vector is empty, return directly
			if(points.empty()){
				return;
			}

			this->numDim = points[0].numDim;
			int height = iheight;
			this->isize = points.size();


			root = buildSubtree(points, 0, points.size(), 0 , height);

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

			threshold =numeric_limits<double>::max();
			return &nearestNeighbor;

		}

		/** Extra credit */
		vector<Point> rangeSearch(vector<pair<double, double>>& queryRegion) {
			return {};
		}

		/* 
		 * Function name: size
		 * Function Prototype: unsigned int size() const 
		 * Description: returns the size (number of nodes) of KDT
		 * Return: unsigned int
		 */

		unsigned int size() const { 

			return isize;
		}

		/*
		 * Function name: height
		 * Function Prototype: int height() const
		 * Description: returns the height of the KDT 
		 * Return: int 
		 */
		int height() const {

			return iheight;
		}

	private:

		/* 
		 * Function Name: buildSubtree
		 * Function Prototype: KDNode * buildSubtree(vector<Point> & points, unsigned int start, unsigned int end,
		 * 				unsigned int curDim, int height)
		 * 	Description: Helper method that recurively uilds the kdt tree in which each level compares a different dimensio
		 * 				n of the Point in order
		 * 				to determine left and right subtrees. Height of the tree gets set in this function too
		 * 	Return: KDNode* which will is a pointer to KDNode object containing Point,left and right
		 */

		KDNode* buildSubtree(vector<Point>& points, unsigned int start,
				unsigned int end, unsigned int curDim, int height) {


			if( start < end){

				//sort the vector comparing curDim values
				sort(points.begin()+start, points.begin() + end, CompareValueAt(curDim));

				//find median
				int median = floor((start + end) /2);

				//check if dimension valid, otherwise reset dimension
				if(!(curDim < numDim)){
					curDim = 0;
				}	
				else{
					curDim++;
				}

				KDNode * curr = new KDNode(points[median]);
				height++;
				curr->left = buildSubtree(points, start, median, curDim, height);
				curr->right = buildSubtree(points, median+1, end ,curDim, height);

				//set iheight
				if( height > iheight ){

					iheight = height;
				}


				return curr;
			}
			else{
				return nullptr;
			}

		}	

		/*
		 * Function name: findNNHelper
		 * Function Prototype: void findNNHelper(KDNode* node, Point& queryPoint, unsgined int curDim)
		 * Description:  Helper function that gets called in findNearestNeighbor in order to find 
		 * 			the point with the closests distance in the kdt to queryPoint
		 * Return: none
		 */
		void findNNHelper(KDNode* node, Point& queryPoint, unsigned int curDim) {

			//compare query point do corresponding dimension to guide left or right
			KDNode* temp = node;

			if(curDim > numDim){
				curDim = 0;
			}

			if(temp != nullptr){

				//Go left if query-value at current dimension is less than node-value
				if( queryPoint.valueAt(curDim) < temp->point.valueAt(curDim)){

					temp = temp->left;
					curDim++;

					findNNHelper(temp, queryPoint, curDim);


					if(temp != nullptr){
						//compare treshhold to parent[dimension], if (curr.dim - query.dim)^2 < treshhold go right
						if(pow(temp->point.valueAt(curDim)- queryPoint.valueAt(curDim),2) < threshold){

							temp = temp->right;
							findNNHelper(temp, queryPoint,curDim);

						}	
					}

				}
				else{ //if equal, always go right

					temp = temp->right;
					curDim++;

					findNNHelper(temp, queryPoint, curDim);

					if(temp != nullptr){
						if(pow(temp->point.valueAt(curDim) - queryPoint.valueAt(curDim),2) < threshold){

							temp = temp->left;
							findNNHelper(temp, queryPoint, curDim);
						}
					}
				}

				//calculate treshhold

				node->point.setDistToQuery(queryPoint); 	//distance to current point

				if( threshold > node->point.distToQuery){

					nearestNeighbor = node->point;
					threshold = node->point.distToQuery;
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

		/*
		 * Function name: deleteAll
		 * Function Prototype: static vpid deleteAll(KDNode* n)
		 * Description: deletes all the nodes in the KDT
		 * Return: none
		 */
		static void deleteAll(KDNode* n) {

			if(n == nullptr){
				return;
			}

			deleteAll(n->left);
			deleteAll(n->right);
			delete n;


		}

		// Add your own helper methods here
};
#endif  // KDT_HPP
