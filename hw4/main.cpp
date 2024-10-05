#include "avl.cpp"

using namespace std;

template <typename DATA_TYPE>
int compare(const DATA_TYPE& item1, const DATA_TYPE& item2)
{
	if (item1 < item2)
		return -1;
	if (item1 == item2)
		return 0;

	return 1;
}


int main(int const argc, char const *argv[])
{

    try
    {    
        avlTree<int> tree(compare);
        tree.insert(5);
        tree.insert(2);
        tree.insert(9);
        tree.insert(1);
        tree.insert(4);
        tree.insert(7);
        tree.insert(3);
        tree.insert(8);
        tree.printTree();

        //tree.rotateRight(3);

        //tree.printTree();

        //tree.rotateLeft(5);

        //tree.printTree();
    }
    catch(DuplicateItemException x)
    {
        cout << x.toString() << '\n';
    }
    catch(TreeEmptyException x)
    {
        cout << x.toString() << '\n';
    }
    catch(ItemNotFoundException x)
    {
        cout << x.toString() << '\n';
    }
    catch(InvalidRotationException x)
    {
        cout << x.toString() << '\n';
    }

    return 0;
}