#include<bits/stdc++.h>

using namespace std;

const int maxnamelength=100;
const int maxingridients=20;
const int maxingridientlength=50;
const int maxinstructions=100;
const int maxinstructionlength=200;
const int maxcategories=10;
const int maxcategorylength=50;
const int maxrecipes=100;
const int hashtblsize=100;

class Recipe{
    public:
    char name[maxnamelength];
    char ingredients[maxingridients][maxingridientlength];
    int num_ingredients;
    char instructions[maxinstructions][maxinstructionlength];
    int num_instructions;
    char categories[maxcategories][maxcategorylength];
    int num_categories;
};

class RecipeNode{
    public:
    Recipe recipe;
    RecipeNode* next;
};

class CategoryNode{
    public:
    char name[maxcategorylength];
    RecipeNode* recipes;
    CategoryNode* next;
};

class IngredientNode{
    public:
    char ingredient[maxingridientlength];
    RecipeNode* recipes;
    IngredientNode* next;
};


Recipe recipes[maxrecipes];
int num_recipes=0;
CategoryNode* categories=NULL;
IngredientNode* ingredient_hashtable[hashtblsize];

// Hash function for ingredients
int hashIngredient(const char* ingredient){
    int hash=0;
    for (int i=0;ingredient[i]!='\0';i++){
        hash=(hash*31+ingredient[i])%hashtblsize;
    }
    return hash;
}
// Function to add a new recipe
void addRecipe(const Recipe& newRecipe) {
    if (num_recipes<maxrecipes) {
        recipes[num_recipes++]=newRecipe;
        // Update categories and ingredient hashtable
        for (int i=0; i<newRecipe.num_categories;i++) {
            CategoryNode* current=categories;
            CategoryNode* prev=nullptr;
            while (current!=nullptr&&strcmp(current->name,newRecipe.categories[i])!=0) {
                prev=current;
                current=current->next;
            }
            if (current==nullptr) {
                // Category not found, create a new category node
                CategoryNode* newNode=new CategoryNode;
                strcpy(newNode->name,newRecipe.categories[i]);
                newNode->recipes=nullptr;
                newNode->next=nullptr;
                if (prev==nullptr) {
                    categories=newNode;
                } else {
                    prev->next=newNode;
                }
                current=newNode;
            }
            // Add recipe to category
            RecipeNode* newRecipeNode=new RecipeNode;
            newRecipeNode->recipe=newRecipe;
            newRecipeNode->next=current->recipes;
            current->recipes=newRecipeNode;
        }
        // Update ingredient hashtable
        for (int i=0; i<newRecipe.num_ingredients;i++) {
            int index=hashIngredient(newRecipe.ingredients[i]);
            IngredientNode* newNode = new IngredientNode;
            strcpy(newNode->ingredient,newRecipe.ingredients[i]);
            newNode->recipes= nullptr;
            newNode->next=ingredient_hashtable[index];
            ingredient_hashtable[index]=newNode;
            // Link recipe to ingredient
            RecipeNode* newRecipeNode=new RecipeNode;
            newRecipeNode->recipe=newRecipe;
            newRecipeNode->next=newNode->recipes;
            newNode->recipes=newRecipeNode;
        }
    } else {
        cout << "Maximum number of recipes reached." << endl;
    }
}
