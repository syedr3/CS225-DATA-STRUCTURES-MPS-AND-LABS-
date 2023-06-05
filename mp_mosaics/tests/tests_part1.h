#pragma once

static inline void rtrim(std::string &s);
bool tree_equals_output(stringstream & s, string filename);
void compareBinaryFiles( string yourFile, string ourFile );

template <int Dim>
void writeKdTreeToFile(const KDTree<Dim>& tree, string fname)
{
  ofstream outputFile(fname, ofstream::out);
  tree.printTree(outputFile, colored_out::DISABLE, -1);
  outputFile.close();
}

//
// Check is range is sorted
//
template <typename RandIter, class Comparator>
bool isSorted(RandIter cur, RandIter end, Comparator cmp) {
  RandIter prev = cur++;
  while(cur != end) {
    if(!cmp(*prev, *cur)) {
      return false;
    }
    ++cur;
    ++prev;
  }
  return false;
}
//
// point vector constructor
//
template <int K>
vector<Point<K>> _point_vector_constructor(int size) {
  vector<Point<K>> points;
  points.reserve(size);
  for (int i = 0; i < size; i++) {
      Point<K> p;
      for (int j = 0; j < K; j++)
          p[j] = i;
      points.push_back(p);
  }
  return points;
}

//
// Simple Constructor
//
template <int K>
void _test_linear_constructor(int size) {
  vector<Point<K>> points = _point_vector_constructor<K>(size);

  KDTree<K> tree(points);
  std::string fname = "kdtree_"+to_string(K)+"_"+to_string(size)+"-actual.kd";
  writeKdTreeToFile(tree,fname);
  compareBinaryFiles(fname, "../data/kdtree_"+to_string(K)+"_"+to_string(size)+"-expected.kd" );
  REQUIRE(true);
}

//
// Simple Nearest Neighbor
//
template <int K>
void _test_linear_nearestNeighbor(int size) {
  vector<Point<K>> points;
  points.reserve(size);
  for (int i = 0; i < size; i++) {
      Point<K> p;
      for (int j = 0; j < K; j++)
          p[j] = i;
      points.push_back(p);
  }

  KDTree<K> tree(points);
  for (int i = 0; i < size; i++) {
    REQUIRE ( tree.findNearestNeighbor(points[i]) == points[i] );
  }
}