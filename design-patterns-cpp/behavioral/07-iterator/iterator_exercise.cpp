#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

template <typename T>
struct Node
{
    T value;
    Node *left{nullptr}, *right{nullptr}, *parent{nullptr};

    Node(T value) : value(value) {}

    Node(T value, Node<T> *left, Node<T> *right) : value(value), left(left), right(right) {
      left->parent = right->parent = this;
    }

    void preorder_traversal_impl(Node<T>* current, std::vector<Node<T>*>& result)
    {
      result.push_back(current);

      if (current->left)
      {
        preorder_traversal_impl(current->left, result);
      }

      if (current->right)
      {
        preorder_traversal_impl(current->right, result);
      }
    }

    void postorder_traversal_impl(Node<T>* current, std::vector<Node<T>*>& result)
    {
      if (current->left)
      {
        postorder_traversal_impl(current->left, result);
      }
      if (current->right)
      {
        postorder_traversal_impl(current->right, result);
      }

      result.push_back(current);
    }

    void inorder_traversal_impl(Node<T>* current, std::vector<Node<T>*>& result)
    {
      if (current->left)
      {
        inorder_traversal_impl(current->left, result);
      }

      result.push_back(current);

      if (current->right)
      {
        inorder_traversal_impl(current->right, result);
      }
    }

    // traverse the node and its children preorder
    // and put all the results into `result`
    void preorder_traversal(std::vector<Node<T>*>& result)
    {
      preorder_traversal_impl(this, result);
    }

    void postorder_traversal(std::vector<Node<T>*>& result)
    {
      postorder_traversal_impl(this, result);
    }

    void inorder_traversal(std::vector<Node<T>*>& result)
    {
      inorder_traversal_impl(this, result);
    }
};

int main(int ac, char* av[])
{
  Node<char> c{'c'};
  Node<char> d{'d'};
  Node<char> e{'e'};
  Node<char> b{'b', &c, &d};
  Node<char> a{'a', &b, &e};

  ostringstream oss;
  // Preorder Traversal
  std::vector<Node<char>*> pre_result;
  a.preorder_traversal(pre_result);

  for (auto n : pre_result)
    oss << n->value;

  std::cout << oss.str() << std::endl;
  oss.str("");
  oss.clear();

  // Postorder Traversal
  std::vector<Node<char>*> post_result;
  a.postorder_traversal(post_result);

  for (auto n : post_result)
    oss << n->value;

  std::cout << oss.str() << std::endl;
  oss.str("");
  oss.clear();

  // Inorder Traversal
  std::vector<Node<char>*> in_result;
  a.inorder_traversal(in_result);

  for (auto n : in_result)
    oss << n->value;

  std::cout << oss.str() << std::endl;
  oss.str("");
  oss.clear();

  return 0;
}