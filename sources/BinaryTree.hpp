
#pragma once
#include <queue>
#include <ostream>
#include <exception>
#include <memory>
#include <iostream>
#include <typeinfo>

using namespace std;

namespace ariel
{

    template <typename T>
    class BinaryTree
    {

    private:
        class Node
        {
        public:
            shared_ptr<Node> right;
            shared_ptr<Node> left;
            T _data;
            Node(const T &data) : _data(data), right(nullptr), left(nullptr){};

            Node(const shared_ptr<Node> &node) : _data(node->_data), right(nullptr), left(nullptr)
            {
                if (node == nullptr)
                {
                    return;
                }

                if (node->left != nullptr)
                {
                    left = make_shared<Node>(node->left);
                }
                if (node->right != nullptr)
                {

                    right = make_shared<Node>(node->right);
                }
            }
        };
        shared_ptr<Node> _root;

        shared_ptr<Node> findNode(const T &key, shared_ptr<Node> node)
        {
            if (node == nullptr)
            {
                return nullptr;
            }
            if (node->_data == key)
            {
                return node;
            }

            shared_ptr<Node> leftNode = findNode(key, node->left);
            if (leftNode != nullptr)
            {
                return leftNode;
            }

            shared_ptr<Node> rightNode = findNode(key, node->right);

            return rightNode;
        }

    public:
        BinaryTree() : _root(nullptr){};
        BinaryTree(const BinaryTree<T> &other_binary_tree) : _root(nullptr)
        {

            if (other_binary_tree._root == nullptr)
            {
                _root = nullptr;
            }
            else
            {
                _root = make_shared<Node>(other_binary_tree._root);
            }
        }
        BinaryTree(BinaryTree &&other_binary_tree) noexcept : _root(nullptr)
        {

            if (other_binary_tree._root != nullptr)
            {
                _root = other_binary_tree._root;
            }
        }

        BinaryTree &operator=(BinaryTree &&other_binary_tree) noexcept
        {
            if (other_binary_tree._root != nullptr)
            {
                _root = other_binary_tree._root;
            }
            return *this;
        }

        BinaryTree &operator=(const BinaryTree &otherBinaryTree)
        {

            if (this != &otherBinaryTree)
            {
                _root = make_shared<Node>(otherBinaryTree._root);
            }
            return *this;
        }

        ~BinaryTree(){};

        BinaryTree &add_root(const T &root)
        {
            if (_root == nullptr)
            {
                _root = make_shared<Node>(root);
            }
            else
            {
                _root->_data = root;
            }

            return *this;
        }
        BinaryTree &add_left(const T &father, const T &chaild)
        {
            if (_root == nullptr)
            {
                throw invalid_argument("illegal action: you need root befor to add left child");
            }
            shared_ptr<Node> n = findNode(father, _root);

            if (n != nullptr && n->left == nullptr)
            {

                n->left = make_shared<Node>(chaild);
            }
            else if (n != nullptr)
            {
                n->left->_data = chaild;
            }
            else
            {
                throw invalid_argument("illegal action: this fathe dont exist");
            }

            return *this;
        }

        BinaryTree &add_right(const T &father, const T &chaild)
        {

            shared_ptr<Node> n = findNode(father, _root);

            if (n != nullptr && n->right == nullptr)
            {

                n->right = make_shared<Node>(chaild);
            }
            else if (n != nullptr)
            {
                n->right->_data = chaild;
            }
            else
            {
                throw invalid_argument("illegal action: this fathe dont exist");
            }

            return *this;
        }

        friend ostream &operator<<(ostream &out, const BinaryTree &b)
        {
            return out << b._root->_data;
        }

        class iterator
        {

        public:
            queue<shared_ptr<Node>> queue_binaryTree;

            iterator(){};

            void travel(shared_ptr<Node> tree);

            T &operator*()
            {

                return (queue_binaryTree.front()->_data);
            }
            T *operator->()
            {
                return &(queue_binaryTree.front()->_data);
            }

            iterator &operator++()
            {
                queue_binaryTree.pop();
                return *this;
            }
            iterator operator++(int)
            {
                iterator temp = *this;
                queue_binaryTree.pop();
                return temp;
            }

            bool operator==(const iterator &it) const
            {

                return ((queue_binaryTree.front()) == (it.queue_binaryTree.front()));
            }
            bool operator!=(const iterator &it) const
            {
                return ((queue_binaryTree.front()) != (it.queue_binaryTree.front()));
            }
        };

        class iterator_preorder : public iterator
        {
        public:
            iterator_preorder(shared_ptr<Node> n)
            {

                travel(n);
                iterator::queue_binaryTree.push((nullptr));
            };

            void travel(shared_ptr<Node> tree)
            {
                if (tree == nullptr)
                {
                    return;
                }

                iterator::queue_binaryTree.push((tree));
                travel(tree->left);
                travel(tree->right);
            }
        };
        class iterator_inorder : public iterator
        {
        public:
            iterator_inorder(shared_ptr<Node> n)
            {

                travel(n);
                iterator::queue_binaryTree.push((nullptr));
            };

            void travel(shared_ptr<Node> tree)
            {
                if (tree == nullptr)
                {
                    return;
                }

                travel(tree->left);
                iterator::queue_binaryTree.push((tree));
                travel(tree->right);
            }
        };

        class iterator_postorder : public iterator
        {
        public:
            iterator_postorder(shared_ptr<Node> n)
            {

                travel(n);
                iterator::queue_binaryTree.push((nullptr));
            };

            void travel(shared_ptr<Node> tree)
            {
                if (tree == nullptr)
                {
                    return;
                }

                travel(tree->left);
                travel(tree->right);
                iterator::queue_binaryTree.push((tree));
            }
        };

        iterator_preorder begin_preorder()
        {
            return iterator_preorder(_root);
        }
        iterator_preorder end_preorder()
        {
            return iterator_preorder(nullptr);
        }

        iterator_inorder begin_inorder()
        {
            return iterator_inorder(_root);
        }
        iterator_inorder end_inorder()
        {
            return iterator_inorder(nullptr);
        }

        iterator_postorder begin_postorder()
        {
            return iterator_postorder(_root);
        }
        iterator_postorder end_postorder()
        {
            return iterator_postorder(nullptr);
        }

        iterator_inorder begin()
        {
            return iterator_inorder(_root);
        }
        iterator_inorder end()
        {
            return iterator_inorder(nullptr);
        }
    };
    // template <typename T1>
};