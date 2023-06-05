#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Point.h"

#include "ImageTraversal.h"

namespace Traversals {
  /**
  * Calculates a metric for the difference between two pixels, used to
  * calculate if a pixel is within a tolerance.
  *
  * @param p1 First pixel
  * @param p2 Second pixel
  * @return the difference between two HSLAPixels
  */
  double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) { //DONE
    double h = fabs(p1.h - p2.h);
    double s = p1.s - p2.s;
    double l = p1.l - p2.l;

    // Handle the case where we found the bigger angle between two hues:
    if (h > 180) { h = 360 - h; }
    h /= 360;

    return sqrt( (h*h) + (s*s) + (l*l) );
  }
  
  /**
  * Adds a Point for the bfs traversal to visit at some point in the future.
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  * @param point the point to be added
  */
  void bfs_add(std::deque<Point> & work_list, const Point & point) { //DONE
    /** @todo [Part 1] */
    work_list.push_back(point);
  }

  /**
  * Adds a Point for the dfs traversal to visit at some point in the future.
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  * @param point the point to be added
  */
  void dfs_add(std::deque<Point> & work_list, const Point & point) { //DONE
    /** @todo [Part 1] */
    work_list.push_front(point);
  }

  /**
  * Removes and returns the current Point in the bfs traversal
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  */
  Point bfs_pop(std::deque<Point> & work_list) { //DONE
    /** @todo [Part 1] */
    Point p = work_list.front();
    work_list.pop_front();
    return p;
    // return Point(0, 0);
  }

  /**
  * Removes and returns the current Point in the dfs traversal
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  */
  Point dfs_pop(std::deque<Point> & work_list) { //DONE
    /** @todo [Part 1] */
    Point p = work_list.front();
    work_list.pop_front();
    return p;
    // return Point(0, 0);
  }

  /**
  * Initializes a ImageTraversal on a given `png` image,
  * starting at `start`, and with a given `tolerance`.
  * @param png The image this traversal is going to traverse
  * @param start The start point of this traversal
  * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
  * it will not be included in this traversal
  * @param traversal_add a function pointer to an implemented function which takes in a reference to the work list
  * and the point to be added
  * @param traversal_pop a function pointer to an implemented function which takes in a reference to the work list
  * and returns the next point to be processed in the traversal
  */
  ImageTraversal::ImageTraversal(const PNG & png, const Point & start, double tolerance, add_function traversal_add, pop_function traversal_pop) {  
    /** @todo [Part 1] */
    iter_.png_ = png;
    iter_.start_ = start;
    iter_.tolerance_ = tolerance;
    iter_.traversal_add_ = traversal_add;
    iter_.traversal_pop_ = traversal_pop;
    iter_.current = start;
    // iter_.x.resize(png.width()*png.height());
    
  }

  /**
  * Returns an iterator for the traversal starting at the first point.
  */
  ImageTraversal::Iterator ImageTraversal::begin() {
    /** @todo [Part 1] */
    ImageTraversal hey(iter_.png_,iter_.start_,iter_.tolerance_,iter_.traversal_add_,iter_.traversal_pop_);
    hey.iter_.x.resize(iter_.png_.width()*iter_.png_.height());
    return hey.iter_;
  }

  /**
  * Returns an iterator for the traversal one past the end of the traversal.
  */
  ImageTraversal::Iterator ImageTraversal::end() { //DONE
    /** @todo [Part 1] */
    Iterator hey;
    hey.current = Point(-1,-1);
    return hey;
    // return ImageTraversal(iter_.png_,Point(-1,-1),iter_.tolerance_,iter_.traversal_add_,iter_.traversal_pop_).iter_;

  }

  /**
  * Default iterator constructor.
  */
  ImageTraversal::Iterator::Iterator() {
    /** @todo [Part 1] */
  }

bool ImageTraversal::Iterator::checker(Point p){
    if(p.x < png_.width() && p.y < png_.height() && p.x >=0 && p.y >=0 ){
      if ((calculateDelta(png_.getPixel(p.x,p.y), png_.getPixel(start_.x,start_.y)) < tolerance_)){
        if(x[p.y*png_.width() + p.x] == false)
            return true;
      }
}
return false;
}

  /**
  * Iterator increment opreator.
  *
  * Advances the traversal of the image.
  */
  ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
    /** @todo [Part 1] */
    // x.resize(png_.width()*png_.height());
    x[current.y*png_.width()+current.x] = true;
    Point right = Point(current.x+1, current.y);
    Point below = Point(current.x, current.y+1);
    Point left = Point(current.x-1, current.y);
    Point above = Point(current.x, current.y-1);
    // while(!work_list.empty()) {traversal_pop_(work_list);}
    if (checker(right)){
              traversal_add_(work_list,right);
    }
    if (checker(below)){
              traversal_add_(work_list,below);
    }
    if (checker(left)){
              traversal_add_(work_list,left);
    }
    if (checker(above)){
              traversal_add_(work_list,above);
    }
    if (work_list.empty()){
              traversal_add_(work_list,Point(-1,-1));
              current = traversal_pop_(work_list);
              return *this;
    }

    Point test = work_list.front();
    while(x[test.y*png_.width() + test.x]){
      traversal_pop_(work_list);
      if(work_list.empty()){
            traversal_add_(work_list,Point(-1,-1));
            current = traversal_pop_(work_list);
            return *this;
      }
      test = work_list.front();
    }
    current = traversal_pop_(work_list);
    return *this;
}
  /**
  * Iterator accessor opreator.
  *
  * Accesses the current Point in the ImageTraversal.
  */
  Point ImageTraversal::Iterator::operator*() {
    /** @todo [Part 1] */
    // return Point(0, 0);
    return current;
  }

  /**
  * Iterator inequality operator.
  *
  * Determines if two iterators are not equal.
  */
  bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) { //DONE
    /** @todo [Part 1] */
  Point asd = current;
  Point fds = other.current;
  return !(asd == fds);
  }

}