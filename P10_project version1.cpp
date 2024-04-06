#include<bits/stdc++.h>
#define ignoreinput cin.ignore();
using namespace std;

class Recipe 
{
    public:
    char name[100];
    char ingrdts[100][100]; //Ingredients
    int num_ingrdts;
    char instructs[100][100];
    int num_instructs;
    char categories[100][100];
    int num_categories;
};

class recipenode 
{
    public:
    Recipe method;
    recipenode* nxt;
};

class CategoryNode 
{
    public:
    char name[100];
    recipenode* items;
    CategoryNode* nxt;
};

class IngredientNode 
{
    public:
    char ingredient[100];
    recipenode* items;
    IngredientNode* nxt;
};

Recipe recipes[100];
int num_recipes=0;
CategoryNode* categories=NULL;
IngredientNode* ingrdnthashtable[100];

// Hash function for ingredients
int hashingrdnt(const char* ingredient) 
{
    int hash=0;
    for (int i=0;ingredient[i]!='\0';i++) 
    {
        hash=((hash*31)+ingredient[i])%100;
    }
    return hash;
}
// Function to add a new recipe
void addRecipe(const Recipe& newRecipe) 
{
    if (num_recipes<100) 
    {
        recipes[num_recipes++]=newRecipe;
        // Update categories and ingredient hashtable
        for (int i=0;i<newRecipe.num_categories;i++) 
        {
            CategoryNode* current=categories;
            CategoryNode* prev=nullptr;
            while (current!=nullptr&&strcmp(current->name,newRecipe.categories[i])!=0) 
            {
                prev=current;
                current=current->nxt;
            }
            if (current==nullptr) 
            {
                // Category not found, create a new category node
                CategoryNode* newNode=new CategoryNode;
                strcpy(newNode->name,newRecipe.categories[i]);
                newNode->items=nullptr;
                newNode->nxt=nullptr;
                if (prev==nullptr) 
                {
                    categories=newNode;
                } else 
                {
                    prev->nxt=newNode;
                }
                current=newNode;
            }
            // Add recipe to category
            recipenode* newRecipeNode=new recipenode;
            newRecipeNode->method=newRecipe;
            newRecipeNode->nxt=current->items;
            current->items=newRecipeNode;
        }
        // Update ingredient hashtable
        for (int i=0; i<newRecipe.num_ingrdts;i++) 
        {
            int index=hashingrdnt(newRecipe.ingrdts[i]);
            IngredientNode* newNode = new IngredientNode;
            strcpy(newNode->ingredient,newRecipe.ingrdts[i]);
            newNode->items= nullptr;
            newNode->nxt=ingrdnthashtable[index];
            ingrdnthashtable[index]=newNode;
            // Link recipe to ingredient
            recipenode* newRecipeNode=new recipenode;
            newRecipeNode->method=newRecipe;
            newRecipeNode->nxt=newNode->items;
            newNode->items=newRecipeNode;
        }
    } else 
    {
        cout<<"Maximum number of recipes attained."<<endl;
    }
}
// Function to search for a recipe by name
void findrecipebyname(const char* name)
{
    bool found=false;
    for (int i=0;i<num_recipes;i++) 
    {
        if (strcmp(recipes[i].name,name)==0) 
        {
            found=true;
            cout<<"Recipe found:"<<endl;
            cout<<"Name: "<<recipes[i].name << endl;
            cout<<"Ingredients: ";
            for (int j=0;j<recipes[i].num_ingrdts;j++) 
            {
                cout<<recipes[i].ingrdts[j]<<", ";
            }
            cout<<endl<<"Instructions: ";
            for(int j=0;j<recipes[i].num_instructs;j++)
            {
                cout<<recipes[i].instructs[j] <<endl;
            }
            cout<<"Categories: ";
            for(int j=0;j<recipes[i].num_categories;j++)
            {
                cout<<recipes[i].categories[j] << "/";
            }
            cout<<endl<<endl;
            break;
        }
    }
    if (!found){
        cout<<"Recipe not found."<<endl;
    }
}
// Function to save recipes to a text file
void saverecipesinfile(const char* filename) 

{
    ofstream file(filename);
    if(!file.is_open()) 
    {
        cout<<"Error opening file."<<endl;
        return;
    }
    for (int i=0;i<num_recipes;i++) 
    {
        file<<"Name: "<<recipes[i].name<<endl;
        file<<"Ingredients: ";
        for(int j=0;j<recipes[i].num_ingrdts;j++) 
        {
            file<<recipes[i].ingrdts[j]<<", ";
        }
        file<<endl;
        file<<"Instructions: ";
        for (int j=0;j<recipes[i].num_instructs;j++) 
        {
        file<<recipes[i].instructs[j]<<endl;
        }
        file<<"Categories: ";
        for (int j=0;j<recipes[i].num_categories;j++) 
        {
            file<<recipes[i].categories[j]<<", ";
        }
        file<<endl<<endl;
    }
    file.close();
}
// Function to search for a recipe interactively by name
void searchrecipebyuser() 
{
    char name[100];
    cout<<"Enter the name of the recipe to search: ";
    cin.getline(name,100);
    findrecipebyname(name);
}

// Function to add a new recipe interactively
void addrecipeuser() 
{
    Recipe newRecipe;
    cout<<"Enter recipe name: ";
    cin.getline(newRecipe.name,100);
    cout<<"Enter number of ingredients: ";
    cin>>newRecipe.num_ingrdts;
    ignoreinput;
    for(int i=0;i<newRecipe.num_ingrdts;i++) 
    {
        cout<<"Enter ingredient "<<i+1<<": ";
        cin.getline(newRecipe.ingrdts[i],100);
    }
    cout<<"Enter number of instructions: ";
    cin>>newRecipe.num_instructs;
    ignoreinput;
    for(int i=0;i<newRecipe.num_instructs;i++) 
    {
        cout<<"Enter instruction "<<i+1<<": ";
        cin.getline(newRecipe.instructs[i],100);
    }
    cout<<"Enter number of categories: ";
    cin>>newRecipe.num_categories;
    ignoreinput;
    for(int i=0; i<newRecipe.num_categories;i++) 
    {
        cout<<"Enter category "<<i+1<<": ";
        cin.getline(newRecipe.categories[i],100);
    }
    addRecipe(newRecipe);
}
// Function to delete a recipe by name
void deleteRecipe(const char* name) 
{
    bool found=false;
    for (int i= 0;i<num_recipes;i++) {
        if (strcmp(recipes[i].name,name) == 0)
        {
            found=true;
            // Shift recipes to overwrite the deleted recipe
            for (int j=i;j<num_recipes-1;j++) 
            {
                recipes[j]=recipes[j+1];
            }
            num_recipes--;
            cout <<"Recipe deleted successfully."<<endl;

            // Save recipes to file immediately after deleting
            saverecipesinfile("recipes.txt");

            break;
        }
    }
    if(!found) 
    {
        cout<<"Recipe not found."<<endl;
    }
}
// Function to delete a recipe interactively
void deleterecipebyuser()
{
    char name[100];
    cout<<"Enter the name of the recipe to delete: ";
    cin.getline(name,100);
    deleteRecipe(name);
}
// To display recipes as per the given category
void displayrecipebycat(const char* category) 
{
    bool found=false;
    for(CategoryNode* current=categories; current != nullptr;current=current->nxt) 
    {
        if (strcmp(current->name, category) == 0) 
        {
            found=true;
            cout << "Recipes in category '" << category << "':" <<endl;
            for (recipenode* recipeNode= current->items; recipeNode!= nullptr; recipeNode= recipeNode->nxt){
                Recipe recipe=recipeNode->method;
                cout<<"Name: "<<recipe.name <<endl;
                cout<< "Ingredients: ";
                for (int i = 0; i<recipe.num_ingrdts; i++)
                {
                    cout<<recipe.ingrdts[i]<<", ";
                }
                cout<<endl<<"Instructions: ";
                for (int i=0;i<recipe.num_instructs;i++)
                {
                    cout<<recipe.instructs[i]<<endl;
                }
                cout<<endl;
            }
            break;
        }
    }
    if (!found)
    {
        cout<<"No recipes found in category '"<<category<<"'."<<endl;
    }
}
