/***
 * NAME: ASIM LATIF
 * CMS ID: 283230
 * SECTION: 283230
 */

#include<bits/stdc++.h>
#include<fstream>
#include <cstring>
using namespace std;

#define SPACES 10


struct Node {
    string data;
    int height;
    struct Node *left;
    struct Node *right;
};

// return max of two numbers
int GET_MAX(int first_num, int second_num) {
    return (first_num > second_num) ? first_num : second_num;
}

// display avl tree with root and child nodes
void PRINT_2D_FUNC(Node *root, int space) {

    if (root == NULL)
        return;

    space += SPACES;

    PRINT_2D_FUNC(root->right, space);


    cout << endl;
    for (int i = SPACES; i < space; i++)
        cout << " ";
    cout << root->data << "\n";

    PRINT_2D_FUNC(root->left, space);
}


void print_func(Node *root, int index) {

    cout << " <<***********************<< Key Value: " << index << " >>**************************>> " << endl;
    PRINT_2D_FUNC(root, 0);


}

// Pre-order Traversal
void preOrder(Node *root) {
    if (root != NULL) {
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Creating AVL Tree Class
class AVL {
public:
    // root node
    struct Node *root;

    AVL() {
        // initializing it to null
        this->root = NULL;
    }

    // it fixes the height of each node
    int height(struct Node *tnode) {

        if (tnode->left && tnode->right) {
            if (tnode->left->height < tnode->right->height)
                return tnode->right->height + 1;
            else return tnode->left->height + 1;
        } else if (tnode->left && tnode->right == NULL) {
            return tnode->left->height + 1;
        } else if (tnode->left == NULL && tnode->right) {
            return tnode->right->height + 1;
        }
        return 0;

    }

    // returns the height of given node
    int return_height(Node *node) {
        if (node == NULL)
            return 0;
        return node->height;
    }

    // returns difference between left and right subtree
    int get_balance_factor(Node *node) {
        if (node == NULL)
            return 0;
        return return_height(node->left) - return_height(node->right);
    }

    // right rotation to balance avl tree
    Node *rr_Rotation(Node *node) {
        // left node
        struct Node *left_node;
        // right node of left node
        struct Node *right_left_node;
        left_node = node->left;
        right_left_node = left_node->right;

        left_node->right = node;
        node->left = right_left_node;

        node->height = GET_MAX(return_height(node->left),
                               return_height(node->right)) + 1;
        left_node->height = GET_MAX(return_height(left_node->left),
                                    return_height(left_node->right)) + 1;

        return left_node;
    }

    // left rotation to balance avl tree
    Node *ll_rotation(Node *node) {
        // right node
        struct Node *right_node;
        // left node of right node
        struct Node *left_right_node;
        right_node = node->right;
        left_right_node = right_node->left;
        right_node->left = node;
        node->right = left_right_node;

        node->height = GET_MAX(return_height(node->left),
                               return_height(node->right)) + 1;
        right_node->height = GET_MAX(return_height(right_node->left),
                                     return_height(right_node->right)) + 1;

        return right_node;
    }

    // insert a node in avl tree and balances each inserted node
    struct Node *insert_node(struct Node *root, string data) {
        // if no node in tree, given node becomes root
        if (root == NULL) {
            struct Node *node;
            node = new struct Node;
            node->data = data;
            root = node;
            root->left = root->right = NULL;
            root->height = 1;
            return root;
        }
            // if inserting node is less than root
        else {
            // if inserting node is less than root
            if (data < root->data) {
                root->left = insert_node(root->left, data);
                // if inserting node is more than root
            } else if (data > root->data) {
                root->right = insert_node(root->right, data);
            } else {
                return root;
            }
        }

        root->height = height(root);
        int balance_factor = get_balance_factor(root);


        if (balance_factor > 1 && data < root->left->data)
            return rr_Rotation(root);

        if (balance_factor < -1 && data > root->right->data)
            return ll_rotation(root);

        if (balance_factor > 1 && data > root->left->data) {
            root->left = ll_rotation(root->left);
            return rr_Rotation(root);
        }

        if (balance_factor < -1 && data < root->right->data) {
            root->right = rr_Rotation(root->right);
            return ll_rotation(root);
        }


        return root;
    }

    Node *min_val_node(Node *node) {
        struct Node *current = node;


        while (current->left != NULL)
            current = current->left;

        return current;
    }

    // deletes the given node from avl tree
    Node *delete_node(Node *root, string data) {

        if (root == NULL) {
            return root;
        }


        if (data < root->data)
            root->left = delete_node(root->left, data);


        else if (data > root->data)
            root->right = delete_node(root->right, data);

        else {
            if ((root->left == NULL) ||
                (root->right == NULL)) {
                Node *temp = root->left ?
                             root->left :
                             root->right;

                if (temp == NULL) {
                    temp = root;
                    root = NULL;
                } else
                    *root = *temp;

                free(temp);
            } else {

                Node *temp = min_val_node(root->right);


                root->data = temp->data;

                root->right = delete_node(root->right,
                                          temp->data);
            }
        }
        if (root == NULL)
            return root;


        root->height = 1 + GET_MAX(return_height(root->left),
                                   return_height(root->right));

        int balance = get_balance_factor(root);

        // checking condition for right rotation
        if (balance > 1 &&
            get_balance_factor(root->left) >= 0)
            return rr_Rotation(root);

        if (balance > 1 &&
            get_balance_factor(root->left) < 0) {
            // first rotating left
            root->left = ll_rotation(root->left);
            // then rotating right
            return rr_Rotation(root);
        }
        // checking condition for left rotation
        if (balance < -1 &&
            get_balance_factor(root->right) <= 0)
            return ll_rotation(root);

        if (balance < -1 &&
            get_balance_factor(root->right) > 0) {
            root->right = rr_Rotation(root->right);
            return ll_rotation(root);
        }

        return root;
    }


};
// returns the key value for given name
int get_key_val(string name) {
    // taking bits of first char in name
    string char_name_in_bits = bitset<8>(name[0]).to_string();
    // taking lower three bits
    char_name_in_bits = char_name_in_bits.substr(char_name_in_bits.length() - 3);
    // initializing key to zero
    int key = 0;
    int size = char_name_in_bits.size();
    // converting lower binary digits to decimal
    for (int i = 0; i < size; i++) {
        if (char_name_in_bits[i] == '1') {
            key = key + pow(2.0, i);
        } else if (char_name_in_bits[i] == '1' && i != 0) {
            key = key + pow(0.0, i);
        }
    }
    return key;
}

// Creating Hash Class
class Hash {

    int TABLE_SIZE;

    AVL *hash_tree;

public:
    // return key for char of name
    int hash_func(string name) {

        return get_key_val(name);

    }
    // Constructor
    Hash(int size) {

        this->TABLE_SIZE = size;
        hash_tree = new AVL[TABLE_SIZE];

    }
    // inserts an item into tree and returns the index
    int insert_item(string data) {
        int index = hash_func(data);
        hash_tree[index].root = hash_tree[index].insert_node(hash_tree[index].root, data);
        return index;
    }
    // returns height of tree
    int get_avl_height(int index) {
        return hash_tree[index].root->height;
    }

    int delete_item(string data) {


        int index = hash_func(data);
        hash_tree[index].root = hash_tree[index].delete_node(hash_tree[index].root, data);
        return index;
    }
    // to display names in tree
    void display_func() {

        for (int i = 0; i < TABLE_SIZE; i++) {
            print_func(hash_tree[i].root, i);
        }

    }
    // prints details of the tree
    void get_details(int index) {
        cout << "Index : " << index << endl;
        cout << "Height : " << get_avl_height(index) << endl;
    }

};


int main() {
    string name_read_array[91];
    short read_loop_index = 0;
    string read_line;
    // file for file handling
    ifstream file;
    // opening file by specifying the absolute path
    file.open("/home/asim/CLionProjects/DSA_Assignemnt2/Names.txt");
    cout << file.is_open() << endl;
    // checks if file opened successfully or not
    if (file.is_open()) {
        // loop to insert read names into our array
        while (!file.eof()) {
            getline(file, read_line);
            name_read_array[read_loop_index] = read_line;
            read_loop_index++;
        }
        file.close();

    }

    // getting size of names array
    int size_name_array = sizeof(name_read_array) / sizeof(name_read_array[0]);
    // declaring hash table of size 8 ranging from 0 to 7
    Hash hash_table(8);
    // looping to insert names into hash table
    for (int i = 0; i < size_name_array; i++)
        hash_table.insert_item(name_read_array[i]);
    //prompt variable
    int command;
    int index;
    // name variable
    string name;

    do {
        cout << "1. Insert a Name" << endl;
        cout << "2. Delete a Name" << endl;
        cout << "3. Print the Table" << endl;
        cout << "4. Exit" << endl;
        scanf("%d", &command);

        while (command < 1 || command > 4) {
            cout << "Choose Valid Command!!" << endl;
            // taking input from user
            scanf("%d", &command);

        }


        if (command == 1) {

            cout << "Name to be Inserted: " << endl;
            getline(cin, name);
            getline(cin, name);
            cout << "Name is being Inserted.." << name << endl;
            index = hash_table.insert_item(name);
            cout << "Name Inserted Successfully.\nDetails: " << endl;
            hash_table.get_details(index);

        }


        if (command == 2) {

            cout << "Name to be Deleted: " << endl;
            getline(cin, name);
            getline(cin, name);
            index = hash_table.delete_item(name);
            hash_table.get_details(index);
        }

        if (command == 3) {
            cout << "Visualization Of Hash AVL Tree" << endl;
            hash_table.display_func();
        }
        if (command == 4) {
            cout << "Program Exited!" << endl;
        }
    } while (command != 4);
}
