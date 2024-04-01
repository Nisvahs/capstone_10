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