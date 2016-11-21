#include <functional>
#include <string>
#include <utility>
#include <iostream>
#include <iterator>

namespace DM852{
	template<typename Key, typename Value, typename Compare = std::less<Key> >
	class RBtree
	{

		enum Color
		{
			BLACK, // 0
			RED // 1
		};

	public:

		using key_type = Key;
		using mapped_type = Value;
		using value_type = std::pair<const Key, Value>;
		using key_compare = Compare;

		struct Node
		{
			mapped_type data;
			key_type key;
			Color color;
			Node *parent, *leftChild, *rightChild, *successor;

			Node (key_type k, mapped_type d)
			{
				key = k;
				data = d;
				leftChild = nullptr;
				rightChild = nullptr;
				parent = nullptr;
				successor = nullptr;
				color = RED;
			}

			Node () 
			{
				leftChild = nullptr;
				rightChild = nullptr;
				parent = nullptr;
				successor = nullptr;
				color = BLACK;
			}
		};

		key_compare comp;
		Node *NIL;
		Node *root;
		Node *toMain;
		
		class iterator 
		{

		public:

			using iterator_category = std::bidirectional_iterator_tag;

			iterator(Node *p) : position(p) {}
			~iterator()
			{
				delete position;
			}

			iterator(const iterator& it);
		
			bool operator== (const iterator& rhs) const
			{
				return (*this == rhs);
			}

			bool operator!= (const iterator& rhs)
			{
				/*bool result = !(*this == rhs);
				std::cout << "evalutated to " << result << std::endl;*/
				return !(*this == rhs);
			}

			Node& operator* () const 
			{
				return *position;
			}


			Node* operator->() const
			{
				return position;
			}

			iterator& operator++ () 
			{
				std::cout << "++ " << std::endl;
				position = position->successor;
				return *this;
			}

			iterator operator++ (int);

			iterator& operator-- ();

			iterator operator-- (int);

		private:
			Node *position;

		};



		class const_iterator : public std::iterator<std::bidirectional_iterator_tag, Node> 
		{
		public:
			const_iterator();
			~const_iterator();	
		};

		using iterator = typename RBtree::iterator;
		using const_iterator = typename RBtree::const_iterator;

		iterator begin()
		{
			std::cout << "(begin)" << std::endl;
			Node *currentNode = root;
			if(currentNode != NIL)
			{
				while(currentNode->leftChild != NIL)
				{
					currentNode = currentNode->leftChild;
				}
			}
			std::cout << "(begin ending)" << std::endl;
			return iterator(currentNode);
		}
		
		iterator end()
		{
			std::cout << "begin" << std::endl;
			return iterator(NIL);
		}

		RBtree() 
		{
			NIL = new Node();
			root = NIL;
		}
		
		//RBtree(const Compare &key_compare);

		~RBtree()
		{
			delete root;
		}

		void insert(const value_type &v)
		{
			std::cout << "const " << std::endl;
		}

 		void insert(value_type &&v)
 		{
 			std::cout << std::endl;
 			std::cout << "insert: " << v.second  << std::endl;
			Node *z = new Node(v.first, v.second);	
			Node *y = NIL;
			Node *x = root;
			while (x != NIL)
			{
				y = x;
				if (comp(z->key, x->key))
				{
					x = x->leftChild;
				}
				else if (comp(x->key, z->key))
				{
					x = x->rightChild;
				}
				else
				{
					x->data = v.second;
				}
			}
			z->parent = y;
			if (y == NIL)
			{
				root = z;
			}		
			else if (comp(z->key, y->key))
			{
				y->leftChild = z;
			}
			else
			{
				y->rightChild = z;
			}
			z->leftChild = NIL;
			z->rightChild = NIL;
			z->color = RED;
			rb_insert_fixup(z);
 		}

 		void find(const Key &k)
 		{
 			Node x = find(k, root);
 			if (x.data == k)
 			{
 				std::cout << "Found" << std::endl;
 			}
 			else 
 			{
 				std::cout << "Not found" << std::endl;
 			}
 		}

 		Node find(const Key &k, Node *x)
 		{
 			if (x == NIL || !(comp(k, x->data) || comp(x->data, k)))
 			{
 				return *x;
 			}
 			if (comp(k, x->data))
 			{
 				return find(k, x->leftChild);
 			}
 			else
 			{
 				return find(k, x->rightChild);
 			}
 		}

		void find(const Key &k) const
		{
		}

		void erase(Node *z) // using const_iterator it
		{
			Node y = z;
			Node x;
			int y_original_color = y->color;
			if (z->leftChild == NIL) 
			{
				x = z->rightChild;
				rb_transplant(z, z->rightChild);
			}
			else if (z->rightChild == NIL)
			{
				x = z->leftChild;
			}
			else
			{
				y = tree_minimum(z->rightChild);
				y_original_color = y->color;
				x = y->rightChild;
				if (y->parent == z)
				{
					x->parent = y;
				}
				else
				{
					rb_transplant(y, y->rightChild);
					y->rightChild = z->rightChild;
					y->rightChild->parent = y;
				}
				rb_transplant(z, y);
				y->leftChild = z->leftChild;
				y->leftChild->parent = y;
				y->color = z->color;
			}
			if (y_original_color == BLACK)
			{
				rb_delete_fixup(x);
			}
		}
	

		void rb_insert_fixup(Node *z)
		{
			while(z->parent->color == RED ) 
			{
				if (z->parent == z->parent->parent->leftChild)
				{
					Node *y = z->parent->parent->rightChild;
					if (y->color == RED)
					{
						z->parent->color = BLACK;
						y->color = BLACK;
						z->parent->parent->color = RED;
						z = z->parent->parent;
					}
					else 
					{
						if (z == z->parent->rightChild)
						{
							z = z->parent;
							leftRotate(z);
						}
						z->parent->color = BLACK;
						z->parent->parent->color = RED;
						rightRotate(z->parent->parent);
					}
				}
				else
				{
					Node *y = z->parent->parent->leftChild;
					if (y->color == RED)
					{
						z->parent->color = BLACK;
						y->color = BLACK;
						z->parent->parent->color = RED;
						z = z->parent->parent;
					}
					else 
					{
						if (z == z->parent->leftChild)
						{
							z = z->parent;
							rightRotate(z);
						}
						z->parent->color = BLACK;
						z->parent->parent->color = RED;
						leftRotate(z->parent->parent);
					}
				}
			}
			root->color = BLACK;
			setsuccesors(root);
		}

		void leftRotate(Node *x)
		{
			Node *y = x->rightChild;
			x->rightChild = y->leftChild;
			if (y->leftChild != NIL)
			{
				y->leftChild->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == NIL)
			{
				root = y;
			}
			else if (x == x->parent->leftChild)
			{
				x->parent->leftChild = y;
			}
			else
			{
				x->parent->rightChild = y;
			}
			y->leftChild = x;
			x->parent = y;
		}

		void rightRotate(Node *x)
		{
			Node *y = x->leftChild;
			x->leftChild = y->rightChild;
			if (y->rightChild != NIL)
			{
				y->rightChild->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == NIL)
			{
				root = y;
			}
			else if (x == x->parent->rightChild)
			{
				x->parent->rightChild = y;
			}
			else
			{
				x->parent->leftChild = y;
			}
			y->rightChild = x;
			x->parent = y;
		}

		void rb_transplant(Node *u, Node *v)
		{
			if (u->parent == NIL)
			{
				root = v;
			}
			else if (u == u->parent->leftChild)
			{
				u->parent->leftChild = v;
			}
			else
			{
				u->parent->rightChild = v;
			}
			v->parent = u->parent;
		}

		void rb_delete_fixup(Node *x)
		{
			while (x != root && x->color == BLACK)
			{
				if (x == x->parent->leftChild)
				{
					Node w = x->parent->rightChild;
					if (w->color == RED)
					{
						w->color = BLACK;
						x->parent->color = RED;
						leftRotate(x->parent);
						w = x->parent->rightChild;
					}
					if (w->leftChild->color == BLACK && w->rightChild->color == BLACK)
					{
						w->color == RED;
						x = x->parent;
					}
					else
					{
						if (w->rightChild->color == BLACK)
						{
							w->leftChild->color = BLACK;
							w->color = RED;
							rightRotate(w);
							w = x->parent->rightChild;
						}
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->rightChild->color = BLACK;
						leftRotate(x->parent);
						x = root;
					}
				}
				else
				{
					Node w = x->parent->leftChild;
					if (w->color == RED)
					{
						w->color = BLACK;
						x->parent->color = RED;
						rightRotate(x->parent);
						w = x->parent->leftChild;
					}
					if (w->rightChild->color == BLACK && w->leftChild->color == BLACK)
					{
						w->color == RED;
						x = x->parent;
					}
					else
					{
						if (w->leftChild->color == BLACK)
						{
							w->rightChild->color = BLACK;
							w->color = RED;
							leftRotate(w);
							w = x->parent->leftChild;
						}
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->leftChild->color = BLACK;
						rightRotate(x->parent);
						x = root;
					}
				}	
			}
			x->color = BLACK;
		}

		Node* tree_minimum(Node *x)
		{
			while (x->leftChild != NIL)
			{
				x = x->leftChild;
			}
			return x;
		}

		Node* tree_successor(Node *x)
		{
			if (x->rightChild !=  NIL)
			{
				return tree_minimum(x->rightChild);
			}
			Node *y = x->parent;
			while (y != NIL && x==y->rightChild)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}

		void setsuccesors(Node *x)
		{
			if (x != NIL)
			{
				setsuccesors(x->leftChild);
				x->successor = tree_successor(x);
				setsuccesors(x->rightChild);
			}
		}

		void in_order_tree(Node *x)
		{
			if (x != NIL)
			{
				in_order_tree(x->leftChild);
				std::cout << x->data << " has successor: " << x->successor->data << std::endl;
				in_order_tree(x->rightChild);
			}
		}

		void printTree(Node *n) {
			if (n != NIL) {
				std::cout << "hit " << n->data << std::endl;
			}
			if (n->leftChild != NIL)
			{
				std::cout << "Go left" << std::endl;
				printTree(n->leftChild);
			}
			if (n->rightChild != NIL)
			{
				std::cout << "Go right" << std::endl;
				printTree(n->rightChild);
			}
			std::cout << "back from " << n->data << std::endl;
			
		}

	private:
		int treeSize;

	};
}