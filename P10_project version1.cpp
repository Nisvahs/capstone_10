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
