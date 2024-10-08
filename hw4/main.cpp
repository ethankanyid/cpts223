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
    //cout << "     5\n 3 \t7\n2  4  6  8" << endl;

    try
    {
        tree.insert(5);
        tree.insert(3);
        tree.insert(7);
        tree.insert(4);
        tree.insert(2);
        tree.insert(6);
        tree.insert(1);
        cout << "     5\n 3 \t7\n2  4  6\n1" << endl << endl;
        cout << "remove 6"<< endl;
        tree.remove(6);
        cout << "     3\n 2 \t5\n1     4  7" << endl << endl;
        cout << "remove 1"<< endl;
        tree.remove(1);
        cout << "     3\n 2 \t5\n      4  7" << endl << endl;   
        cout << "remove 2"<< endl; 
        tree.remove(2);
        cout << "     5\n 3 \t7\n   4" << endl << endl;
        cout << "remove 7"<< endl;
        tree.remove(7);
        cout << "     4\n 3 \t5\n" << endl << endl;
        cout << "remove 4"<< endl;
        tree.remove(4);
        cout << "     3\n   \t5\n" << endl << endl;
        cout << "insert 2 then 4"<< endl;
        tree.insert(2);
        tree.insert(4);
        cout << "     3\n 2 \t5\n      4" << endl << endl;
        cout << "remove 2"<< endl;
        tree.remove(2);
        cout << "     4\n 3 \t5\n" << endl << endl;
        cout << "insert 7 then 6"<< endl;
        tree.insert(7);
        cout << "     4\n 3 \t5\n   \t 7\n" << endl << endl;
        tree.insert(6);
        cout << "     4\n 3 \t6\n      5  7" << endl << endl;
        cout << "insert 8"<< endl;
        tree.insert(8);
        cout << "     6\n 4 \t5\n3      7  8" << endl << endl;
        cout << "remove 8 then 5"<< endl;
        tree.remove(8);
        tree.remove(5);
        cout << "     6\n 4 \t7\n3         " << endl << endl;
        cout << "insert 2"<< endl;
        tree.insert(2);   
        cout << "     6\n 3 \t7\n2  4       " << endl << endl;
        cout << "insert 5"<< endl;
        tree.insert(5);
        cout << "     4\n 3 \t6\n2     5   7" << endl << endl;

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


    /*while (command != 'Q') // let user insert and remove
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
    }*/
    return 0;
}