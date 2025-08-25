🌳 Trees in C

1. What is a Tree?

A tree is a data structure made of nodes.

Each node can have children → creates a hierarchy.

Root = the top node.

Leaf = a node with no children.

Subtree = a smaller tree inside the big tree.



---

2. Binary Tree (most common in C)

Each node has at most two children (left and right).


typedef struct node
{
    int value;
    struct node *left;
    struct node *right;
} node;


---

3. Binary Search Tree (BST)

Special type of binary tree with ordering rules:

Left child < Parent < Right child.

Useful for searching, inserting, deleting efficiently (≈ O(log n) average if balanced).



---

4. Create a Node

node *create(int value)
{
    node *n = malloc(sizeof(node));
    if (n != NULL)
    {
        n->value = value;
        n->left = NULL;
        n->right = NULL;
    }
    return n;
}


---

5. Insert into BST

node *insert(node *root, int value)
{
    if (root == NULL)
        return create(value);

    if (value < root->value)
        root->left = insert(root->left, value);
    else if (value > root->value)
        root->right = insert(root->right, value);

    return root;
}


---

6. Search in BST

bool search(node *root, int value)
{
    if (root == NULL)
        return false;
    if (root->value == value)
        return true;
    else if (value < root->value)
        return search(root->left, value);
    else
        return search(root->right, value);
}


---

7. Tree Traversals

Different ways to visit all nodes:

In-order (Left → Root → Right) → prints sorted order in BST.

Pre-order (Root → Left → Right) → useful for saving tree structure.

Post-order (Left → Right → Root) → useful for freeing memory.


Example (in-order):

void inorder(node *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%i ", root->value);
    inorder(root->right);
}


---

8. Freeing a Tree

Always free memory when done:

void free_tree(node *root)
{
    if (root == NULL)
        return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}


---

✅ Key Takeaways

Trees = hierarchical version of linked lists.

BSTs allow fast searching and inserting.

In C: nodes are allocated with malloc, freed with free.

Traversals (in-order, pre-order, post-order) are the standard way to process trees.


