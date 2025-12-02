#ifndef CAR_CATEGORY_H
#define CAR_CATEGORY_H

#include <string>
#include <vector>

using namespace std;

struct CarCategoryNode {
    string categoryName;    
    string categoryLabel;    
    int categoryID;          
    CarCategoryNode* left;
    CarCategoryNode* right;

    CarCategoryNode(string name, string label, int id);
};


class CarCategoryTree {
private:
    CarCategoryNode* root;
    int jumlahKategori;

   
    CarCategoryNode* buildTree(vector<string>& currentCategories);
    void printRecursive(CarCategoryNode* node, int space);
    void destroyTree(CarCategoryNode* node);
    void autoAssignDefault(CarCategoryNode* node); 
    void pendingCategory(CarCategoryNode* node, vector<CarCategoryNode*>& list);
    bool searching(CarCategoryNode* node, string targetName);

 
    void preOrder(CarCategoryNode* node);
    void inOrder(CarCategoryNode* node);
    void postOrder(CarCategoryNode* node);

public:
    
    void buildCategoryTree(vector<string> categories); 
    void showCategoryTree();                             

    
    void showActiveCategories();                      
    void updateCategoryInfo(int id, string newLabel); 

    void findCategoryStatus(string categoryName);
    void printAllTraversals();
    bool checkCategoryTree();
};


class AdminCategoryAuth {
private:
    string username;
    string password;
public:
    AdminCategoryAuth();
    bool login();
};

#endif
