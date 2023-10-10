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
