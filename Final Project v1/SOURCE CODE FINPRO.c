#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h>

struct customer
{
    char username[26];  // max 25 character, bikin lower case aja
    char nik[17];       // WAJIB 16 digit
    char email[31];     // max 30 character
    char phone_Num[14]; // max 13 digit
    char file_Name[42]; // Username + NIK = 25 + 16 = 41

    // BST based on username
    struct customer *left;
    struct customer *right;
};

struct portfolio
{
    char saham[5]; // kode saham cmn 4 karakter (BBRI, BBCA, BREN, dll)
    int lot;
    double avg_Price;
    double total_Invested;

    // BST based on total_invested
    struct portfolio *left;
    struct portfolio *right;
};

void to_Lowercase(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower((unsigned char)str[i]);
    }
}

void to_Uppercase(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = toupper((unsigned char)str[i]);
    }
}

void clear_Screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int wait_Key()
{
    printf("\033[1;33m");
    printf("Press any key to continue...");
    printf("\033[1;0m");
    getch();
    clear_Screen();
    return 0;
}

int digits_Only(const char *s)
{
    while (*s)
    {
        if (isdigit(*s++) == 0)
            return 0;
    }
    return 1;
}

int validate_Double(const char *str)
{
    char *endptr;
    strtod(str, &endptr);

    return *endptr == '\0' && endptr != str;
}

// Validate Menu Input
int validate_Option_Menu()
{
    int valid_Flag = 0;
    char temp[100];
    int option = 0;

    do
    {
        printf(">> ");
        scanf(" %[^\n]", temp);

        if (digits_Only(temp) == 1)
        {
            valid_Flag = 1;
            option = atoi(temp);
        }
        else
        {
            printf("\033[1;31m");
            printf("Option should be a number!\n");
            printf("\033[1;0m");
        }

    } while (valid_Flag != 1);

    return option;
}

// Validate Name
void validate_Username(char username[])
{
    int valid_Flag = 0;

    do
    {
        printf("Enter username: ");
        scanf(" %[^\n]", username);

        if (strlen(username) > 2 && strlen(username) < 26)
        {
            valid_Flag = 1;

            int loop = 0;
            for (loop = 0; loop < strlen(username); loop++)
            {
                if (!isalpha(username[loop]))
                {
                    valid_Flag = 0;
                    printf("\033[1;31m");
                    printf("Username must only consist of alphabetic characters!\n");
                    printf("\033[1;0m");
                    break;
                }
            }
        }
        else
        {
            printf("\033[1;31m");
            printf("Username must be between 3-25 characters!\n");
            printf("\033[1;0m");
        }

    } while (valid_Flag != 1);
    printf("\n");
    to_Lowercase(username);
}

// Validate NIK
int search_NIK(struct customer *root, char nik[])
{
    if (root == NULL)
    {
        return 0;
    }

    if (strcmp(nik, root->nik) == 0)
    {
        return 1;
    }

    if (search_NIK(root->left, nik))
    {
        return 1;
    }
    return search_NIK(root->right, nik);
}

void validate_NIK(char nik[])
{
    int valid_Flag = 0;

    do
    {
        printf("Enter NIK: ");
        scanf(" %[^\n]", nik);

        if (digits_Only(nik) == 1)
        {
            if (strlen(nik) == 16)
            {
                valid_Flag = 1;
            }
            else
            {
                printf("\033[1;31m");
                printf("NIK must consist of 16 digits!\n");
                printf("\033[1;0m");
            }
        }
        else
        {
            printf("\033[1;31m");
            printf("NIK must consist of only numbers!\n");
            printf("\033[1;0m");
        }

    } while (valid_Flag != 1);
    // printf("\n");
}

// Validate Email
void validate_Email(char email[])
{
    int valid_Flag = 0;

    do
    {
        printf("Enter email: ");
        scanf(" %[^\n]", email);

        if (strlen(email) > 2 && strlen(email) < 31)
        {
            char *at_ptr = strchr(email, '@');
            if (at_ptr != NULL && strchr(at_ptr, '.') != NULL)
            {
                valid_Flag = 1;
                for (int i = 0; i < strlen(email); i++)
                {
                    if (!(isalnum(email[i]) || email[i] == '@' || email[i] == '.' || email[i] == '-' || email[i] == '_'))
                    {
                        valid_Flag = 0;
                        printf("\033[1;31m");
                        printf("Email contains invalid characters!\n");
                        printf("\033[1;0m");
                        break;
                    }
                }
            }
            else
            {
                printf("\033[1;31m");
                printf("Email must contain '@' and a domain (e.g., 'example@domain.com')!\n");
                printf("\033[1;0m");
            }
        }
        else
        {
            printf("\033[1;31m");
            printf("Email must be between 3-30 characters!\n");
            printf("\033[1;0m");
        }

    } while (valid_Flag != 1);
    printf("\n");
}

// Validate Phone Number
void validate_Phone(char phone_Num[])
{
    int valid_Flag = 0;

    do
    {
        printf("Enter phone number: ");
        scanf(" %[^\n]", phone_Num);

        if (digits_Only(phone_Num) == 1)
        {
            if (strlen(phone_Num) > 9 && strlen(phone_Num) < 14)
            {
                valid_Flag = 1;
            }
            else
            {
                printf("\033[1;31m");
                printf("Phone number must be between 10-13 digits!\n");
                printf("\033[1;0m");
            }
        }
        else
        {
            printf("\033[1;31m");
            printf("Phone number must consist of only numbers!\n");
            printf("\033[1;0m");
        }

    } while (valid_Flag != 1);
    printf("\n");
}

// Validate Stock Name
void validate_Stock(char stock[])
{
    int valid_Flag = 0;

    do
    {
        printf("Enter stock (name/code): ");
        scanf(" %[^\n]", stock);

        if (strlen(stock) == 4)
        {
            valid_Flag = 1;

            int loop = 0;
            for (loop = 0; loop < strlen(stock); loop++)
            {
                if (!isalpha(stock[loop]))
                {
                    valid_Flag = 0;
                    printf("\033[1;31m");
                    printf("Stock (name/code) must only consist of alphabetic characters!\n");
                    printf("\033[1;0m");
                    break;
                }
            }
        }
        else
        {
            printf("\033[1;31m");
            printf("Stock (name/code) must be 4 characters long!\n");
            printf("\033[1;0m");
        }

    } while (valid_Flag != 1);

    to_Uppercase(stock);
    printf("\n");
}

// Validate Lot Entry
int validate_Lot_Entry()
{
    int valid_Flag = 0;
    char temp[100];
    int lot;

    do
    {
        printf("Enter lot size: ");
        scanf(" %[^\n]", temp);

        if (digits_Only(temp) == 1)
        {
            lot = atoi(temp);

            if (lot > 0)
            {
                valid_Flag = 1;
            }
            else
            {
                printf("\033[1;31m");
                printf("Lot size must be a positive number!\n");
                printf("\033[1;0m");
            }
        }
        else
        {
            printf("\033[1;31m");
            printf("Option should be a number!\n");
            printf("\033[1;0m");
        }

    } while (valid_Flag != 1);

    printf("\n");
    return lot;
}

// Validate Lot Exit
int validate_Lot_Exit(int available_Lot)
{
    int valid_Flag = 0;
    int lot;
    char temp[100];

    do
    {
        printf("Enter lot size: ");
        scanf(" %[^\n]", temp);

        if (digits_Only(temp) == 1)
        {
            lot = atoi(temp);

            if (lot > 0)
            {
                if (lot <= available_Lot)
                {
                    valid_Flag = 1;
                }
                else
                {
                    printf("\033[1;31m");
                    printf("Lot size exceeds available lot size (\033[1;33m%d\033[1;31m)!\n", available_Lot);
                    printf("\033[1;0m");
                }
            }
            else
            {
                printf("\033[1;31m");
                printf("Lot size must be a positive number!\n");
                printf("\033[1;0m");
            }
        }
        else
        {
            printf("\033[1;31m");
            printf("Option should be a number!\n");
            printf("\033[1;0m");
        }

    } while (valid_Flag != 1);

    printf("\n");
    return lot;
}

// Validate Average Price
double validate_Avg_Price()
{
    int valid_Flag = 0;
    char temp[100];
    double avg_Price = 0;

    do
    {
        printf("Enter average price entry: ");
        scanf(" %[^\n]", temp);

        if (validate_Double(temp))
        {
            avg_Price = strtod(temp, NULL);
            if (avg_Price > 0)
            {
                valid_Flag = 1;
            }
            else
            {
                printf("\033[1;31m");
                printf("Average price must be a positive number!\n");
                printf("\033[0m");
            }
        }
        else
        {
            printf("\033[1;31m");
            printf("Average price must be a number!\n");
            printf("\033[0m");
        }

    } while (valid_Flag != 1);
    printf("\n");
    return avg_Price;
}

// Validate Update Option
void validate_Option_Update(char option_Update[])
{
    int valid_Flag = 0;

    do
    {
        printf("Do you want to [buy/sell] lot(s): ");
        scanf(" %[^\n]", option_Update);
        to_Lowercase(option_Update);

        if (strcmp(option_Update, "buy") == 0 || strcmp(option_Update, "sell") == 0)
        {
            valid_Flag = 1;
        }
        else
        {
            printf("\033[1;31m");
            printf("Invalid option! Please enter \033[1;33m'buy'\033[1;31m or \033[1;33m'sell'\033[1;31m.\n");
            printf("\033[1;0m");
        }
    } while (valid_Flag != 1);
    printf("\n");
}

// Validate Yes No
void validate_Option_YN(char option_YN[], char sentence[])
{
    int valid_Flag = 0;

    do
    {
        printf("%s", sentence);
        scanf(" %[^\n]", option_YN);
        to_Lowercase(option_YN);

        if (strcmp(option_YN, "y") == 0 || strcmp(option_YN, "n") == 0)
        {
            valid_Flag = 1;
        }
        else
        {
            printf("\033[1;31m");
            printf("Invalid option! Please enter \033[1;33m'y'\033[1;31m or \033[1;33m'n'\033[1;31m.\n");
            printf("\033[1;0m");
        }
    } while (valid_Flag != 1);
    printf("\n");
}

// Segala function punya portfolio_BST
// Portfolio BST "Search"
struct portfolio *search_Portfolio_BST(struct portfolio *root, char saham[])
{
    if (root == NULL)
    {
        return NULL;
    }

    // Compare saham
    if (strcmp(saham, root->saham) == 0)
    {
        return root;
    }

    struct portfolio *found_Node = search_Portfolio_BST(root->left, saham);
    if (found_Node == NULL)
    {
        found_Node = search_Portfolio_BST(root->right, saham);
    }
    return found_Node;
}

// Portfolio BST "Create New Node"
struct portfolio *create_New_Portfolio(char saham[], int lot, double avg_Price, double total_Invested)
{
    struct portfolio *new_Portfolio = (struct portfolio *)malloc(sizeof(struct portfolio));
    strcpy(new_Portfolio->saham, saham);
    new_Portfolio->lot = lot;
    new_Portfolio->avg_Price = avg_Price;
    new_Portfolio->total_Invested = total_Invested;

    new_Portfolio->left = NULL;
    new_Portfolio->right = NULL;
    return new_Portfolio;
}

// Portfolio BST "Insert Node"
struct portfolio *insert_Portfolio(struct portfolio **root, char saham[], int lot, double avg_Price, double total_Invested)
{
    if (*root == NULL)
    {
        *root = create_New_Portfolio(saham, lot, avg_Price, total_Invested);
    }
    else if (total_Invested < (*root)->total_Invested)
    {
        (*root)->left = insert_Portfolio(&(*root)->left, saham, lot, avg_Price, total_Invested);
    }
    else if (total_Invested > (*root)->total_Invested)
    {
        (*root)->right = insert_Portfolio(&(*root)->right, saham, lot, avg_Price, total_Invested);
    }

    return *root;
}

// Portfolio BST "Entry Stock"
void entry_Portfolio_BST(struct portfolio **root)
{
    clear_Screen();

    printf("\033[1;34m");
    printf("====================\n");
    printf("\033[1;33m");
    printf("#   Entry Stock   #\n");
    printf("\033[1;34m");
    printf("====================\n\n");
    printf("\033[1;0m");

    char saham_Input[100];
    validate_Stock(saham_Input);

    struct portfolio *temp_Saham = search_Portfolio_BST(*root, saham_Input);
    if (temp_Saham != NULL)
    {
        char option_YN[100];
        char sentence[] = "Do you want to update its lot instead? [y/n]: ";
        printf("\033[1;31m");
        printf("Stock already exists!\n");
        printf("\033[1;0m");
        validate_Option_YN(option_YN, sentence);

        if (strcmp(option_YN, "y") == 0)
        {
            update_Portfolio_BST(&(*root));
        }

        // selesai update atau user input "n" langsung return
        free(temp_Saham);
        return;
    }

    int lot_Input;
    lot_Input = validate_Lot_Entry();

    double avg_Price_Input;
    avg_Price_Input = validate_Avg_Price();

    double total_Invested_Input;
    total_Invested_Input = (lot_Input * 100 * avg_Price_Input);

    *root = insert_Portfolio(&(*root), saham_Input, lot_Input, avg_Price_Input, total_Invested_Input);
    free(temp_Saham);
}

// Portfolio BST "Reversed In-Order Print"
void reverse_In_Order_Portfolio(struct portfolio *root)
{ // total_Invested yg tinggi tampil dulu jadi tranversal dri kanan bST
    if (root != NULL)
    {
        reverse_In_Order_Portfolio(root->right);
        // printf("");
        printf("\033[1;34m|\033[1;0m %-5s \033[1;34m|\033[1;0m %-10d \033[1;34m|\033[1;0m %-13.2lf \033[1;34m|\033[1;0m %-14.2lf \033[1;34m|\n", root->saham, root->lot, root->avg_Price, root->total_Invested);
        printf("-------------------------------------------------------\n");
        printf("\033[1;0m");
        reverse_In_Order_Portfolio(root->left);
    }
}

// Portfolio BST "View"
void view_Portfolio_BST(struct portfolio *root)
{
    if (root == NULL)
    {
        printf("\033[1;31m");
        printf("There is no data yet!\n\n");
        printf("\033[1;0m");
    }
    else
    {
        printf("\033[1;34m");
        printf("======================\n");
        printf("\033[1;33m");
        printf("#   View Portfolio   #\n");
        printf("\033[1;34m");
        printf("======================\n\n");

        printf("-------------------------------------------------------\n");
        printf("|\033[1;33m %-5s \033[1;34m|\033[1;33m %-10s \033[1;34m|\033[1;33m %-13s \033[1;34m|\033[1;33m %-14s \033[1;34m|\n", "Saham", "Jumlah Lot", "Average Price", "Total Invested");
        printf("-------------------------------------------------------\n");
        printf("\033[1;0m");
        reverse_In_Order_Portfolio(root);
    }
}

// Portfolio BST "Find Minimum"
struct portfolio *find_Portfolio_Minimum(struct portfolio *root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

// Portfolio BST "Delete Data"
void delete_Portfolio_Data(struct portfolio **root, char saham_Input[])
{
    if (*root == NULL)
    {
        return;
    }

    delete_Portfolio_Data(&((*root)->left), saham_Input);
    delete_Portfolio_Data(&((*root)->right), saham_Input);

    if (strcmp((*root)->saham, saham_Input) == 0)
    {
        if ((*root)->left == NULL)
        {
            struct portfolio *temp = *root;
            *root = (*root)->right;
            free(temp);
        }
        else if ((*root)->right == NULL)
        {
            struct portfolio *temp = *root;
            *root = (*root)->left;
            free(temp);
        }
        else
        {
            struct portfolio *temp = find_Portfolio_Minimum((*root)->right);
            strcpy((*root)->saham, temp->saham);
            (*root)->lot = temp->lot;
            (*root)->avg_Price = temp->avg_Price;
            (*root)->total_Invested = temp->total_Invested;
            delete_Portfolio_Data(&((*root)->right), temp->saham);
        }
    }
}

// Portfolio BST "Remove"
void remove_Portfolio_BST(struct portfolio **root)
{
    if (*root == NULL)
    {
        printf("\033[1;31m");
        printf("There is no data yet!\n\n");
        printf("\033[1;0m");
        return;
    }

    printf("\033[1;34m");
    printf("====================\n");
    printf("\033[1;33m");
    printf("#   Remove Stock   #\n");
    printf("\033[1;34m");
    printf("====================\n\n");
    printf("\033[1;0m");

    char saham_Input[100];
    validate_Stock(saham_Input);

    struct portfolio *temp = search_Portfolio_BST(*root, saham_Input);
    if (temp == NULL)
    {
        printf("\033[1;31m");
        printf("Stock doesn't exist!\n");
        printf("\033[1;0m");
    }
    else
    {
        delete_Portfolio_Data(root, saham_Input);
        printf("\033[1;31m");
        printf("Remove success!\n\n");
        printf("\033[1;0m");
    }
}

// Portfolio BST "Update"
void update_Portfolio_BST(struct portfolio **root)
{
    clear_Screen();
    if (*root == NULL)
    {
        printf("\033[1;31m");
        printf("There is no data yet!\n\n");
        printf("\033[1;0m");
        return;
    }

    printf("\033[1;34m");
    printf("====================\n");
    printf("\033[1;33m");
    printf("#   Update Stock   #\n");
    printf("\033[1;34m");
    printf("====================\n\n");
    printf("\033[1;0m");

    char saham_Input[100];
    validate_Stock(saham_Input);

    struct portfolio *temp_Saham = search_Portfolio_BST(*root, saham_Input);
    if (temp_Saham == NULL)
    {
        char option_YN[100];
        char sentence[] = "Do you want to entry new stock instead? [y/n]: ";
        printf("\033[1;31m");
        printf("Stock doesn't exist!\n");
        printf("\033[1;0m");
        validate_Option_YN(option_YN, sentence);

        if (strcmp(option_YN, "y") == 0)
        {
            entry_Portfolio_BST(&(*root));
        }
        return;
    }

    printf("\033[1;33m");
    printf("Stock: \033[1;0m%s\n", temp_Saham->saham);
    printf("\033[1;33m");
    printf("Lot Size: \033[1;0m%d\n", temp_Saham->lot);
    printf("\033[1;33m");
    printf("Average Price: \033[1;0m%lf\n", temp_Saham->avg_Price);
    printf("\033[1;33m");
    printf("Total Invested: \033[1;0m%lf\n\n", temp_Saham->total_Invested);

    char option_Update[100];
    validate_Option_Update(option_Update);

    if (strcmp(option_Update, "buy") == 0)
    {
        int lot_Update = 0;
        double avg_Price_Update = 0;

        lot_Update = validate_Lot_Entry();
        avg_Price_Update = validate_Avg_Price();

        temp_Saham->avg_Price = ((temp_Saham->lot * temp_Saham->avg_Price) + (lot_Update * avg_Price_Update)) / (temp_Saham->lot + lot_Update);
        temp_Saham->lot = temp_Saham->lot + lot_Update;
        temp_Saham->total_Invested = temp_Saham->lot * temp_Saham->avg_Price * 100;
    }
    else if (strcmp(option_Update, "sell") == 0)
    {
        int lot_Update = 0;
        lot_Update = validate_Lot_Exit(temp_Saham->lot);

        temp_Saham->lot = temp_Saham->lot - lot_Update;
        temp_Saham->total_Invested = temp_Saham->lot * temp_Saham->avg_Price * 100;

        if (temp_Saham->lot == 0)
        {
            delete_Portfolio_Data(&(*root), saham_Input);
            printf("\033[1;33m");
            printf("Stock removed from portfolio because lot size is zero.\n");
            printf("\033[1;0m");
        }
    }
}

// Portfolio BST "Initialize File"
struct portfolio *read_Portfolio_File(const char *file_Name_Input)
{
    FILE *portfolio_Data = fopen(file_Name_Input, "r");
    if (portfolio_Data == NULL)
    {
        perror("File not found!");
        return NULL;
    }

    struct portfolio *root = NULL;
    char line[128];

    while (fgets(line, sizeof(line), portfolio_Data))
    {
        char saham[5];
        int lot;
        double avg_Price;
        double total_Invested;

        if (sscanf(line, "%4[^#]#%d#%lf#%lf", saham, &lot, &avg_Price, &total_Invested) == 4)
        {
            root = insert_Portfolio(&root, saham, lot, avg_Price, total_Invested);
        }
    }

    fclose(portfolio_Data);
    return root;
}

// Portfolio BST "Exit"
void write_Portfolio_File(FILE *portfolio_Data, struct portfolio *root)
{
    if (root != NULL)
    {
        write_Portfolio_File(portfolio_Data, root->left);
        fprintf(portfolio_Data, "%s#%d#%lf#%lf\n", root->saham, root->lot, root->avg_Price, root->total_Invested);
        write_Portfolio_File(portfolio_Data, root->right);
    }
}

void free_Portfolio_BST(struct portfolio *root)
{
    if (root == NULL)
    {
        return;
    }
    free_Portfolio_BST(root->left);
    free_Portfolio_BST(root->right);
    free(root);
}

void exit_Portfolio_BST(struct portfolio *root, const char *portfolio_File_Name)
{
    FILE *portfolio_Data = fopen(portfolio_File_Name, "w");
    write_Portfolio_File(portfolio_Data, root);
    free_Portfolio_BST(root);
    fclose(portfolio_Data);
}

// Menu Portfolio
void portfolio_Menu(const char *file_Name)
{
    struct portfolio *portfolio_BST = read_Portfolio_File(file_Name);

    int option;
    do
    {
        option = 0;
        printf("\033[1;34m");
        printf("#---------------------------#\n");
        // printf("\033[1;33m");
        printf("|\033[1;33m       Portfolio Menu      \033[1;34m|\n");
        // printf("\033[1;0m");
        printf("#---------------------------#\n");
        printf("| \033[1;0m[1] Entry Stock           \033[1;34m|\n");
        printf("| \033[1;0m[2] View Stock            \033[1;34m|\n");
        printf("| \033[1;0m[3] Update Stock          \033[1;34m|\n");
        printf("| \033[1;0m[4] Remove Stock          \033[1;34m|\n");
        printf("| \033[1;31m[5] Logout                \033[1;34m|\n");
        printf("#---------------------------#\n");
        printf("\033[0m");
        // printf(">> ");
        // scanf("%d", &option);

        option = validate_Option_Menu();

        if (option < 1 || option > 5)
        {
            printf("\033[1;31m");
            printf("Invalid input!\n");
            printf("\033[1;0m");
            wait_Key();
        }
        else
        {
            switch (option)
            {
            case 1:
            {
                clear_Screen();
                entry_Portfolio_BST(&portfolio_BST);
                wait_Key();
                break;
            }
            case 2:
            {
                clear_Screen();
                view_Portfolio_BST(portfolio_BST);
                wait_Key();
                break;
            }
            case 3:
            {
                clear_Screen();
                update_Portfolio_BST(&portfolio_BST);
                wait_Key();
                break;
            }
            case 4:
            {
                clear_Screen();
                remove_Portfolio_BST(&portfolio_BST);
                wait_Key();
                break;
            }
            case 5:
            {
                clear_Screen();
                printf("\033[1;33m");
                printf("Logged out successfully!\n\n");
                printf("\033[1;0m");
                exit_Portfolio_BST(portfolio_BST, file_Name);
                break;
            }
            }
        }
    } while (option != 5);
}

// Segala function punya customer_BST
// Customer BST "Search"
struct customer *search_Customer_BST(struct customer *root, char file_Name[])
{
    if (root == NULL)
    {
        return NULL;
    }

    int cmp = strcmp(file_Name, root->file_Name);
    if (cmp == 0)
    {
        return root;
    }
    else if (cmp < 0)
    {
        return search_Customer_BST(root->left, file_Name);
    }
    else
    {
        return search_Customer_BST(root->right, file_Name);
    }
}

struct customer *search_By_NIK_Customer_BST(struct customer *root, char nik[])
{
    if (root == NULL)
    {
        return NULL;
    }

    if (strcmp(nik, root->nik) == 0)
    {
        return root;
    }

    struct customer *temp_Search = search_By_NIK_Customer_BST(root->left, nik);
    if (temp_Search != NULL)
    {
        return temp_Search;
    }

    return search_By_NIK_Customer_BST(root->right, nik);
}

// Customer BST "Create New Node"
struct customer *create_New_Customer(char username[], char nik[], char email[], char phone_Num[], char file_Name[])
{
    struct customer *new_Customer = (struct customer *)malloc(sizeof(struct customer));
    strcpy(new_Customer->username, username);
    strcpy(new_Customer->nik, nik);
    strcpy(new_Customer->email, email);
    strcpy(new_Customer->phone_Num, phone_Num);
    strcpy(new_Customer->file_Name, file_Name);

    new_Customer->left = NULL;
    new_Customer->right = NULL;
    return new_Customer;
}

// Customer BST "Insert Node"
struct customer *insert_Customer(struct customer **root, char username[], char nik[], char email[], char phone_Num[], char file_Name[])
{
    // yg lbh kecil valuenya ke kiri
    if (*root == NULL)
    {
        *root = create_New_Customer(username, nik, email, phone_Num, file_Name);
    }
    else if (strcmp(file_Name, (*root)->file_Name) < 0)
    {
        (*root)->left = insert_Customer(&(*root)->left, username, nik, email, phone_Num, file_Name);
    }
    else if (strcmp(file_Name, (*root)->file_Name) > 0)
    {
        (*root)->right = insert_Customer(&(*root)->right, username, nik, email, phone_Num, file_Name);
    }

    return *root;
}

// Customer BST "Login"
void login_Customer_BST(struct customer *root)
{
    char username_Input[100];
    char nik_Input[100];
    char file_Name_Input[42];

    printf("\033[1;34m");
    printf("===========================\n");
    printf("\033[1;33m");
    printf("#   Login Customer Data   #\n");
    printf("\033[1;34m");
    printf("===========================\n\n\033[1;0m");

    validate_Username(username_Input);
    validate_NIK(nik_Input);
    printf("\n");

    strcpy(file_Name_Input, username_Input);
    strcat(file_Name_Input, nik_Input);

    struct customer *temp = search_Customer_BST(root, file_Name_Input);
    if (temp == NULL)
    {
        printf("\033[1;31m");
        printf("Customer not found!\n\n");
        printf("\033[1;0m");
        return;
    }

    // else
    printf("\033[1;32m");
    printf("Login successful!\n\n");
    printf("\033[1;0m");
    wait_Key();

    // open file
    strcat(file_Name_Input, ".txt");
    portfolio_Menu(file_Name_Input);
}

// Customer BST "Register"
void register_Customer_BST(struct customer **root)
{
    char username_Input[100];
    char nik_Input[100];
    char email_Input[100];
    char phone_Num_Input[100];
    char file_Name_Input[42];

    printf("\033[1;34m");
    printf("==============================\n\033[1;0m");
    printf("\033[1;33m");
    printf("#   Register Customer Data   #\n");
    printf("\033[1;34m");
    printf("==============================\n\n\033[1;0m");

    validate_Username(username_Input);

    int temp_Check_NIK = 0;
    do
    {
        validate_NIK(nik_Input);

        temp_Check_NIK = search_NIK(*root, nik_Input);

        if (temp_Check_NIK == 1)
        {
            printf("\033[1;31mNIK already used!\n\033[1;0m");
        }
        else
        {
            printf("\n");
        }

    } while (temp_Check_NIK == 1);

    strcpy(file_Name_Input, username_Input);
    strcat(file_Name_Input, nik_Input);

    struct customer *temp = search_Customer_BST(*root, file_Name_Input);
    if (temp != NULL)
    {
        printf("\033[1;31m");
        printf("Customer already exists!\n");
        printf("\033[1;0m");
        free(temp);
        return;
    }

    validate_Email(email_Input);
    validate_Phone(phone_Num_Input);

    *root = insert_Customer(&(*root), username_Input, nik_Input, email_Input, phone_Num_Input, file_Name_Input);

    // buat file.txt baru untuk data saham user yg baru diinput
    strcat(file_Name_Input, ".txt");
    FILE *create_New_File = fopen(file_Name_Input, "w");
    printf("\033[1;32m");
    printf("Customer registered successfully!\n\n");
    printf("\033[1;0m");
    fclose(create_New_File);

    return *root;
}

// Customer BST "In-Order Print"
void in_Order_Customer(struct customer *root)
{
    if (root != NULL)
    {
        in_Order_Customer(root->left);
        printf("\033[1;34m|\033[1;0m %-25s \033[1;34m|\033[1;0m %-16s \033[1;34m|\033[1;0m %-31s \033[1;34m|\033[1;0m %-16s \033[1;34m|\033[1;0m %-42s \033[1;34m|\n", root->username, root->nik, root->email, root->phone_Num, root->file_Name);
        printf("--------------------------------------------------------------------------------------------------------------------------------------------------\033[1;0m\n");
        in_Order_Customer(root->right);
    }
}

// Customer BST "View"
void view_Customer_BST(struct customer *root)
{
    if (root == NULL)
    {
        printf("\033[1;31m");
        printf("There is no data yet!\n\n");
        printf("\033[1;0m");
    }
    else
    {
        printf("\033[1;34m");
        printf("==========================\n");
        printf("\033[1;33m");
        printf("#   View Customer Data   #\n");
        printf("\033[1;34m");
        printf("==========================\n\n");
        printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("|\033[1;33m %-25s \033[1;34m|\033[1;33m %-16s \033[1;34m|\033[1;33m %-31s \033[1;34m|\033[1;33m %-16s \033[1;34m|\033[1;33m %-42s \033[1;34m|\n", "Username", "NIK", "Email", "Phone Number", "File Name");
        printf("--------------------------------------------------------------------------------------------------------------------------------------------------\033[1;0m\n");
        in_Order_Customer(root);
    }
}

// Customer BST "Search Specific"
void find_Specific_Customer_BST(struct customer *root)
{
    if (root == NULL)
    {
        printf("\033[1;31m");
        printf("There is no data yet!\n\n");
        printf("\033[1;0m");
    }
    else
    {
        char nik_Input[100];
        printf("\033[1;34m");
        printf("============================\n");
        printf("\033[1;33m");
        printf("#   Search Customer Data   #\n");
        printf("\033[1;34m");
        printf("============================\n\n");
        printf("\033[1;0m");
        validate_NIK(nik_Input);

        struct customer *found_Customer = search_By_NIK_Customer_BST(root, nik_Input);

        if (found_Customer != NULL)
        {
            printf("\033[1;34m");
            printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("|\033[1;33m %-25s \033[1;34m|\033[1;33m %-16s \033[1;34m|\033[1;33m %-31s \033[1;34m|\033[1;33m %-16s \033[1;34m|\033[1;33m %-42s \033[1;34m|\n", "Username", "NIK", "Email", "Phone Number", "File Name");
            printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("|\033[1;0m %-25s \033[1;34m|\033[1;0m %-16s \033[1;34m|\033[1;0m %-31s \033[1;34m|\033[1;0m %-16s \033[1;34m|\033[1;0m %-42s \033[1;34m|\n", found_Customer->username, found_Customer->nik, found_Customer->email, found_Customer->phone_Num, found_Customer->file_Name);
            printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("\033[1;0m");
        }
        else
        {
            printf("\033[1;31m");
            printf("Customer with that NIK doesn't exist!\n\n");
            printf("\033[1;0m");
        }
    }
}

// Customer BST "Find Minimum"
struct customer *find_Customer_Minimum(struct customer *root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

// Customer BST "Delete Data"
void delete_Customer_Data(struct customer **root, char file_Name_Input[])
{
    if (*root == NULL)
    {
        return;
    }

    int cmp = strcmp(file_Name_Input, (*root)->file_Name);

    if (cmp > 0)
    {
        delete_Customer_Data(&((*root)->right), file_Name_Input);
    }
    else if (cmp < 0)
    {
        delete_Customer_Data(&((*root)->left), file_Name_Input);
    }
    else
    {
        if ((*root)->left == NULL)
        {
            struct customer *temp = *root;
            *root = (*root)->right;
            free(temp);
        }
        else if ((*root)->right == NULL)
        {
            struct customer *temp = *root;
            *root = (*root)->left;
            free(temp);
        }
        else
        {
            struct customer *temp = find_Customer_Minimum((*root)->right);
            strcpy((*root)->file_Name, temp->file_Name);
            strcpy((*root)->username, temp->username);
            strcpy((*root)->nik, temp->nik);
            strcpy((*root)->email, temp->email);
            strcpy((*root)->phone_Num, temp->phone_Num);
            delete_Customer_Data(&((*root)->right), temp->file_Name);
        }
    }
}

// Customer BST "Remove"
void remove_Customer_BST(struct customer **root)
{
    if (*root == NULL)
    {
        printf("\033[1;31m");
        printf("There is no data yet!\n\n");
        printf("\033[1;0m");
        return;
    }

    printf("\033[1;34m");
    printf("============================\n\033[1;0m");
    printf("\033[1;33m");
    printf("#   Remove Customer Data   #\n");
    printf("\033[1;34m");
    printf("============================\n\n\033[1;0m");

    char name_Input[100];
    validate_Username(name_Input);

    char nik_Input[100];
    validate_NIK(nik_Input);

    char file_Name_Input[42];
    strcpy(file_Name_Input, name_Input);
    strcat(file_Name_Input, nik_Input);

    struct customer *temp = search_Customer_BST(*root, file_Name_Input);
    if (temp == NULL)
    {
        printf("\033[1;31m");
        printf("\nUsername or NIK incorrect!\n");
        printf("\033[1;0m");
    }
    else
    {
        delete_Customer_Data(&(*root), file_Name_Input);
        strcat(file_Name_Input, ".txt");
        remove(file_Name_Input);
        printf("\033[1;31m");
        printf("\nDelete success!\n\n");
        printf("\033[1;0m");
    }
}

// Customer BST "Initialize File"
struct customer *read_Customer_File(const char *customer_File_Name)
{
    FILE *customer_Data = fopen(customer_File_Name, "r");
    if (customer_Data == NULL)
    {
        perror("File not found!");
        return NULL;
    }

    struct customer *root = NULL;
    char line[128];

    while (fgets(line, sizeof(line), customer_Data))
    {
        char username[26];
        char nik[17];
        char email[31];
        char phone_Num[17];
        char file_Name[42];

        if (sscanf(line, "%25[^#]#%16[^#]#%30[^#]#%16[^#]#%31[^\n]", username, nik, email, phone_Num, file_Name) == 5)
        {
            root = insert_Customer(&root, username, nik, email, phone_Num, file_Name);
        }
    }

    fclose(customer_Data);
    return root;
}

// Customer BST "Exit"
void write_Customer_File(FILE *customer_Data, struct customer *root)
{
    if (root != NULL)
    {
        write_Customer_File(customer_Data, root->left);
        fprintf(customer_Data, "%s#%s#%s#%s#%s\n", root->username, root->nik, root->email, root->phone_Num, root->file_Name);
        write_Customer_File(customer_Data, root->right);
    }
}

void free_Customer_BST(struct customer *root)
{
    if (root == NULL)
    {
        return;
    }
    free_Customer_BST(root->left);
    free_Customer_BST(root->right);
    free(root);
}

void exit_Customer_BST(struct customer *root, const char *customer_File_Name)
{
    FILE *customer_Data = fopen(customer_File_Name, "w");
    write_Customer_File(customer_Data, root);
    free_Customer_BST(root);
    fclose(customer_Data);
}

// Menu Customer
int customer_Menu()
{
    int option;
    int valid_Flag = 0;
    clear_Screen();

    do
    {
        printf("\033[1;34m");
        printf("#---------------------------#\n");
        printf("|\033[1;33m       Customer Menu       \033[1;34m|\n");
        printf("#---------------------------#\n");
        printf("|\033[1;0m [1] Login                 \033[1;34m|\n");
        printf("|\033[1;0m [2] Register              \033[1;34m|\n");
        printf("|\033[1;0m [3] View All              \033[1;34m|\n");
        printf("|\033[1;0m [4] Search                \033[1;34m|\n");
        printf("|\033[1;0m [5] Remove                \033[1;34m|\n");
        printf("|\033[1;31m [6] Exit                  \033[1;34m|\n");
        printf("#---------------------------#\n");
        printf("\033[0m");

        option = validate_Option_Menu();

        if (option < 1 || option > 6)
        {
            printf("\033[1;31m");
            printf("Invalid input!\n");
            printf("\033[1;0m");
            wait_Key();
        }
        else
        {
            valid_Flag = 1;
        }

    } while (valid_Flag == 0);

    return option;
}

int main()
{
    const char *customer_File_Name = "customer.txt";
    struct customer *customer_BST = read_Customer_File(customer_File_Name);

    int option;
    do
    {
        option = customer_Menu();
        switch (option)
        {
        case 1:
        { // Login
            clear_Screen();
            login_Customer_BST(customer_BST);
            wait_Key();
            break;
        }
        case 2:
        { // Register
            clear_Screen();
            register_Customer_BST(&customer_BST);
            wait_Key();
            break;
        }
        case 3:
        { // View
            clear_Screen();
            view_Customer_BST(customer_BST);
            wait_Key();
            break;
        }
        case 4:
        { // Search Specific
            clear_Screen();
            find_Specific_Customer_BST(customer_BST);
            wait_Key();
            break;
        }
        case 5:
        { // Delete
            clear_Screen();
            remove_Customer_BST(&customer_BST);
            wait_Key();
            break;
        }
        case 6:
        { // Exit
            printf("\033[1;33m");
            printf("Thank you for using our program!\n");
            printf("\033[1;0m");
            exit_Customer_BST(customer_BST, customer_File_Name);
            break;
        }
        }
    } while (option != 6);

    return 0;
}