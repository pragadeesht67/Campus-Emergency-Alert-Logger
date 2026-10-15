#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALERTS 100
#define FILE_NAME "alerts_database.txt"

// Structure to hold alert details
typedef struct {
    int alert_id;
    char student_name[50];
    char emergency_type[30];
    char location[50];
    char status[20];
} Alert;

// Function Prototypes
void log_alert(Alert *alerts, int *count);
void view_alerts(Alert *alerts, int count);
void save_to_file(Alert *alerts, int count);
void load_from_file(Alert *alerts, int *count);

int main() {
    Alert campus_alerts[MAX_ALERTS];
    int alert_count = 0;
    int choice;

    load_from_file(campus_alerts, &alert_count);

    while(1) {
        printf("\n=== Campus Emergency Alert System ===\n");
        printf("1. Log New Emergency Alert\n");
        printf("2. View Active Alerts\n");
        printf("3. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear the newline character from buffer

        switch(choice) {
            case 1:
                log_alert(campus_alerts, &alert_count);
                break;
            case 2:
                view_alerts(campus_alerts, alert_count);
                break;
            case 3:
                save_to_file(campus_alerts, alert_count);
                printf("Exiting system. Stay safe!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

void log_alert(Alert *alerts, int *count) {
    if (*count >= MAX_ALERTS) {
        printf("Alert database is full!\n");
        return;
    }

    Alert new_alert;
    new_alert.alert_id = *count + 1;

    printf("Enter Student Name: ");
    fgets(new_alert.student_name, sizeof(new_alert.student_name), stdin);
    new_alert.student_name[strcspn(new_alert.student_name, "\n")] = 0;

    printf("Enter Emergency Type (Medical/Security/Fire/Other): ");
    fgets(new_alert.emergency_type, sizeof(new_alert.emergency_type), stdin);
    new_alert.emergency_type[strcspn(new_alert.emergency_type, "\n")] = 0;

    printf("Enter Location on Campus: ");
    fgets(new_alert.location, sizeof(new_alert.location), stdin);
    new_alert.location[strcspn(new_alert.location, "\n")] = 0;

    strcpy(new_alert.status, "Pending");

    alerts[*count] = new_alert;
    (*count)++;

    printf("Alert successfully logged. Help is on the way.\n");
}

void view_alerts(Alert *alerts, int count) {
    if (count == 0) {
        printf("No active alerts at the moment.\n");
        return;
    }

    printf("\n--- Active Emergency Alerts ---\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d | Name: %s | Type: %s | Location: %s | Status: %s\n",
               alerts[i].alert_id, 
               alerts[i].student_name, 
               alerts[i].emergency_type, 
               alerts[i].location, 
               alerts[i].status);
    }
    printf("-------------------------------\n");
}

void save_to_file(Alert *alerts, int count) {
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Error opening file for saving.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%s,%s,%s\n", 
                alerts[i].alert_id, 
                alerts[i].student_name, 
                alerts[i].emergency_type, 
                alerts[i].location, 
                alerts[i].status);
    }
    fclose(file);
    printf("Alerts saved to %s successfully.\n", FILE_NAME);
}

void load_from_file(Alert *alerts, int *count) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        // File doesn't exist yet, which is fine on first run
        return;
    }

    while (fscanf(file, "%d,%49[^,],%29[^,],%49[^,],%19[^\n]\n", 
                  &alerts[*count].alert_id, 
                  alerts[*count].student_name, 
                  alerts[*count].emergency_type, 
                  alerts[*count].location, 
                  alerts[*count].status) == 5) {
        (*count)++;
    }
    fclose(file);
}
