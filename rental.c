#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define FILE_NAME "records.save"
#define DATE_FORMAT "%d-%m-%Y"

typedef struct
{
    int car_id;
    char car_name[100];
} CarStruct;

typedef struct
{
    int rent_id;
    char customer_name[20];
    int car_id;
    char rent_date[20];
    char return_date[20];
} RentRecordStruct;

void rent_car();
void view_cars();
void return_car();
void view_rented_cars();

int generate_rent_id();
void clear_screen();
void print_menu();
void get_current_date(char *buffer);
void save_record(RentRecordStruct record);
void wait_enter();

CarStruct cars[8] = {
    {1, "Mitsubishi Pajero Sport"},
    {2, "Toyota Kijang Innova"},
    {3, "Toyota Avanza"},
    {4, "Wuling Air EV"},
    {5, "Daihatsu Sigra"},
    {6, "Toyota Camry"},
    {7, "Honda Jazz"},
    {8, "Nissan March"}
};

int main()
{
    srand(time(NULL));

    clear_screen();
    puts("Car rental system");
    printf("\n");

    do
    {
        char confirmation = '\0';
        print_menu();

        printf("Your choice: ");
        scanf(" %c", &confirmation);
        getchar();

        switch (confirmation)
        {
        case '1':
            rent_car();
            wait_enter();
            clear_screen();
            break;

        case '2':
            view_cars();
            wait_enter();
            clear_screen();
            break;

        case '3':
            return_car();
            wait_enter();
            clear_screen();
            break;

        case '4':
            view_rented_cars();
            wait_enter();
            clear_screen();
            break;

        case '5':
            puts("Exiting program. Goodbye!");
            return 0;

        default:
            clear_screen();
            puts("Invalid choice! Please try again");
            printf("\n");
        }
    } while (1);

    return 0;
}

void clear_screen()
{
    printf("\e[1;1H\e[2J");
}

void print_menu()
{
    puts("1. Rent car");
    puts("2. View available cars to rent");
    puts("3. Return car");
    puts("4. View rented cars");
    puts("5. Exit program");
}

int generate_rent_id()
{
    return rand() % 1000 + 1;
}

void get_current_date(char *buffer)
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(buffer, 20, DATE_FORMAT, tm);
}

void save_record(RentRecordStruct record)
{
    FILE *file = fopen(FILE_NAME, "a");
    if (!file)
    {
        printf("Cannot open file. Exiting...");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%d#%s#%d#%s#%s\n", record.rent_id, record.customer_name, record.car_id, record.rent_date, record.return_date);
    fclose(file);
}

void view_cars()
{
    clear_screen();
    int car_count = sizeof(cars) / sizeof(CarStruct);

    puts("===================================");
    puts("|           Available Cars        |");
    puts("===================================");
    puts("|  ID   |           Name          |");
    puts("===================================");

    for (int i = 0; i < car_count; i++)
    {
        printf("|   %d   |%-25s|\n", cars[i].car_id, cars[i].car_name);
    }
    puts("===================================");
}

void rent_car()
{
    clear_screen();
    RentRecordStruct record;

    printf("Enter your name: ");
    scanf("%19s", record.customer_name); getchar();

    view_cars();
    printf("Enter Car ID to rent: ");
    scanf("%d", &record.car_id); getchar();

    record.rent_id = generate_rent_id();
    get_current_date(record.rent_date);

    printf("Enter the return date (format: DD-MM-YYYY): ");
    scanf("%19s", record.return_date); getchar();

    save_record(record);

    printf("Car rented successfully! Rent ID: %d\n", record.rent_id);
}


void view_rented_cars()
{
    clear_screen();
    FILE *file = fopen(FILE_NAME, "r");
    if (!file)
    {
        puts("No rental records found.");
        return;
    }

    puts("======================================================================================");
    puts("| Rent ID | Customer Name    | Car Name                  | Rent Date   | Return Date |");
    puts("======================================================================================");
    RentRecordStruct record;
    while (fscanf(file, "%d#%19[^#]#%d#%19[^#]#%19[^\n]\n", &record.rent_id, record.customer_name, &record.car_id, record.rent_date, record.return_date) == 5)
    {
        char car_name[100] = "Unknown";
        
        // Match id with name in CarStruct cars
        for (int i = 0; i < sizeof(cars) / sizeof(CarStruct); i++)
        {
            if (cars[i].car_id == record.car_id)
            {
                strcpy(car_name, cars[i].car_name);
                break;
            }
        }

        printf("| %-7d | %-16s | %-25s | %-11s | %-11s |\n",
               record.rent_id, record.customer_name, car_name, record.rent_date, record.return_date);
    }

    puts("======================================================================================");
    fclose(file);
}

void return_car()
{
    clear_screen();
    view_rented_cars();
    
    int rent_id;
    printf("Enter Rent ID to return: ");
    scanf("%d", &rent_id); getchar();

    FILE *file = fopen(FILE_NAME, "r");
    if (!file)
    {
        puts("No rental records found.");
        return;
    }

    FILE *temp = fopen("temp.save", "w");
    if (!temp)
    {
        printf("Cannot open temporary file. Exiting...");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    RentRecordStruct record;
    bool found = false;

    while (fscanf(file, "%d#%19[^#]#%d#%19[^#]#%19[^\n]\n", &record.rent_id, record.customer_name, &record.car_id, record.rent_date, record.return_date) == 5)
    {
        if (record.rent_id == rent_id)
        {
            found = true;
        }
        else
        {
            fprintf(temp, "%d#%s#%d#%s#%s\n", record.rent_id, record.customer_name, record.car_id, record.rent_date, record.return_date);
        }
    }

    fclose(file);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.save", FILE_NAME);

    if (found)
        printf("Car returned successfully! Rent ID: %d\n", rent_id);
    else
        printf("Rent ID %d not found.\n", rent_id);

}

void wait_enter()
{
    puts("Press enter to go back...");
    getchar();
}
