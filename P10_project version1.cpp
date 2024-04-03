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
void addRecipe(const Recipe& newRecipe){
    if(num_recipes<maxrecipes) {
        recipes[num_recipes++]=newRecipe;
        // Update categories
        CategoryNode* currentCategory=categories;
        CategoryNode* prevCategory=nullptr;
        bool categoryFound=false;
        // Condition to check if category already exists
        for (int i=0;i<newRecipe.num_categories;i++){
            categoryFound=false;
            currentCategory=categories;
            prevCategory=nullptr;
            while(currentCategory!=nullptr){
                if(strcmp(currentCategory->name,newRecipe.categories[i])==0){
                    categoryFound=true;
                    break;
                }
                prevCategory=currentCategory;
                currentCategory=currentCategory->next;
            }
            if(!categoryFound){
                // Category not found so create a new category node
                CategoryNode* newCategoryNode=new CategoryNode;
                strcpy(newCategoryNode->name,newRecipe.categories[i]);
                newCategoryNode->recipes=nullptr;
                newCategoryNode->next=nullptr;
                if (prevCategory==nullptr){
                    categories=newCategoryNode;
                } else{
                    prevCategory->next=newCategoryNode;
                }
                currentCategory=newCategoryNode;
            }
            // Add recipe to category
            RecipeNode* newRecipeNode=new RecipeNode;
            newRecipeNode->recipe=newRecipe;
            newRecipeNode->next=currentCategory->recipes;
            currentCategory->recipes=newRecipeNode;
        }

        // Update ingredients
        for (int i=0;i<newRecipe.num_ingredients;i++){
            IngredientNode* currentIngredient=ingredient_hashtable[hashIngredient(newRecipe.ingredients[i])];
            IngredientNode* prevIngredient=nullptr;
            bool ingredientFound=false;
            // to check if ingredient already exists
            while (currentIngredient!=nullptr) {
                if (strcmp(currentIngredient->ingredient,newRecipe.ingredients[i])==0){
                    ingredientFound=true;
                    break;
                }
                prevIngredient=currentIngredient;
                currentIngredient=currentIngredient->next;
            }
            if (!ingredientFound){
                // Since ingredient not found, create a new ingredient node
                IngredientNode* newIngredientNode=new IngredientNode;
                strcpy(newIngredientNode->ingredient,newRecipe.ingredients[i]);
                newIngredientNode->recipes=nullptr;
                newIngredientNode->next=nullptr;
                int index=hashIngredient(newRecipe.ingredients[i]);
                if (prevIngredient==nullptr){
                    ingredient_hashtable[index]=newIngredientNode;
                } else {
                    prevIngredient->next=newIngredientNode;
                }
                currentIngredient=newIngredientNode;
            }
            // Link recipe to ingredient
            RecipeNode* newRecipeNode=new RecipeNode;
            newRecipeNode->recipe=newRecipe;
            newRecipeNode->next=currentIngredient->recipes;
            currentIngredient->recipes=newRecipeNode;
        }
    } else{
        cout<<"Maximum number of recipes reached."<<endl;
    }
}
