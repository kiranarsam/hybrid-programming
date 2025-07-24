#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

template <typename T>
struct BinaryTree;

// todo: refactor to refer to parent instead of entire tree
template <typename T>
struct Node
{
  T value = T();
  Node<T> *left = nullptr;
  Node<T> *right = nullptr;
  Node<T> *parent = nullptr;
  BinaryTree<T>* tree = nullptr;

  explicit Node(const T& value) : value(value)
  {
  }

  Node(const T& value, Node<T>* const left, Node<T>* const right)
    : value(value),
      left(left),
      right(right)
  {
    this->left->tree = this->right->tree = tree;
    this->left->parent = this->right->parent = this;
  }

  void set_tree(BinaryTree<T>* t)
  {
    tree = t;
    if (left) left->set_tree(t);
    if (right) right->set_tree(t);
  }

  ~Node()
  {
    if (left) delete left;
    if (right) delete right;
  }
};

template <typename T>
struct BinaryTree
{
  Node<T>* root = nullptr;

  explicit BinaryTree(Node<T>* const root)
    : root{ root }, pre_order{ *this }
  {
    root->set_tree(this);
  }

  ~BinaryTree() { if (root) delete root; }

  template <typename U>
  struct PreOrderIterator
  {
    Node<U>* current;

    explicit PreOrderIterator(Node<U>* current)
      : current(current)
    {
    }

    bool operator!=(const PreOrderIterator<U>& other)
    {
      return current != other.current;
    }

    // no continuations in C++ (unlike C#)
    PreOrderIterator<U>& operator++()
    {
      if (current->right)
      {
        current = current->right;
        while (current->left)
          current = current->left;
      }
      else
      {
        Node<T>* p = current->parent;
        while (p && current == p->right)
        {
          current = p;
          p = p->parent;
        }
        current = p;
      }
      return *this;
    }

    Node<U>& operator*() { return *current; }
  };

  typedef PreOrderIterator<T> iterator;

  iterator end()
  {
    return iterator{ nullptr };
  }

  iterator begin()
  {
    Node<T>* n = root;

    if (n)
      while (n->left)
        n = n->left;
    return iterator{ n };
  }

  // expose as a traversal object
  // todo: make this inorder
  class pre_order_traversal
  {
    BinaryTree<T>& tree;
  public:
    pre_order_traversal(BinaryTree<T>& tree) : tree{tree} {}
    iterator begin() { return tree.begin(); }
    iterator end() { return tree.end(); }
  } pre_order;
};

void std_iterators()
{
  std::vector<std::string> names{ "john", "jane", "jill", "jack" };

  std::vector<std::string>::iterator it = names.begin(); // or begin(names)
  std::cout << "first name is " << *it << "\n";


  ++it; // advance the iterator
  it->append(std::string(" goodall"));
  std::cout << "second name is " << *it << "\n";

  while (++it != names.end())
  {
    std::cout << "another name: " << *it << "\n";
  }

  // traversing the entire vector backwards
  // note global rbegin/rend, note ++ not --
  // expand auto here
  for (auto ri = std::rbegin(names); ri != std::rend(names); ++ri)
  {
    std::cout << *ri;
    if (ri + 1 != std::rend(names)) // iterator arithmetic
      std::cout << ", ";
  }
  std::cout << std::endl;

  // constant iterators
  std::vector<std::string>::const_reverse_iterator jack = std::crbegin(names);
  // won't work
  //*jack += "test";
}

// in order traversal
void binary_tree_iterator()
{
  //         me
  //        /  \
  //   mother   father
  //      / \
  //   m'm   m'f

  BinaryTree<std::string> family{
    new Node<std::string>{"me",
      new Node<std::string>{"mother",
        new Node<std::string>{"mother's mother"},
        new Node<std::string>{"mother's father"}
      },
      new Node<std::string>{"father"}
    }
  };

  // pre order traversal
  for (auto it = family.begin(); it != family.end(); ++it)
  {
    std::cout << (*it).value << "\n";
  }

  std::cout << "=== and now, through a dedicated object:\n";

  // use iterator name
  for (const auto& it: family.pre_order)
  {
    std::cout << it.value << "\n";
  }
}


int main(int argc, char **argv)
{
  std_iterators();
  binary_tree_iterator();

  return 0;
}
