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
        tree.insert(4);
        tree.insert(5);
        tree.insert(3);
        tree.insert(2);
        tree.insert(6);
        tree.insert(8);
        tree.insert(30);
        tree.insert(1);
        tree.insert(15);
        //tree.rotateRight(-9);
        tree.rotateLeft(-9);
        cout << "worked" << endl;

        tree.printTree();
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

    return 0;
}