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
    avlTree<int> tree(compare);
    char command;
    int num;

    while (command != 'Q')
    {
        try
        {   
            cout << "Enter a command (I or R or Q): ";
            cin >> command;

            switch (command)
            {
                case 'I':
                case 'i':
                    cout << "Enter a number to insert: ";
                    cin >> num;
                    tree.insert(num);
                    break;

                case 'R':
                case 'r':
                    cout << "Enter a number to remove: ";
                    cin >> num;
                    tree.remove(num);
                    break;
                
                case 'Q':
                case 'q':
                    command = 'Q';
                    break;
                default:
                    cout << "Invalid Command" << endl;
            }
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
        catch(InvalidRotationException x)
        {
            cout << x.toString() << '\n';
        }
    }
    return 0;
}