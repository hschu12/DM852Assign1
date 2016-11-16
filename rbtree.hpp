#include <functional>
#include <string>
#include <utility>
#include <iostream>

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
			Node *parent, *leftChild, *rightChild;

			Node (key_type k, mapped_type d)
			{
				key = k;
				data = d;
				leftChild = nullptr;
				rightChild = nullptr;
				parent = nullptr;
				color = RED;
			}

			Node () 
			{
				leftChild = nullptr;
				rightChild = nullptr;
				parent = nullptr;
				color = RED;
			}
		};
		
		key_compare comp;
		Node *NIL;
		Node *root;

		
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
				else 
				{
					x = x->rightChild;
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
			rb_insert_fixup(*z);
 		}

 		void find(const Key &k)
 		{
 		}


		void find(const Key &k) const
		{
		}

		/*void erase(const_iterator it)
		{
			Node n = new Node;
			return n;
		}*/
	

		void rb_insert_fixup(Node &z)
		{
			while(z.parent.color == Red ) 
			{
				if (z.parent == z.parent.parent.leftChild)
				{
					Node y = z.parent.parent.rightChild;
					if (y.color == RED)
					{
						z.parent.color = BLACK;
						y.color = BLACK;
						z.parent.parent.color = RED;
						z = z.parent.parent;
					}
					else if (z == z.parent.rightChild)
					{
						z = z.parent;
						leftRotate(*z);
					}
					z.parent.color = BLACK;
					z.parent.parent.color = RED;
					rightRotate(*z);
				}
			}
			else
			{
				
			}
		}
	private:
		int treeSize;

	};
}