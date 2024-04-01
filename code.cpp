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
    char name[100];
    char ingredients[100][100];
    int num_ingredients;
    char instructions[100][100];
    int num_instructions;
    char categories[100][100];
    int num_categories;
};

class RecipeNode{
    public:
    Recipe recipe;
    RecipeNode* next;
};

class CategoryNode{
    public:
    char name[100];
    RecipeNode* recipes;
    CategoryNode* next;
};

class IngredientNode{
    public:
    char ingredient[100];
    RecipeNode* recipes;
    IngredientNode* next;
};

Recipe recipes[100];
int num_recipes=0;
CategoryNode* categories=NULL;
IngredientNode* ingredient_hashtable[100];

// Hash function for ingredients
int hashIngredient(const char* ingredient){
    int hash=0;
    for(int i=0;ingredient[i]!='\0';i++){
        hash=(hash*31+ingredient[i])%100;
    }
    return hash;
}

// Function to add new recipe
void addRecipe(const Recipe& newRecipe){
    if (num_recipes<maxrecipes) {
        recipes[num_recipes++]=newRecipe;
        // Update categories and ingredient hashtable
        for(int i=0; i<newRecipe.num_categories;i++){
            CategoryNode* current=categories;
            CategoryNode* prev=nullptr;
            while(current!=nullptr&&strcmp(current->name,newRecipe.categories[i])!=0){
                prev=current;
                current=current->next;
            }
            if (current==nullptr) {                     //No categories so we will create a new category
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
            // Add recipe to the category
            RecipeNode* newRecipeNode=new RecipeNode;
            newRecipeNode->recipe=newRecipe;
            newRecipeNode->next=current->recipes;
            current->recipes=newRecipeNode;
        }
        // Update ingredient hashtable
        for (int i=0;i<newRecipe.num_ingredients;i++){
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
        cout<<"Maximum number of recipes reached."<<endl;
    }
}

// Function to save recipes to textfile
void saveRecipesToFile(const char* filename){
    ofstream file(filename);
    if (!file.is_open()){
        cout<<"Error opening file for writing."<<endl;
        return;
    }
    for (int i=0; i<num_recipes;i++) {
        file<<"Name: "<<recipes[i].name<< endl;
        file<<"Ingredients: ";
        for (int j=0;j<recipes[i].num_ingredients;j++){
            file<<recipes[i].ingredients[j]<<", ";
        }
        file<<endl;
        file<<"Instructions: ";
        for (int j=0;j<recipes[i].num_instructions;j++){
            file<<recipes[i].instructions[j]<<endl;
        }
        file<<"Categories: ";
        for (int j=0;j<recipes[i].num_categories;j++){
            file<<recipes[i].categories[j]<<", ";
        }
        file<<endl<<endl;
    }
    file.close();
}

// Function to search for a recipe by name
void searchRecipeByName(const char* name){
    bool found = false;
    for(int i=0;i<num_recipes;i++){
        if (strcmp(recipes[i].name,name)==0){
            found=true;
            cout<<"Recipe found:"<<endl;
            cout<<"Name: "<<recipes[i].name<<endl;
            cout<<"Ingredients: ";
            for (int j=0;j<recipes[i].num_ingredients;j++){
                cout<<recipes[i].ingredients[j]<<", ";
            }
            cout<<endl<<"Instructions: ";
            for (int j = 0; j < recipes[i].num_instructions; j++){
                cout<<recipes[i].instructions[j]<<endl;
            }
            cout<<"Categories: ";
            for (int j=0;j<recipes[i].num_categories;j++){
                cout<<recipes[i].categories[j]<<"/";
            }
            cout<<endl<<endl;
            break;
        }
    }
    if (!found) {
        cout<<"Recipe not found."<<endl;
    }
}

// Function to search for a recipe by name by user.
void searchRecipeInteractive(){
    char name[maxnamelength];
    cout << "Enter the name of the recipe to search: ";
    cin>>name;
    cin.ignore();
    searchRecipeByName(name);
}

// Function to add a new recipe by user.
void addRecipeInteractive(){
    Recipe newRecipe;
    cout<<"Enter recipe name: ";
    cin>>newRecipe.name;
    cout<<"Enter number of ingredients: ";
    cin>> newRecipe.num_ingredients;
    cin.ignore(); 
    for (int i=0;i<newRecipe.num_ingredients;i++){
        cout<<"Enter ingredient "<<i+1<<": ";
        cin>>newRecipe.ingredients[i];
        cin.ignore();
    }
    cout<< "Enter number of instructions: ";
    cin>>newRecipe.num_instructions;
    cin.ignore(); 
    for(int i=0;i<newRecipe.num_instructions;i++){
        cout<<"Enter instruction "<<i+1<<": ";
        cin>>newRecipe.instructions[i];
    }
    cout<<"Enter number of categories: ";
    cin>>newRecipe.num_categories;
    cin.ignore(); 
    for(int i=0; i<newRecipe.num_categories;i++){
        cout<<"Enter category "<<i+1<<": ";
        cin>>newRecipe.categories[i];
        cin.ignore();
    }
    addRecipe(newRecipe);
}

// Function to delete a recipe by name
void deleteRecipe(const char* name){
    bool found=false;
    for(int i=0;i<num_recipes;i++){
        if (strcmp(recipes[i].name,name)==0){
            found=true;
            // Shift recipes to overwrite the deleted recipe
            for(int j=i;j<num_recipes-1;j++){
                recipes[j]=recipes[j+1];
            }
            num_recipes--;
            cout<<"Recipe deleted successfully."<<endl;
            break;
        }
    }
    if(!found){
        cout<<"Recipe not found."<<endl;
    }
}

// Function to delete a recipe interactively
void deleteRecipeInteractive(){
    char name[maxnamelength];
    cout<<"Enter the name of the recipe to delete: ";
    cin>>name;
    deleteRecipe(name);
}

// Function to display recipe by category
void displayRecipesByCategory(const char* category){
    bool found=false;
    for(CategoryNode* current=categories;current!= nullptr;current=current->next){
        if(strcmp(current->name,category)==0){
            found=true;
            cout<<"Recipes in category '"<<category<<"':"<< endl;
            for(RecipeNode* recipeNode=current->recipes;recipeNode!=nullptr;recipeNode=recipeNode->next){
                Recipe recipe=recipeNode->recipe;
                cout<<"Name: "<<recipe.name<<endl;
                cout<<"Ingredients: ";
                for(int i = 0; i< recipe.num_ingredients;i++){
                    cout<<recipe.ingredients[i]<< ", ";
                }
                cout<<endl <<"Instructions: ";
                for(int i=0;i<recipe.num_instructions;i++){
                    cout<<recipe.instructions[i]<<endl;
                }
                cout<<endl;
            }
            break;
        }
    }
    if(!found){
        cout<<"No recipes found in category '"<<category<<"'."<<endl;
    }
}

int main(){
    // Sample recipes that are already in Menu.
    Recipe recipe1={"Aloo Mutter", {"Aloo", "mutter", "bacon", "spices", "Tomato"},5,
                      {"Cut Aloo,tomoato and peel off mutter as per the quantity.", "In a vessel add both vegetables and oil", "Add the spices .",
                       "Cook until ready to serve"},4,
                      {"Indian","Vegetable sabji"},2};

    Recipe recipe2 = {"Chicken Curry", {"chicken","onion","tomato","coconut milk","curry powder"}, 5,
                      {"In a pan mix onion until soft.","Add chicken and brown on all sides.","Stir in tomato,coconut milk,and curry powder.",
                       "Again mix until chicken is cooked through."}, 4,
                      {"Indian","Curry"}, 2};

    Recipe recipe3 = {"Margherita Pizza",{"Pizza dough","tomato","sauce","cheese","capsicum","olive oil"},6,
                      {"Prepare Pizza Dough","Add cheese and veggies","Put the pizza in oven.",
                       "Drizzle with olive oil before serving."},4,
                      {"Italian","Neopolitan"},2};

    addRecipe(recipe1);
    addRecipe(recipe2);
    addRecipe(recipe3);
    

    cout<<"Enter 1 if you want to add recipe"<<endl;
    cout<<"Enter 2 if you want to delete recipe"<<endl;
    cout<<"Enter 3 if you want to search recipe"<<endl;
    cout<<"Enter 4 if you want to display recipes by category"<<endl;
    cout<<"Enter 0 if you want to exit"<<endl;
    int choice;
    cin>>choice;
    cin.ignore();

    while(choice)
    {
    switch(choice){
        case 1:
            addRecipeInteractive(); //This will add a recipe of user choice.
            break;
        case 2:
            deleteRecipeInteractive(); //This will delete a recipe of your choice.
            break;
        case 3:
            searchRecipeInteractive(); //This will search a recipe. 
            break;
        case 4:
            char category[maxcategorylength];
            cout << "Enter the category to display recipes: ";
            cin>>category;
            cin.ignore();
            displayRecipesByCategory(category); //This will display all recipes of the category.
            break;
        default:
            break;
    }
    cout<<"Enter 1 if you want to add a recipe"<<endl;
    cout<<"Enter 2 if you want to delete recipe"<<endl;
    cout<<"Enter 3 if you want to search recipe"<<endl;
    cout<<"Enter 4 if you want to display recipes by category"<<endl;
    cout<<"Enter 0 if you want to exit"<<endl;
    cin>>choice;
    cin.ignore();
    }

saveRecipesToFile("recipes.txt"); //This will save all the output to file

    return 0;
}////